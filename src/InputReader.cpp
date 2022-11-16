#include "FileReader.h"
#include "Cuboid.h"
#include <string>
#include <iostream>
#include "InputReader.h"
#include "ParticleContainer.h"
#include "Particle.h"

InputReader::InputReader() = default;

InputReader::~InputReader() = default;

void InputReader::startInteractiveCommandLine(std::vector<Cuboid>& cuboids, double& end_time, double& delta_t, double& sigma, double& epsilon){
    std::string inputFile = "";
    FileReader fileReader;
    std::string inputString = "";
    std::cout << "Welcome to Week 2" << std::endl;
    while (true) {
        std::cout << "The status quo is:" << std::endl;
        std::cout << "\t- The End-Time is set to " << end_time << "." << std::endl;
        std::cout << "\t- The Delta_t is set to " << delta_t << "." << std::endl;
        std::cout << "\t- The epsilon is set to " << epsilon << "." << std::endl;
        std::cout << "\t- The sigma is set to " << sigma << "." << std::endl;
        if (cuboids.size() == 0) {
            std::cout << "\t- You have no cuboids set up so far." << std::endl;
        } else {
            std::cout << "\t- You have " << cuboids.size() << " cuboids set up." << std::endl;
        }
        std::cout << "If you would like to view your Cuboids, type in \'C\'.\nTo set up a new Cuboid manually, type in \'M\'.\nTo read in a File, type in \'F\'. \nTo set the End-Time or Delta_t, use \'E\' or \'D\', respectively.\n\'P\' is for setting the epsilon, \'I\' sets the sigma. \n\'S\' starts the Simulation." << std::endl;
        char chosenOption = 'x'; 
        std::cin >> chosenOption;

        switch(chosenOption) {
            case 'C': 
                if (cuboids.size() == 0) {
                    std::cout << "You have no cuboids set up so far.";
                } else {
                    for (int i = 0; i < (int) cuboids.size(); ++i) {
                        std::cout << "Cuboid number " << i << " :" << std::endl;
                        std::cout << cuboids.at(i) << std::endl;
                    }
                    std::cout << std::endl;
                }
                break;
            case 'E':
                std::cout << "The current End-Time is :" << end_time << ".\n\t Please input a new value: ";
                std::cin >> end_time;
                while (end_time <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> end_time;
                }
                break;
            case 'D':
                std::cout << "The current Delta_t is :" << delta_t << ".\n\t Please input a new value: ";
                std::cin >> delta_t;
                while (delta_t <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> delta_t;
                }
                break;
            case 'I':
                std::cout << "The current Sigma is :" << sigma << ".\n\t Please input a new value: ";
                std::cin >> sigma;
                while (sigma <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> sigma;
                }
                break;
            case 'P':
                std::cout << "The current Epsilon is :" << epsilon << ".\n\t Please input a new value: ";
                std::cin >> epsilon;
                while (epsilon <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> epsilon;
                }
                break;
            case 'F':
                    {
                std::cout << "Please input a file: ";
                std::cin >> inputFile;
                const char* inputFilePointer = inputFile.c_str();
                fileReader.readFileCuboids(cuboids, inputFilePointer);
                std::cout << "Particles read!" << std::endl;
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
                std::cout << "Please input the Coordinates of the left lower Corner." << std::endl;
                std::cout << "\tThe first coordinate: ";
                std::cin >> leftLowerCorner.at(0);
                std::cout << "\tThe second coordinate: ";
                std::cin >> leftLowerCorner.at(1);
                std::cout << "\tThe third coordinate: ";
                std::cin >> leftLowerCorner.at(2);
                std::cout << "Please input the amout of particles in each direction." << std::endl;
                std::cout << "\tIn x direction: ";
                std::cin >> amountOfParticles.at(0);
                std::cout << "\tIn y direction: ";
                std::cin >> amountOfParticles.at(1);
                std::cout << "\tIn z direction: ";
                std::cin >> amountOfParticles.at(2);
                std::cout << "Please input the width of the Mesh: ";
                std::cin >> meshWidth;
                std::cout << "Please input the mass of a particle: ";
                std::cin >> particleMass;
                std::cout << "Please input the initial velocity of a particle in each direction." << std::endl;
                std::cout << "\tIn x direction: ";
                std::cin >> initialVelocity.at(0);
                std::cout << "\tIn y direction: ";
                std::cin >> initialVelocity.at(1);
                std::cout << "\tIn z direction: ";
                std::cin >> initialVelocity.at(2);
                std::cout << "Please input the average for the Brownian Motion: ";
                std::cin >> brownianMotionVelocity;
                std::cout << "Please input the Dimensions: ";
                std::cin >> dimensions;

                cuboids.emplace_back(Cuboid(leftLowerCorner, amountOfParticles, meshWidth, particleMass, initialVelocity, brownianMotionVelocity, dimensions));
                    }
                break;
            case 'S': 
                std::cout << "Simulation started!" << std::endl;
                return;
            default:
                std::cout << "Bad option, please try again!" << std::endl;
                break;
        }
    }

}

  void InputReader::firstWeekInput(double& end_time, double delta_t, ParticleContainer& particleContainer) {
    std::string inputFile = "";
    FileReader fileReader;
    std::string inputString = "";
    std::cout << "Welcome to Week 1" << std::endl;
    while (true) {
        std::cout << "The status quo is:" << std::endl;
        std::cout << "\t- The End-Time is set to " << end_time << "." << std::endl;
        std::cout << "\t- The Delta_t is set to " << delta_t << "." << std::endl;
        std::cout << "To set the End-Time, please type in \'E\'. To set the Delta_t, use \'D\'. \nUse \'F\' to specify the input file. \n\'S\' starts the Simulation." << std::endl;

        char chosenOption = 'x'; 
        std::cin >> chosenOption;

        switch(chosenOption){
            case 'E':
                std::cout << "The current End-Time is :" << end_time << ".\n\t Please input a new value: " ;
                std::cin >> end_time;
                while (end_time <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> end_time;
                }
                break;
            case 'D':
                std::cout << "The current Delta_t is :" << delta_t << ".\n\t Please input a new value: ";
                std::cin >> delta_t;
                while (delta_t <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one: ";
                    std::cin >> delta_t;
                }
                break;
            case 'F':
                    {
                std::cout << "Please input a file: ";
                std::cin >> inputFile;
                const char* inputFilePointer = inputFile.c_str();
                fileReader.readFile(particleContainer, inputFilePointer);
                std::cout << "Particles read!" << std::endl;
                    }
                break;
            case 'S': 
                std::cout << "Simulation started!" << std::endl;
                return;
            default:
                std::cout << "Bad option, please try again!" << std::endl;
                break;
        }

    }
    

  }
