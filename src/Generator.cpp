
#include <vector>
#include "Generator.h"
#include "Particle.h"
#include "Cuboid.h"
#include <array>
#include <iostream>
#include "utils/MaxwellBoltzmannDistribution.h"
#include "utils/ArrayUtils.h"
#include <unordered_map>

//a default Constructor
Generator::Generator() {

};
//a default Destructor
Generator::~Generator() = default;

//copy from another Generator
Generator::Generator(const Generator& other) {
    Particles = other.Particles;
}

//Constructor with the cuboids as an argument, initialising the Particle Vektor. Why a Vector? Linked-Cell Method inboud
Generator::Generator(std::vector<Cuboid>& Cuboids_args) :Cuboids(Cuboids_args) {
    std::size_t size = { 0 };
    for (Cuboid n : Cuboids) {
        int x_size = n.getAmountOfParticles().at(0);
        int y_size = n.getAmountOfParticles().at(1);
        int z_size = n.getAmountOfParticles().at(2);
        size += x_size * y_size * z_size;
    }
    Particles.reserve(size);
    std::cout << "Cuboids are already stored!" << std::endl;
    
}



//initialises the given unordered_map for the ParticleContainer
void Generator::initialise(std::vector<Cuboid>& cuboids, std::unordered_map<int, Particle>& particles, int& particleCounter) {
    std::array<double, 3> generateBrownianMovement {.0,.0,.0};
    for (Cuboid n : cuboids) {
        int x_size = n.getAmountOfParticles().at(0);
        int y_size = n.getAmountOfParticles().at(1);
        int z_size = n.getAmountOfParticles().at(2);
        particleCounter = x_size * y_size * z_size;
        particles.reserve(particleCounter);
        int map_counter = { 0 };
        for (int i{ 0 };i < x_size;++i) {
            for (int j{ 0 };i < x_size;++i) {
                for (int k{ 0 };i < x_size;++i) {
                    std::array<double, 3 > position = n.getLeftLowerCorner();
                    position.at(0) += i * n.getMeshWidth();
                    position.at(1) += j * n.getMeshWidth();
                    position.at(2) += k * n.getMeshWidth();
                    generateBrownianMovement = maxwellBoltzmannDistributedVelocity(n.getBrownianMotionVelocity(), 3);
                    particles.emplace(map_counter, (Particle(position, (n.getInitialVelocity()+generateBrownianMovement), n.getParticleMass(), 0)));
                    map_counter++;
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


