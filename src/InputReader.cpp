#include "FileReader.h"
#include "Cuboid.h"
#include <string>
#include <iostream>
#include "InputReader.h"
#include "ParticleContainer.h"
#include "Particle.h"
#include"spdlog/spdlog.h"
#include <memory>
#include "../libs/libxsd/xsd/cxx/xml/dom/auto-ptr.hxx"
#include "input.hxx"



InputReader::InputReader() = default;

InputReader::~InputReader() = default;

void InputReader::startInteractiveCommandLine(std::vector<Cuboid>& cuboids, double& end_time, double& delta_t, double& sigma, double& epsilon,std::auto_ptr<input> h){
    std::string inputFile = "";
    FileReader fileReader;
    std::string inputString = "";
    spdlog::info("Welcome to Week 2");
    
    while (true) {
      spdlog::info("The status quo is:");
        spdlog::info("\t- The End-Time is set to {}",end_time);
        spdlog::info("\t- The Delta_t is set to {}",delta_t);
        spdlog::info("\t- The epsilon is set to {} ",epsilon);
        spdlog::info("\t- The sigma is set to {}",sigma);
        if (cuboids.size() == 0) {
            spdlog::warn("\t- You have no cuboids set up so far.");
            
        } else {
            spdlog::info(" \t- You have {} cuboids set up.", cuboids.size());
           
        }
        spdlog::info("\nIf you would like to view your Cuboids, type in \'C\'.\nTo set up a new Cuboid manually, type in \'M\'.\nTo read in a File, type in \'F\'. \nTo set the End-Time or Delta_t, use \'E\' or \'D\', respectively.\n\'P\' is for setting the epsilon, \'I\' sets the sigma. \n\'S\' starts the Simulation.");
        
        char chosenOption = 'x'; 
        std::cin >> chosenOption;

        switch(chosenOption) {
            case 'C': 
                if (cuboids.size() == 0) {
                     spdlog::info("You have no cuboids set up so far.");
                    
                } else {
                    for (int i = 0; i < (int) cuboids.size(); ++i) {
                        spdlog::info("Cuboid number {}",i);    
                    }
                    
                }
                break;
            case 'E':
                spdlog::info("The current End-Time is : {} \n\t Please input a new value:",end_time);
                std::cin >> end_time;
                while (end_time <= 0.0) {
                    spdlog::warn("This is an invalid time. Please input a new one: ");
                    std::cin >> end_time;
                }
                break;
            case 'D':
                spdlog::info("The current Delta_t is :{}.\n\t Please input a new value: ",delta_t);
                std::cin >> delta_t;
                while (delta_t <= 0.0) {
                    spdlog::warn("This is an invalid time. Please input a new one: ");                   
                    std::cin >> delta_t;
                }
                break;
            case 'I':
                spdlog::info("The current sigma is :{}.\n\t Please input a new value: ",sigma);
                std::cin >> sigma;
                while (sigma <= 0.0) {
                    spdlog::warn("This is an invalid time. Please input a new one: ");
                    
                    std::cin >> sigma;
                }
                break;
            case 'P':
            spdlog::info("The current epsilon is :{}.\n\t Please input a new value: ",epsilon);
                
                std::cin >> epsilon;
                while (epsilon <= 0.0) {
                    spdlog::warn("This is an invalid time. Please input a new one: ");
                   
                    std::cin >> epsilon;
                }
                break;
            case 'F':
                    {
                spdlog::info("Please input a file: ");               
                std::cin >> inputFile;
                const char* inputFilePointer = inputFile.c_str();
                fileReader.readFileCuboids(cuboids, h);
                spdlog::info("Particles read!" );
                
                    }
                break;
            case 'M':
                    {
                std::array<double,3> leftLowerCorner {};
                std::array<int,3> amountOfParticles {};
                double meshWidth = .0;
                double particleMass = .0;
                std::array<double,3> initialVelocity {};
                double brownianMotionVelocity = .0;
                int dimensions = 0;
                spdlog::info("Please input the Coordinates of the left lower Corner.");
                spdlog::info("\tThe first coordinate: ");
                
               
                std::cin >> leftLowerCorner.at(0);
               
                 spdlog::info("\tThe second coordinate: ");
                std::cin >> leftLowerCorner.at(1);
                 spdlog::info("\tThe third coordinate: ");
                std::cin >> leftLowerCorner.at(2);
                spdlog::info("Please input the amout of particles in each direction.");
                spdlog::info("\tIn x direction: ");                
                std::cin >> amountOfParticles.at(0);
                 spdlog::info("\tIn y direction: ");
                std::cin >> amountOfParticles.at(1);
                 spdlog::info("\tIn z direction: ");
                std::cin >> amountOfParticles.at(2);
                
                spdlog::info("Please input the width of the Mesh: ");
                std::cin >> meshWidth;
                
                spdlog::info("Please input the mass of a particle: ");
                std::cin >> particleMass;
                
                spdlog::info("Please input the initial velocity of a particle in each direction.");
                
                spdlog::info("\tIn x direction: ");
                std::cin >> initialVelocity.at(0);
                spdlog::info("\tIn y direction: ");
                std::cin >> initialVelocity.at(1);
                spdlog::info("\tIn z direction: ");
                std::cin >> initialVelocity.at(2);
                
                spdlog::info("Please input the average for the Brownian Motion: ");
                std::cin >> brownianMotionVelocity;
                
                 spdlog::info("Please input the Dimensions: ");
                std::cin >> dimensions;

                cuboids.emplace_back(Cuboid(leftLowerCorner, amountOfParticles, meshWidth, particleMass, initialVelocity, brownianMotionVelocity, dimensions));
                    }
                break;
            case 'S': 
            spdlog::info("Simulation started!");
               
                return;
            default:
            spdlog::warn("Bad option, please try again!");std::cout << "Bad option, please try again!" << std::endl;
                break;
        }
    }

}

  void InputReader::firstWeekInput(double& end_time, double delta_t, ParticleContainer& particleContainer) {
    std::string inputFile = "";
    FileReader fileReader;
    std::string inputString = "";
    spdlog::info("Welcome to Week 1");
   
    while (true) {
        spdlog::info("The status quo is:");
        spdlog::info("\t- The End-Time is set to {}",end_time);
        spdlog::info("\t- The Delta_t is set to {}",delta_t);
       spdlog::info("To set the End-Time, please type in \'E\'. To set the Delta_t, use \'D\'. \nUse \'F\' to specify the input file. \n\'S\' starts the Simulation.");
        

        char chosenOption = 'x'; 
        std::cin >> chosenOption;

        switch(chosenOption){
            case 'E':
                spdlog::info("The current End-Time is : {} \n\t Please input a new value:",end_time);
                std::cin >> end_time;
                while (end_time <= 0.0) {
                    spdlog::warn("This is an invalid time. Please input a new one: ");
                    std::cin >> end_time;
                }
                break;
            case 'D':
                 spdlog::info("The current Delta_t is :{}.\n\t Please input a new value: ",delta_t);
                std::cin >> delta_t;
                while (delta_t <= 0.0) {
                   spdlog::warn("This is an invalid time. Please input a new one: ");
                    std::cin >> delta_t;
                }
                break;
            case 'F':
                    {
                        spdlog::info("Please input a file: ");
                
                std::cin >> inputFile;
                const char* inputFilePointer = inputFile.c_str();
                fileReader.readFile(particleContainer, inputFilePointer);
                spdlog::info("Particles read!");
                
                    }
                break;
            case 'S': 
               spdlog::info("Simulation started!" );               
                return;
            default:
              spdlog::warn("Bad option, please try again!" );

                break;
        }

    }
    

  }