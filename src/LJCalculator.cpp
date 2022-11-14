#include "LJCalculator.h"
#include "Particle.h"
#include "utils/ArrayUtils.h"
#include <cmath>

LJCalculator::LJCalculator() = default;

LJCalculator::~LJCalculator() = default;

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