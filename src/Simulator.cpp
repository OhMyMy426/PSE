//This class runs the simulation. It calls the calculator on the particles and calls the OutputWriter to do the output. It´s called by MainClass

#include "Simulator.h"
#include "Calculator.h"
#include "LJCalculator.h"
#include <array>
#include "OutputWriter.h"
#include <iostream>


Simulator::Simulator() = default;

Simulator::~Simulator() = default;


void Simulator::runSimulation(ParticleContainer& particleContainer, double& end_time, double& delta_t, double& epsilon, double& sigma) {
  //setting up
  LJCalculator calculator;
  OutputWriter outputWriter;
  const double start_time = 0;
  double current_time = start_time;
  int iteration = 0;
  

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


  //increase the Iteration and plot if necc
  iteration++;
  if (iteration % 10 == 0) {
    outputWriter.VTKOutput(particleContainer, iteration, "Simulation2");
  }
//    std::cout << "Iteration " << iteration << " finished." << std::endl;


  //increase the current time
  current_time += delta_t;
  }

  
  
}
