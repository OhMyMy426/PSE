#pragma once
#include "Calculator.h"
#include "Particle.h"

class LJCalculator: public Calculator {
public:
  LJCalculator();
  virtual ~LJCalculator();

  void calculateF_LJ(Particle& firstParticle, Particle& secondParticle, double& sigma, double& epsilon);
};