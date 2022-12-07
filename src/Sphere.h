#pragma once
#include <array>
#include<iostream>


//Author: Alex
//This is a class that was made to get and store the input for the second Task of PSE.

class Sphere {
private:
    /**
     * The coordinates of the left lower corner
     */
    std::array<double,3> centerPoint;
    /**
    * The amout of particles in the cuboid along the radius
    */
    double radius;
    /**
     * The meshWidth of the Particles in the Cuboid
     */
    double meshWidth;
    /**
     * The mass of a single particle. All particlemasses are the same in one cuboid
     */
    double particleMass;
    /**
     * The initial velocity of the particles
     */
    std::array<double,3> initialVelocity;
    /**
     * The average for the calculation of the brownian motion for the particles
     */
    double brownianMotionVelocity;
    /**
     * The amount of dimensions of the Simulation for this Cuboid. 2 or 3
     */
    int dimensions;


public:
    Sphere(const Sphere& other);
    Sphere(std::array<double,3> centerPoint, double radius,
           double meshWidth, double particleMass, std::array<double,3> initialVelocity, double brownianMotionVelocity, int dimensions);
    virtual ~Sphere();

    std::array<double,3>& getCenterPoint();
    double getRadius();
    double getMeshWidth();
    double getParticleMass();
    std::array<double,3>& getInitialVelocity();
    double getBrownianMotionVelocity();
    int getDimensions();

    void setCenterPoint(std::array<double,3>& parameter);
    void setRadius(double parameter);
    void setMeshWidth(double parameter);
    void setParticleMass(double parameter);
    void setInitialVelocity(std::array<double,3>& parameter);
    void setBrownianMotionVelocity(double parameter);
    void setDimensions(int parameter);

    bool operator==(Sphere &other);

    std::string toString() const;
};

std::ostream &operator<<(std::ostream &stream, Sphere &p);