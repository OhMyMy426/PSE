#include "InputReader.h"
#include <iostream>
#include <vector>
#include "Cuboid.h"
#include "Generator.h"
#include "ParticleContainer.h"
#include "Particle.h"
#include "Simulator.h"
#include <unordered_map>
#include <iostream>
#include "MolSim.h"
#include"spdlog/spdlog.h"


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
    
    spdlog::info("Hello and welcome to Molecular Simulations. Please choose the week you would like to use. Week one (\'1\') is Simulation of Planets, week two (\'2\') Lennard-Jones-Potential");
    
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
                MolSim molSim;
                molSim.firstWeek(particleContainer, end_time, delta_t);
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
                Simulator simulator;
                simulator.runSimulation(particleContainer, end_time, delta_t, epsilon, sigma);
        }
            break;
        default: 
        spdlog::warn("Bad week-input, start the program again please and choose either 1 or 2!!!");
           
    }



return 0;



}
