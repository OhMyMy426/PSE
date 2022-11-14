#pragma once
#include <vector>
#include "Cuboid.h"

class InputReader {
public:
  InputReader();
  virtual ~InputReader();

  void startInteractiveCommandLine(std::vector<Cuboid>& cuboids, double& end_time, double& delta_t, double& sigma, double& epsilon);
  void firstWeekInput(double& end_time, double delta_t, ParticleContainer& particleContainer);
};
