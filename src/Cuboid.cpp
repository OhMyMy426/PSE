#include "Cuboid.h"
#include <array>
#include <iostream>
#include "utils/ArrayUtils.h"

Cuboid::Cuboid(std::array<double,3> leftLowerCorner, std::array<int,3> amountOfParticles, 
            double meshWidth, double particleMass, std::array<double,3> initialVelocity, double brownianMotionVelocity, int dimensions)
            :leftLowerCorner(leftLowerCorner), amountOfParticles(amountOfParticles),meshWidth(meshWidth), particleMass(particleMass),initialVelocity(initialVelocity), brownianMotionVelocity(brownianMotionVelocity), dimensions(dimensions)
    {}


Cuboid::Cuboid(const Cuboid& other) {
    leftLowerCorner = other.leftLowerCorner;
    amountOfParticles = other.amountOfParticles;
    meshWidth = other.meshWidth;
    particleMass = other.particleMass;
    initialVelocity = other.initialVelocity;
    brownianMotionVelocity = other.brownianMotionVelocity;
    dimensions = other.dimensions;
}

Cuboid::~Cuboid() {};


std::array<double,3>& Cuboid::getLeftLowerCorner() {return leftLowerCorner;}
std::array<int,3>& Cuboid::getAmountOfParticles(){return amountOfParticles;}
double Cuboid::getMeshWidth() {return meshWidth;}
double Cuboid::getParticleMass() {return particleMass;}
std::array<double,3>& Cuboid::getInitialVelocity() {return initialVelocity;}
double Cuboid::getBrownianMotionVelocity() {return brownianMotionVelocity;}
int Cuboid::getDimensions() {return dimensions;}

void Cuboid::setLeftLowerCorner(std::array<double,3>& parameter) {leftLowerCorner = parameter;}
void Cuboid::setAmountOfParticles(std::array<int,3>& parameter) {amountOfParticles = parameter;}
void Cuboid::setMeshWidth(double parameter) {meshWidth = parameter;}
void Cuboid::setParticleMass(double parameter) {particleMass = parameter;}
void Cuboid::setInitialVelocity(std::array<double,3>& parameter) {initialVelocity = parameter;}
void Cuboid::setBrownianMotionVelocity(double parameter) {brownianMotionVelocity = parameter;}
void Cuboid::setDimensions(int parameter) {dimensions = parameter;}


std::string Cuboid::toString() const {
  std::stringstream stream;
  stream << "Cuboid:\n - leftLowerCorner:" << "{" << leftLowerCorner.at(0) << " " << leftLowerCorner.at(1) << " " << leftLowerCorner.at(2) << "}" << "\n - amountOfParticles: " << 
   "{" << amountOfParticles.at(0) << " " << amountOfParticles.at(1) << " " << amountOfParticles.at(2) << "}" << "\n - meshWidth: " << meshWidth << "\n - particleMass: " << particleMass << "\n - initialVelocity: " << "{" << initialVelocity.at(0) << " " << initialVelocity.at(1) << " " << initialVelocity.at(2) << "}" << "\n - borwnianMotionVelocity: " << brownianMotionVelocity << "\n - Dimensions: " << dimensions;
  return stream.str();
}

bool Cuboid::operator==(Cuboid &other) {
  return (leftLowerCorner == other.leftLowerCorner) && (amountOfParticles == other.amountOfParticles) && (meshWidth == other.meshWidth) &&
         (particleMass == other.particleMass) && (initialVelocity == other.initialVelocity) && (brownianMotionVelocity == other.brownianMotionVelocity) && (dimensions == other.dimensions);
}

std::ostream &operator<<(std::ostream &stream, Cuboid &c) {
  stream << c.toString();
  return stream;
}