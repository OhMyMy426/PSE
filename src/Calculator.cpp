#include "Calculator.h"
#include "Particle.h"
#include "utils/ArrayUtils.h"

Calculator::Calculator() = default;

Calculator::~Calculator() = default;

void Calculator::calculateX(Particle& firstParticle, double& delta_t) {
    std::array<double, 3> new_x_to_calculate;
    for (int j = 0; j < 3; ++j) {
        new_x_to_calculate.at(j) = firstParticle.getX().at(j) + delta_t * firstParticle.getV().at(j) + (delta_t * delta_t) * firstParticle.getF().at(j)/(2 * firstParticle.getM());
    }
    firstParticle.setX(new_x_to_calculate);
}

void Calculator::calculateV(Particle& firstParticle, double& delta_t) {
    std::array<double, 3> added_forces;
    std::array<double, 3> new_v_to_calculate;

    added_forces = firstParticle.getF() + firstParticle.getOldF();
    for (size_t i = 0; i < 3; i++) {
            new_v_to_calculate[i] = firstParticle.getV().at(i) + (delta_t * (added_forces[i] / (2 * firstParticle.getM())));
        }
}

