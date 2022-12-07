#include "Sphere.h"
#include <array>
#include <iostream>
#include "utils/ArrayUtils.h"

Sphere::Sphere(std::array<double,3> centerPoint, double radius,
               double meshWidth, double particleMass, std::array<double,3> initialVelocity, double brownianMotionVelocity, int dimensions)
        :centerPoint(centerPoint), radius(radius), meshWidth(meshWidth), particleMass(particleMass),initialVelocity(initialVelocity), brownianMotionVelocity(brownianMotionVelocity), dimensions(dimensions)
{}


Sphere::Sphere(const Sphere& other) {
    centerPoint = other.centerPoint;
    radius = other.radius;
    meshWidth = other.meshWidth;
    particleMass = other.particleMass;
    initialVelocity = other.initialVelocity;
    brownianMotionVelocity = other.brownianMotionVelocity;
    dimensions = other.dimensions;
}

Sphere::~Sphere() {};


std::array<double,3>& Sphere::getCenterPoint() {return centerPoint;}
double Sphere::getRadius(){return radius;}
double Sphere::getMeshWidth() {return meshWidth;}
double Sphere::getParticleMass() {return particleMass;}
std::array<double,3>& Sphere::getInitialVelocity() {return initialVelocity;}
double Sphere::getBrownianMotionVelocity() {return brownianMotionVelocity;}
int Sphere::getDimensions() {return dimensions;}

void Sphere::setCenterPoint(std::array<double,3>& parameter) {centerPoint = parameter;}
void Sphere::setRadius(double parameter) {radius = parameter;}
void Sphere::setMeshWidth(double parameter) {meshWidth = parameter;}
void Sphere::setParticleMass(double parameter) {particleMass = parameter;}
void Sphere::setInitialVelocity(std::array<double,3>& parameter) {initialVelocity = parameter;}
void Sphere::setBrownianMotionVelocity(double parameter) {brownianMotionVelocity = parameter;}
void Sphere::setDimensions(int parameter) {dimensions = parameter;}


std::string Sphere::toString() const {
    std::stringstream stream;
    stream << "Sphere:\n - Centerpoint:" << "{" << centerPoint.at(0) << " " << centerPoint.at(1) << " " << centerPoint.at(2) << "}" << "\n - Radius: " <<
           radius << "\n - meshWidth: " << meshWidth << "\n - particleMass: " << particleMass << "\n - initialVelocity: " << "{" << initialVelocity.at(0) << " " << initialVelocity.at(1) << " " << initialVelocity.at(2) << "}" << "\n - borwnianMotionVelocity: " << brownianMotionVelocity << "\n - Dimensions: " << dimensions;
    return stream.str();
}

bool Sphere::operator==(Sphere &other) {
    return (centerPoint == other.centerPoint) && (radius == other.radius) && (meshWidth == other.meshWidth) &&
           (particleMass == other.particleMass) && (initialVelocity == other.initialVelocity) && (brownianMotionVelocity == other.brownianMotionVelocity) && (dimensions == other.dimensions);
}

std::ostream &operator<<(std::ostream &stream, Sphere &c) {
    stream << c.toString();
    return stream;
}
