#pragma once
#include "ParticleContainer.h"
#include "Particle.h"
#include "Simulator.h"

class Week1Simulator: public Simulator {
public:
  Week1Simulator();
  virtual ~Week1Simulator();

  int runSimulation(ParticleContainer& particleContainer, double& end_time, double& delta_t);
};