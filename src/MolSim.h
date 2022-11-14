#pragma once
#include "ParticleContainer.h"
#include "Particle.h"

class MolSim {
public:
  MolSim();
  virtual ~MolSim();

  int  firstWeek(ParticleContainer& particleContainer, double& end_time, double& delta_t);
};