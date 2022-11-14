/*
 * FileReader.h
 *
 *  Created on: 23.02.2010
 *      Author: eckhardw
 */

#pragma once

#include "Particle.h"

#include <list>
#include <unordered_map>
#include <vector>
#include "Cuboid.h"

#include "ParticleContainer.h"

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  void readFile(ParticleContainer& particleContainer, const char* filename);
  void readFileCuboids(std::vector<Cuboid>& CuboidVektor, const char* filename);
};
