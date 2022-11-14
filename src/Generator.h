#pragma once
#include <vector>
#include <unordered_map>
#include "Particle.h"
#include "Cuboid.h"

class Generator
{
private:
    std::vector<Particle> Particles;
public:
    Generator(const Generator& other);
    Generator(std::vector<Cuboid> cuboids);
};



    

