#include "InputReader.h"
#include <iostream>
#include <vector>
#include "Cuboid.h"
#include "ParticleContainer.h"
#include "Particle.h"
#include "Simulator.h"
#include <unordered_map>
#include <iostream>
#include "MolSim.h"

//This is the Main Class of the new Project. From here, the simulation of the first and second homework can be started

int main(int argc, char *argsv[]) {
    //first, the user is asked for the week he wants to run
    std::cout << "Hello and welcome to Molecular Simulations. Please choose the week you would like to use. Week one is Simulation of Planets, week two Lennard-Jones-Potential" << std::endl;
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
                double end_time = 1000;
                double delta_t = 0.014;
                double sigma = 1;
                double epsilon = 5;
                //calling of the command line
                InputReader inputReader;
                inputReader.startInteractiveCommandLine(cuboids, end_time, delta_t, sigma, epsilon);
                //initialise the unordered Map and the counter that the generator fills that then goes into the ParticleContainer for the Simulation in Simulator
                std::unordered_map<int, Particle> particles {};
                int particle_counter = 0;
                //Call the Generator, giving us the Particles out of the Cuboids the user gave us
                ParticleContainer particleContainer(particles, particle_counter);
                //Construct our Simulator and run the Simulation with the given Parameters
                Simulator simulator;
                simulator.runSimulation(particleContainer, end_time, delta_t, epsilon, sigma);
        }
            break;
        default: 
            std::cout << "Bad week-input, start the program again please and choose either 1 or 2!!!" << std::endl;
    }



return 0;



}
