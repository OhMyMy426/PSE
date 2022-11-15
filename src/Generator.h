//The particle-generator, generating the particles from the cuboids
//Author: Xiyu
#pragma once
#include <vector>
#include <unordered_map>
#include "Particle.h"
#include "Cuboid.h"
#include "ParticleContainer.h"

class Generator
{
private:
    std::vector<Cuboid> Cuboids = {};
    std::vector<Particle> Particles = {};
public:
    Generator(const Generator& other);
    Generator(std::vector<Cuboid>& Cuboids_args);
    Generator();
    virtual ~Generator();
    void initialise(std::vector<Cuboid>& cuboids, ParticleContainer& particleContainer);
    std::vector<Cuboid>& getCuboids();
    std::vector<Particle>& getParticles();
};



    


