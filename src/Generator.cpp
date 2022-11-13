#include <vector>
#include "Particle.h"
#include "Generator.h"
#include "Cuboid.h"
#include <array>
#include <iostream>


Generator::Generator(const Generator& other) {
    Particles = other.Particles;
}

Generator::Generator(std::vector<Cuboid> Cuboids_args) :Cuboids(Cuboids_args) {
    std::size_t size = {0};
    for (Cuboid n : Cuboids) {
         int x_size = n.getAmountOfParticles().at(0);
        int y_size = n.getAmountOfParticles().at(1);
        int z_size = n.getAmountOfParticles().at(2);
        size += x_size * y_size * z_size;
    }
    Particles.reserve(size);
    std::cout << "Cuboids are already stored!" << std::endl;
}


void Generator::initialise(std::vector<Cuboid>& cuboids, std::vector<Particle>& Particles) {
    for (Cuboid n : Cuboids) {
        int x_size = n.getAmountOfParticles().at(0);
        int y_size = n.getAmountOfParticles().at(1);
        int z_size = n.getAmountOfParticles().at(2);
        for (int i{ 0 };i < x_size;++i) {
            for (int j{ 0 };i < x_size;++i) {
                for (int k{ 0 };i < x_size;++i) {
                    std::array<double, 3 > position = n.getLeftLowerCorner();
                    position.at(0) += i * n.getMeshWidth();
                    position.at(1) += j * n.getMeshWidth();
                    position.at(2) += k * n.getMeshWidth();
                    Particles.push_back(Particle(position, n.getInitialVelocity(), n.getParticleMass(), 0)); 
                }
            }
        }
    }
}


std::vector<Cuboid>& Generator::getCuboids() {
    return Cuboids;
};
std::vector<Particle>& Generator::getParticles() {
    return Particles;
}
