#pragma once

#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"
#include <string>
#include "ParticleContainer.h"


class OutputWriter {

public:
  OutputWriter();
  virtual ~OutputWriter();

  void VTKOutput(ParticleContainer& particleContainer, int iteration, std::string out_name);
};
