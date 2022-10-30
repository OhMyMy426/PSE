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

class FileReader {

public:
  FileReader();
  virtual ~FileReader();

  void FileReader::readFile(std::unordered_map<int, Particle> &particles, char* filename, int &particle_counter);
};
