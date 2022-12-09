#pragma once

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include <string>
#include "ParticleContainer.h"
#include "LinkedCellContainer2D.h"


class OutputWriter {
private:
  int counter;
public:
  OutputWriter();
  virtual ~OutputWriter();

  void VTKOutput(ParticleContainer& particleContainer, int iteration, std::string out_name);
  void VTKOutput(LinkedCellContainer2D& linkedCellContainer, int iteration, std::string out_name);
};
