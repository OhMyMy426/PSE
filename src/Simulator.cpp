//This class runs the simulation. It calls the calculator on the particles and calls the OutputWriter to do the output. It´s called by MainClass

#include "Simulator.h"
#include "Calculator.h"
#include "LJCalculator.h"
#include <array>
#include "OutputWriter.h"
#include <iostream>
#include <chrono>


Simulator::Simulator() = default;

Simulator::~Simulator() = default;

/**
 * Runs the entire simulation for week 2. Can benchmark.
 *
 * @param particleContainer the ParticleContainer with the particles to simulate
 * @param end_rime The End-Time of the simulation
 * @param delta_t The delta_t of the simulation
 * @param epsilon The epsilon for the force Calculation with the LJ-Potential
 * @param sigma The sigma for the force Calculation with the LJ-Potential

 */
void Simulator::runSimulation(ParticleContainer& particleContainer, double& end_time, double& delta_t, double& epsilon, double& sigma) {
  //setting up
  LJCalculator calculator;
  OutputWriter outputWriter;
  const double start_time = 0;
  double current_time = start_time;
  int iteration = 0;
  char timeSelection = 'x';

  std::cout << "Would you like to measure the raw time of the simulation (Particles already set up)? No output files will be generated. Please input Y/N: ";
  std::cin >> timeSelection;

  while (timeSelection != 'N' && timeSelection != 'Y') {
    std::cout << "Invalid input for time detection. Please input Y/N: ";
  std::cin >> timeSelection;
  }
  

  //Setting up time measurement
  auto start = std::chrono::high_resolution_clock::now();

  //This runs the simulation
  while (current_time < end_time) {
  
  // calculate new x 
  for (int i = 0; i < particleContainer.getParticle_counter(); ++i){
      calculator.calculateX(particleContainer.getParticles().at(i), delta_t);
  }


  // shift the forces and calculate the new ones
  //shift the first force:
  particleContainer.getParticles().at(0).setOldF(particleContainer.getParticles().at(0).getF()); 
  particleContainer.getParticles().at(0).setF(std::array<double,3> {.0,.0,.0});
  //the double loop for the force calculation. calculation itself is done by the chosen calculator
  for (int i = 0; i < particleContainer.getParticle_counter(); ++i){
    for (int j = i+1; j < particleContainer.getParticle_counter(); ++j) {
      //shift the other forces. if there are many particles, this may be faster
      if (i == 0) {  
        particleContainer.getParticles().at(j).setOldF(particleContainer.getParticles().at(j).getF()); 
        particleContainer.getParticles().at(j).setF(std::array<double,3> {.0,.0,.0});
      }
      //the force calculation itself. The calculated force is added on both particles according to newtons third law
      calculator.calculateF_LJ(particleContainer.getParticles().at(i), particleContainer.getParticles().at(j), sigma, epsilon);
    }
  }
  

  // calculate new v
  for (int i = 0; i < particleContainer.getParticle_counter(); ++i){
      calculator.calculateV(particleContainer.getParticles().at(i), delta_t);
  }


  //increase the Iteration and plot if necc. IF we measure the time, output is skipped
  iteration++;
  if (iteration % 10 == 0 && timeSelection == 'N') {
    outputWriter.VTKOutput(particleContainer, iteration, "Simulation2");
  }
//std::cout << "Iteration " << iteration << " finished." << std::endl;
  //increase the current time
  current_time += delta_t;
  }
    //if asked, we output the time for the raw Simulation
  auto stop = std::chrono::high_resolution_clock::now();
  if (timeSelection == 'Y') {
    std::cout << "Elapsed time in seconds: " << std::chrono::duration_cast<std::chrono::seconds>(stop - start).count() << " seconds, or " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " in milliseconds." << std::endl;      
  }

  
}
