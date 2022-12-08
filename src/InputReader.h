#pragma once
#include <vector>
#include "Cuboid.h"
#include "Particle.h"
#include "ParticleContainer.h"
#include <memory>
#include "../libs/libxsd/xsd/cxx/xml/dom/auto-ptr.hxx"
#include "input.hxx"





class InputReader {
public:
  InputReader();
  virtual ~InputReader();

  void startInteractiveCommandLine(std::vector<Cuboid>& cuboids, double& end_time, double& delta_t, double& sigma, double& epsilon,std::auto_ptr<input> h);
  void firstWeekInput(double& end_time, double delta_t, ParticleContainer& particleContainer);
};
