#pragma once
#include <vector>
#include <unordered_map>
#include <Particle.h>
#include <Cuboid.h>

class Generator
{
private:
    std::vector<Cuboid> Cuboids;
    std::vector<Particle> Particles;
public:
    Generator(const Generator& other);
    Generator(std::vector<Cuboid> cuboids);
    void initialise(std::vector<Cuboid>& cuboids, std::unordered_map<int,Particle>& particles, int& particleCounter);
    std::vector<Cuboid>& getCuboids();
    std::vector<Particle>& getParticles();
};





