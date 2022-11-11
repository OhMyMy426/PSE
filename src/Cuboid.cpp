#include "Cuboid.h"
#include <array>
#include <iostream>
#include "utils/ArrayUtils.h"

Cuboid::Cuboid(double leftLowerCorner, std::array<double,3> amountOfParticles, 
            double meshWidth, double particleMass, std::array<double,3> initialVelocity, double borwnianMotionVelocity)
            :leftLowerCorner(leftLowerCorner), amountOfParticles(amountOfParticles),meshWidth(meshWidth), particleMass(particleMass),initialVelocity(initialVelocity), borwnianMotionVelocity(getBorwnianMotionVelocity)
    {}


Cuboid::Cuboid(const Cuboid& other) {
    leftLowerCorner = other.leftLowerCorner;
    amountOfParticles = other.amountOfParticles;
    meshWidth = other.meshWidth;
    particleMass = other.particleMass;
    initialVelocity = other.initialVelocity;
    borwnianMotionVelocity = other.borwnianMotionVelocity;
}

Cuboid::~Cuboid() {};


double Cuboid::getLeftLowerCorner() {return leftLowerCorner;}
std::array<double,3>& Cuboid::getAmountOfParticles(){return amountOfParticles};
double Cuboid::getMeshWidth() {return meshWidth;}
double Cuboid::getParticleMass() {return particleMass;}
std::array<double,3>& Cuboid::getInitialVelocity() {return initialVelocity;}
double Cuboid::getBorwnianMotionVelocity() {return borwnianMotionVelocity;}

void Cuboid::setLeftLowerCorner(double parameter) {leftLowerCorner = parameter;}
void Cuboid::getAmountOfParticles(std::array<double,3>& parameter) {amountOfParticles = parameter;}
void Cuboid::getMeshWidth(double parameter) {meshWidth = parameter;}
void Cuboid::getParticleMass(double parameter) {particleMass = parameter;}
void Cuboid::getInitialVelocity(std::array<double,3>& parameter) {initialVelocity = parameter;}
void Cuboid::getBorwnianMotionVelocity(double parameter) {borwnianMotionVelocity = parameter;}


std::string Cuboid::toString() const {
  std::stringstream stream;
  stream << "Cuboid:\n - leftLowerCorner:" << leftLowerCorner << "\n - amountOfParticles: " << amountOfParticles << "\n - meshWidth: " << meshWidth << "\n - particleMass: " << particleMass << "\n - initialVelocity: " << initialVelocity << "\n - borwnianMotionVelocity" << borwnianMotionVelocity;
  return stream.str();
}

bool Cuboid::operator==(Cuboid &other) {
  return (leftLowerCorner == other.leftLowerCorner) && (amountOfParticles == other.amountOfParticles) && (meshWidth == other.meshWidth) &&
         (particleMass == other.particleMass) && (initialVelocity == other.initialVelocity) && (borwnianMotionVelocity == other.borwnianMotionVelocity);
}

std::ostream &operator<<(std::ostream &stream, Cuboid &c) {
  stream << c.toString();
  return stream;
}