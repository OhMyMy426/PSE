#pragma once
#include <array>
//Author: Alex
//This is a class that was made to get and store the input for the second Task of PSE.

class Cuboid {
private:
    std::array<double,3> leftLowerCorner;                     //The coordinate of the lower left front-side corner
    std::array<int,3> amountOfParticles;     //Number of particles per dimension: N1 × N2 × N3
    double meshWidth;                           //Distance h of the particles (mesh width of the grid)
    double particleMass;                        //Mass m of one particle
    std::array<double,3> initialVelocity;       //Initial velocity v of the particles (3 Components)
    double brownianMotionVelocity;              //The mean-value of the velocity of the Brownian Motion
    int dimensions;


public:
    Cuboid(const Cuboid& other);
    Cuboid(std::array<double,3> leftLowerCorner, std::array<int,3> amountOfParticles, 
            double meshWidth, double particleMass, std::array<double,3> initialVelocity, double brownianMotionVelocity, int dimensions);
    virtual ~Cuboid();

    std::array<double,3>& getLeftLowerCorner();
    std::array<int,3>& getAmountOfParticles();
    double getMeshWidth();
    double getParticleMass();
    std::array<double,3>& getInitialVelocity();
    double getBrownianMotionVelocity();
    int getDimensions();

    void setLeftLowerCorner(std::array<double,3>& parameter);
    void setAmountOfParticles(std::array<int,3>& parameter);
    void setMeshWidth(double parameter);
    void setParticleMass(double parameter);
    void setInitialVelocity(std::array<double,3>& parameter);
    void setBrownianMotionVelocity(double parameter);
    void setDimensions(int parameter);

    bool operator==(Cuboid &other);

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &stream, Cuboid &p);