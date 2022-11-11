#include "FileReader.h"
#include "Cuboid.h"
#include <string>
#include <iostream>



void startInteractiveCommandLine(){
    std::cout << "Willkommen zu MolSim!" << std::endl;
    std::string inputFile = "";
    std::vector<Cuboid> cuboids {};
    double end_time = 1000.0;
    double delta_t = 0.014;
    while (true) {
        std::cout << "The status quo is:" << std::endl;
        std::cout << "\t- The End-Time is set to " << end_time << "." << std::endl;
        std::cout << "\t- The Delta_t is set to " << delta_t << "." << std::endl;
        if (cuboids.size() == 0) {
            std::cout << "\t- You have no cuboids set up so far." << std::endl;
        } else {
            std::cout << "\t- You have " << cuboids.size() << " cuboids set up." << std::endl;
        }
        std::cout << "If you would like to view your Cuboids, type in \'C\'.\n To set up a new Cuboid manually, type in \'M\'. To read in a File, type in \'F\'.
                         To set the End-Time or Delta_t, use \'E\' or \'D\', respectively. \'S\' starts the Simulation." << std::endl;
        char chosenOption = 'x'; 
        std::cin >> chosenOption;

        switch(chosenOption) {
            case 'C': 
                if (cuboids.size() == 0) {
                    std::cout << "You have no cuboids set up so far.";
                } else {
                    for (int i = 0; i < cuboids.size(); ++i) {
                        std::cout << "Cuboid number " << i << " :" << std::endl;
                        std::cout << cuboids.at(i) << std::endl;
                    }
                }
                break;
            case 'E':
                std::cout << "The current End-Time is :" << end_time << ".\n\t Please input a new value:" << std::endl;
                std::cin >> end_time;
                while (end_time <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one!" << std::endl;
                    std::cin >> end_time;
                }
                break;
            case 'D':
                 std::cout << "The current Delta_t is :" << delta_t << ".\n\t Please input a new value:" << std::endl;
                std::cin >> delta_t;
                while (delta_t <= 0.0) {
                    std::cout << "This is an invalid time. Please input a new one!" << std::endl;
                    std::cin >> delta_t;
                }
                break;
            
        }
    }
}