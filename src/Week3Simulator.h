#pragma once

#include "Simulator.h"
#include "Particle.h"
#include "LinkedCellContainer2D.h"
#include "Week3Metadata.h"

class Week3Simulator: public Simulator {

public:
  Week3Simulator();
  virtual ~Week3Simulator();

  void runSimulation(LinkedCellContainer2D& linkedCellContainer, Week3Metadata& week3data);

};
