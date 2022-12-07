#include "LJCalculator.h"
#include "Particle.h"
#include "utils/ArrayUtils.h"
#include <cmath>

LJCalculator::LJCalculator() = default;

LJCalculator::~LJCalculator() = default;

/**
 * Calcuaate the force between two particles with the Lennard-Jones-Potential and add the result on both particles according to Newtons III. law 
 *
 * @param firstParticle The first particle for the force calculation
 * @param secondParticle The second particle for the force calculation
 * @param sigma The sigma for the LJ-Potential
 * @param epsilon The epsilon for the LJ-Potential
 */

void LJCalculator::calculateF_LJ(Particle& firstParticle, Particle& secondParticle, double& sigma, double& epsilon) {
    //the l2 Norm of x_i - x_j, since it is frequently used
    double l2Norm = ArrayUtils::L2Norm(firstParticle.getX()-secondParticle.getX());
    //the sixth Power of sigma diveded through the l2-norm above
    double calculation_step = pow((sigma/l2Norm), 6);
    //the Force F_ij
    std::array<double, 3> calculated_force = ((-24*epsilon)/pow(l2Norm, 2))*(calculation_step-2*pow(calculation_step, 2))*(firstParticle.getX()-secondParticle.getX()); 

    //adding the force with correct sign on the Particles
    firstParticle.setF(firstParticle.getF()+calculated_force);
    secondParticle.setF(secondParticle.getF()-calculated_force);
}

void LJCalculator::calculateF_LJ(Particle& firstParticle, Particle& secondParticle, double& sigma, double& epsilon, double& L2Norm) {
    //the sixth Power of sigma diveded through the l2-norm above
    double calculation_step = pow((sigma/L2Norm), 6);
    //the Force F_ij
    std::array<double, 3> calculated_force = ((-24*epsilon)/pow(L2Norm, 2))*(calculation_step-2*pow(calculation_step, 2))*(firstParticle.getX()-secondParticle.getX()); 

    //adding the force with correct sign on the Particles
    firstParticle.setF(firstParticle.getF()+calculated_force);
    secondParticle.setF(secondParticle.getF()-calculated_force);
  }
