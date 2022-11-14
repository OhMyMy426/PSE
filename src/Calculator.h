#pragma once
#include "Particle.h"


class Calculator {
    public:
    Calculator();
    virtual ~Calculator();

    void calculateX(Particle& firstParicle, double& delta_t);
    void calculateV(Particle& firstParicle, double& delta_t);

};