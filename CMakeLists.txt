cmake_minimum_required(VERSION 3.10)

#
if (NOT DEFINED MYFLAGS)
  set(MYFLAGS "-Wall")
endif()

# define project name, version
project(PSEMolDyn_GroupB VERSION 0.0.1)

# let ccmake and cmake-gui offer the default build type options
set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release;RelWithDebInfo;MinSizeRel")

# set Release as the default build type if it is not yet set.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

# collect all cpp files
file(GLOB_RECURSE MY_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    # header don't need to be included but this might be necessary for some IDEs
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# create make target
add_executable(MolSim ${MY_SRC} "src/ParticleContainer.cpp" "src/ParticleContainer.h")

# set cxx standard. You may raise this if you want.
target_compile_features(MolSim
        PRIVATE
            cxx_std_14
)
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/libs)

target_include_directories(MolSim
        PUBLIC SYSTEM
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/libxsd
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(MolSim
        # stuff that is used in headers and source files
        PUBLIC
	xerces-c
	PRIVATE
	${MYFLAGS}
)

set(MyList "src/MainClass.cpp" "src/FileReader.cpp"  "src/Cuboid.cpp" "src/InputReader.cpp" "src/Generator.cpp" "src/Calculator.cpp"  "src/LJCalculator.cpp"  "src/MolSim.cpp"  "src/OutputWriter.cpp" "src/Particle.cpp" "src/ParticleContainer.cpp" "src/Simulator.cpp")
set_source_files_properties(${MyList} PROPERTIES COMPILE_OPTIONS ${MYFLAGS})

#define the flags
# activate all compiler warnings. Clean up your code :P
# depending on the compiler different flags are used
target_compile_options(MolSim
        PRIVATE
            $<$<CXX_COMPILER_ID:GNU>: -Wall >
            # disable some spam warnings for icpc...
            $<$<CXX_COMPILER_ID:Intel>:-w3 -wd383,981,1418,1572,2259>
)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

include(doxygen)

## set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR})

## add_custom_target( doc_doxygen 
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    VERBATIM )

include(doxygen)

## set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR})

## add_custom_target( doc_doxygen 
#   WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#    VERBATIM )


####    GoogleTest
# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  first_test
 # ${MY_SRC}
		src/tests/first_test.cc
	src/spdlog


		)

include_directories(${CMAKE_SOURCE_DIR}/src)
target_link_libraries(

  first_test
  GTest::gtest_main
	xerces-c
)



include(GoogleTest)
gtest_discover_tests(first_test)


#
# Attempt to find the xsd application in various places. If found, the full
# path will be in XSD_EXECUTABLE. Look in the usual locations, as well as in
# the 'bin' directory in the path given in the XSD_ROOT environment variable.
#
FIND_PROGRAM( XSD_EXECUTABLE xsd
		HINTS ${RWSL_DEPS}/xsd/bin $ENV{XSD_ROOT}/bin
		PATHS /usr/local/xsd-3.2.0-i686-macosx/bin
		/usr/local/xsd-3.2.0-x86_64-linux-gnu/bin
		/usr/local/bin
		/opt/xsd-3.2.0-i686-macosx/bin
		/opt/xsd-3.2.0-x86_64-linux-gnu/bin
		/usr/bin
		ENV PATH )

IF( XSD_EXECUTABLE )

	#
	# Obtain the include directory that one can use with INCLUDE_DIRECTORIES() to
	# access the xsd include files.
	#
	GET_FILENAME_COMPONENT( XSD_BIN_DIR "${XSD_EXECUTABLE}" PATH )
	GET_FILENAME_COMPONENT( XSD_ROOT_DIR "${XSD_BIN_DIR}" PATH )
	SET( XSD_INCLUDE_DIR "${XSD_ROOT_DIR}/libxsd" )
ENDIF( XSD_EXECUTABLE )

#
# General CMake package configuration.
#
INCLUDE( FindPackageHandleStandardArgs )
FIND_PACKAGE_HANDLE_STANDARD_ARGS( XSD DEFAULT_MSG XSD_EXECUTABLE
		XSD_INCLUDE_DIR )
IF( XSD_FOUND )
	SET( XSD_INCLUDE_DIRS ${XSD_INCLUDE_DIR} )
ELSE( XSD_FOUND )
	SET( XSD_INCLUDE_DIRS )
ENDIF( XSD_FOUND )

MARK_AS_ADVANCED( XSD_INCLUDE_DIR XSD_EXECUTABLE )

#
# Macro that attempts to generate C++ files from an XML schema. The NAME
# argument is the name of the CMake variable to use to store paths to the
# derived C++ source file. The FILE argument is the path of the schema file to
# process. Additional arguments should be XSD command-line options.
#
# Example:
#
# XSD_SCHEMA( FOO_SRCS Foo.xsd --root-element-first --generate-serialization )
#
# On return, FOO_SRCS will contain Foo.cxx.
#
MACRO( XSD_SCHEMA NAME src/input.xsd )

	#
	# Make a full path from the soource directory
	#
	SET( xs_SRC "${src/input.xsd}" )

	#
	# XSD will generate two or three C++ files (*.cxx,*.hxx,*.ixx). Get the
	# destination file path sans any extension and then build paths to the
	# generated files.
	#
	GET_FILENAME_COMPONENT( xs_FILE "${src/input.xsd}" NAME_WE )
	SET( xs_CXX "${CMAKE_CURRENT_BINARY_DIR}/${xs_FILE}.cxx" )
	SET( xs_HXX "${CMAKE_CURRENT_BINARY_DIR}/${xs_FILE}.hxx" )
	SET( xs_IXX "${CMAKE_CURRENT_BINARY_DIR}/${xs_FILE}.ixx" )

	#
	# Add the source files to the NAME variable, which presumably will be used to
	# define the source of another target.
	#
	LIST( APPEND ${NAME} ${xs_CXX} )

	#
	# Set up a generator for the output files from the given schema file using
	# the XSD cxx-tree command.
	#
	ADD_CUSTOM_COMMAND( OUTPUT "${xs_CXX}" "${xs_HXX}" "${xs_IXX}"
			COMMAND ${XSD_EXECUTABLE}
			ARGS "cxx-tree" ${ARGN} ${xs_SRC}
			DEPENDS ${xs_SRC} )

	#
	# Don't fail if a generated file does not exist.
	#
	SET_SOURCE_FILES_PROPERTIES( "${xs_CXX}" "${xs_HXX}" "${xs_IXX}"
			PROPERTIES GENERATED TRUE )

ENDMACRO( XSD_SCHEMA )
