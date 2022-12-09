#include "InputReader.h"
#include <iostream>
#include <vector>
#include "Cuboid.h"
#include "Generator.h"
#include "ParticleContainer.h"
#include "Particle.h"
#include "Week2Simulator.h"
#include <unordered_map>
#include <iostream>
#include "Week1Simulator.h"
#include "spdlog/spdlog.h"
#include "LinkedCellContainer2D.h"
#include "Week3Metadata.h"
#include "Week3Simulator.h"
#include "Cuboid.h"
#include "FileReader.h"
 


//This is the Main Class of the new Project. From here, the simulation of the first and second homework can be started


int main(int argc, char *argsv[]) {




    if (argc<2)
    {spdlog::error("Spdlog level needed");
    exit(-1);}
    if(std::string(argsv[1])=="TRACE")
    {spdlog::set_level(spdlog::level::trace);}
    if(std::string(argsv[1])=="DEBUG")
    {spdlog::set_level(spdlog::level::debug);}
    if(std::string(argsv[1])=="INFO")
    {spdlog::set_level(spdlog::level::info);}
    if(std::string(argsv[1])=="WARN")
    {spdlog::set_level(spdlog::level::warn);}
    if(std::string(argsv[1])=="ERROR")
    {spdlog::set_level(spdlog::level::err);}
    if(std::string(argsv[1])=="CRITICAL")
    {spdlog::set_level(spdlog::level::critical);}
    if(std::string(argsv[1])=="OFF")
    {spdlog::set_level(spdlog::level::off);}
    //first, the user is asked for the week he wants to run
    
    spdlog::info("Hello and welcome to Molecular Simulations. Please choose the week you would like to use. Week one (\'1\') is Simulation of Planets, week two (\'2\') Lennard-Jones-Potential, week three (\'3\') linkedCells.");
    
    int chosenWeek = 0;
    std::cin >> chosenWeek;
    switch (chosenWeek) {
        case 1:
        //if the chosen week is 1, we run our program from last time, as not-glorious as it was
            {
                double end_time = 1000;
                double delta_t = 0.014;
                std::unordered_map<int, Particle> particles{};
                int particle_counter = 0;
                ParticleContainer particleContainer(particles, particle_counter);
                InputReader inputReader;
                inputReader.firstWeekInput(end_time, delta_t, particleContainer);
                Week1Simulator molSim;
                molSim.runSimulation(particleContainer, end_time, delta_t);
            }
            break;
        case 2: {
                //Initialisation of the necessary Variables for the command line for week two
                std::vector<Cuboid> cuboids {}; 
                Generator particleGenerator;
                double end_time = 5;
                double delta_t = 0.0002;
                double sigma = 1;
                double epsilon = 5;
                //calling of the command line
                InputReader inputReader;
                inputReader.startInteractiveCommandLine(cuboids, end_time, delta_t, sigma, epsilon);
                if(cuboids.size() == 0) {
                spdlog::error("No Particles set up! Please set up particles! The program will end now");
                        exit(-1);
                }
                //initialise the unordered Map and the counter that the generator fills that then goes into the ParticleContainer for the Simulation in Simulator
                std::unordered_map<int, Particle> particles {};
                int particle_counter = 0;
                ParticleContainer particleContainer(particles, particle_counter);
                //Call the Generator, giving us the Particles out of the Cuboids the user gave us
                particleGenerator.initialise(cuboids, particleContainer);
                //Construct our Simulator and run the Simulation with the given Parameters
                Week2Simulator simulator;
                simulator.runSimulation(particleContainer, end_time, delta_t, epsilon, sigma);
                break;
        }
        case 3: {
/*            std::array<double, 3>domainSize = {180.0, 90.0, 1.0};
            LinkedCellContainer2D lck(domainSize, 3.0);
            std::vector<Particle> initialiser;
            Generator generator;
            std::vector<Cuboid> cuboids;
            FileReader fileReader;
            const char* fileName = "input/week2Data.txt";
            fileReader.readFileCuboids(cuboids, fileName);
            generator.initialise(cuboids, initialiser);
            lck.initialiseCells(initialiser);
            Week3Metadata week3Data(20.0, 0.00005, 5, 1, 'x', 'x', 'x', 'x', 'm', 'N');*/
            std::array<double, 3>domainSize = {8.0, 8.0, 1.0};
            LinkedCellContainer2D lck(domainSize, 2.0);
            std::vector<Particle> initialiser;
            initialiser.emplace_back(Particle({5.0,5.0,0}, {20.0,.0,.0}, 1, 0));
            lck.initialiseCells(initialiser);
            Week3Metadata week3Data(100.0, 0.002, 5, 1, 'x', 'x', 'x', 'x', 'm', 'N');
            Week3Simulator simulator;
            simulator.runSimulation(lck, week3Data);
            break;
        }
            
        default: 
        spdlog::warn("Bad week-input, start the program again please and choose either 1 or 2!!!");
           
    }



return 0;



}
