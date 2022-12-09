#include "Calculator.h"
#include "Particle.h"
#include "utils/ArrayUtils.h"
#include <iostream>

Calculator::Calculator() = default;

Calculator::~Calculator() = default;

/**
 * Calculate the Location of a particle using the Velocity-Störmer-Verlet-Algorithm.
 *
 * @param firstParticle The particle for which the calculation should happen
 * @param delta_t The delta_t for the calculation.
 */

void Calculator::calculateX(Particle& firstParticle, double& delta_t) {
    std::array<double, 3> new_x_to_calculate;
    for (int j = 0; j < 3; ++j) {
        new_x_to_calculate.at(j) = firstParticle.getX().at(j) + delta_t * firstParticle.getV().at(j) + (delta_t * delta_t) * firstParticle.getF().at(j)/(2 * firstParticle.getM());
    }
    firstParticle.setX(new_x_to_calculate);
}

/**
 * Calculate the velocity of a particle using the Velocity-Störmer-Verlet-Algorithm.
 *
 * @param firstParticle The particle for which the calculation should happen
 * @param delta_t The delta_t for the calculation.
 */
void Calculator::calculateV(Particle& firstParticle, double& delta_t) {
    std::array<double, 3> added_forces;
    std::array<double, 3> new_v_to_calculate;

    added_forces = firstParticle.getF() + firstParticle.getOldF();
    for (size_t i = 0; i < 3; i++) {
            new_v_to_calculate.at(i) = firstParticle.getV().at(i) + (delta_t * (added_forces.at(i) / (2 * firstParticle.getM())));
        }
    firstParticle.setV(new_v_to_calculate);
}

