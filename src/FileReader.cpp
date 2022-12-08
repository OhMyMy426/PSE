/*
 * FileReader.cpp
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#include "FileReader.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "Cuboid.h"

#include <memory>
#include <unordered_map>
#include "ParticleContainer.h"
#include"spdlog/spdlog.h"
#include "input.hxx"
#include "../libs/libxsd/xsd/cxx/xml/dom/auto-ptr.hxx"


FileReader::FileReader() = default;

FileReader::~FileReader() = default;

/**
 * Read in a File of particles for week 1 - Planets.
 *
 * @param particleContainer The particleContainer in which the particles should be read into
 * @param filename The filename of the inputfile
 */
void FileReader::readFile(ParticleContainer& particleContainer, const char* filename) { //changed FileReader arguments
  std::array<double, 3> x;
  std::array<double, 3> v;
  double m;
  int num_particles = 0;

  std::ifstream input_file(filename);
  std::string tmp_string;

  if (input_file.is_open()) {

    getline(input_file, tmp_string);
    spdlog::info("Read line: {}",tmp_string);
    //std::cout << "Read line: " << tmp_string << std::endl;

    while (tmp_string.empty() || tmp_string[0] == '#') {
      getline(input_file, tmp_string);
      spdlog::info("Read line: {}",tmp_string);
      //std::cout << "Read line: " << tmp_string << std::endl;
    }

    std::istringstream numstream(tmp_string);
    numstream >> num_particles;
    spdlog::info("Reading: {}.",num_particles);
   
    getline(input_file, tmp_string);
    spdlog::info("Read line: {}",tmp_string);
    

    particleContainer.getParticles().reserve(num_particles);

    for (int i = 0; i < num_particles; i++) {
      std::istringstream datastream(tmp_string);

      for (auto &xj : x) {
        datastream >> xj;
      }
      for (auto &vj : v) {
        datastream >> vj;
      }
      if (datastream.eof()) {
        spdlog::info("Error reading file: eof reached unexpectedly reading from line ",i);
       /* std::cout
            << "Error reading file: eof reached unexpectedly reading from line "
            << i << std::endl;*/
        exit(-1);
      }
      datastream >> m;

      particleContainer.getParticles().emplace(particleContainer.getParticle_counter(), Particle (x, v, m, 0));
      particleContainer.setParticleCounter(particleContainer.getParticle_counter()+1);

      getline(input_file, tmp_string);
      spdlog::info("Read line: {}",tmp_string);
      //std::cout << "Read line: " << tmp_string << std::endl;
    }
  } else {
    spdlog::warn("Error: could not open file {}. The program will terminate now!",filename);
    exit(-1);
  }
}

/**
 * Read in a File of particles for week 2 - LJ-Potaential.
 *
 * @param CuboidVektor A Vektor of cuboids in that the cuboids specified in the file should be added to
 * @param filename The filename of the inputfile
 */
void FileReader::readFileCuboids(std::vector<Cuboid>& CuboidVektor, std::auto_ptr<input> h) { //changed FileReader arguments
  std::array<double, 3> leftLowerCorner;
  std::array<int, 3> amoutOfParticles;
  double meshWidth;
  double particleMass;
  std::array<double, 3> initialVelocity;
  double brownianMotionVelocity = .0;
  int dimensions = 0;
  int num_particles;

  std::ifstream input_file(h ->inputfile ());
  std::string tmp_string;

  if (input_file.is_open()) {

    getline(input_file, tmp_string);

    spdlog::info("Read line: {}",tmp_string);

    while (tmp_string.empty() || tmp_string[0] == '#') {
      getline(input_file, tmp_string);
      spdlog::info("Read line: {}",tmp_string);
    }

    std::istringstream numstream(tmp_string);
    numstream >> num_particles;
    spdlog::info("Reading: {}",num_particles);
    getline(input_file, tmp_string);
    spdlog::info("Read line: {}",tmp_string);

    CuboidVektor.reserve(CuboidVektor.size()+num_particles);

    for (int i = 0; i < num_particles; i++) {
      std::istringstream datastream(tmp_string);

      for (auto &xj : leftLowerCorner) {
        datastream >> xj;
      }
      if (datastream.eof()) {
        spdlog::info("Error reading file: eof reached unexpectedly reading from line  {}",i);
            
        exit(-1);
      }
      for (auto &vj : amoutOfParticles) {
        datastream >> vj;
      }
      if (datastream.eof()) {
         spdlog::info("Error reading file: eof reached unexpectedly reading from line  {}",i);
        exit(-1);
      }
      datastream >> meshWidth;
      datastream >> particleMass;
      if (datastream.eof()) {
         spdlog::info("Error reading file: eof reached unexpectedly reading from line  {}",i);
        exit(-1);
      }
      for (auto &xj : initialVelocity) {
        datastream >> xj;
      }
      if (datastream.eof()) {
        spdlog::info("Error reading file: eof reached unexpectedly reading from line  {}",i);
        exit(-1);
      }
      datastream >> brownianMotionVelocity;
      datastream >> dimensions;

      CuboidVektor.emplace_back(Cuboid(leftLowerCorner, amoutOfParticles, meshWidth, particleMass, initialVelocity, brownianMotionVelocity, dimensions));

      getline(input_file, tmp_string);
      spdlog::info("Read line: {}",tmp_string);
    }
  } else {
     spdlog::info("Error: could not open file {}. The program will terminate now!",h->inputfile ());
    exit(-1);
  }
}
