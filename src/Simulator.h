//Author: ALex
//This class is the framework for running a Simulation from week 2 on. It calls the Methods of the Calculator, handles the Output writing and loops over the timesteps
//The input parameters for the simulation are the particles, the End-Time and the Delta_t


#pragma once

#include "Particle.h"

#include <list>
#include <unordered_map>

#include "ParticleContainer.h"

class Simulator {

public:
  Simulator();
  virtual ~Simulator();

  void runSimulation(ParticleContainer& particleContainer, double& end_time, double& delta_t, double& epsilon, double& sigma);
 
};
