#include "Week3Metadata.h"

    Week3Metadata::Week3Metadata(double end_time_arg, double delta_t_arg, double epsilon_arg, double sigma_arg, char upperBoundary_arg, char lowerBoundary_arg, char leftBoundary_arg, char rightBoundary_arg, char type_arg, char output_arg) :
        end_time(end_time_arg), delta_t(delta_t_arg), epsilon(epsilon_arg), sigma (sigma_arg), upperBoundary(upperBoundary_arg), lowerBoundary(lowerBoundary_arg), leftBoundary(leftBoundary_arg), rightBoundary(rightBoundary_arg), reflectionType (type_arg), outputChoice(output_arg)
        {}
    Week3Metadata::Week3Metadata() = default;
    Week3Metadata::~Week3Metadata() = default;

    double& Week3Metadata::getEndTime() {return end_time;}
    double& Week3Metadata::getDeltaT() {return delta_t;}
    double& Week3Metadata::getEpsilon() {return epsilon;}
    double& Week3Metadata::getSigma() {return sigma;}
    char Week3Metadata::getUpperBoundary() {return upperBoundary;}
    char Week3Metadata::getLowerBoundary() {return lowerBoundary;}
    char Week3Metadata::getLeftBoundary() {return leftBoundary;}
    char Week3Metadata::getRightBoundary() {return rightBoundary;}
    char Week3Metadata::getReflectionType() {return reflectionType;}
    char Week3Metadata::getOutputChoice() {return outputChoice;}
    void Week3Metadata::setEndTime(double param) {end_time = param;}
    void Week3Metadata::setDeltaT(double param) {delta_t = param;}
    void Week3Metadata::setEpsilon(double param) {epsilon = param;}
    void Week3Metadata::setSigma(double param) {sigma = param;}
    void Week3Metadata::setUpperBoundary(char param) {upperBoundary = param;}
    void Week3Metadata::setLowerBoundary(char param) {lowerBoundary = param;}
    void Week3Metadata::setLeftBoundary(char param) {leftBoundary = param;}
    void Week3Metadata::setRightBoundary(char param) {rightBoundary = param;}
    void Week3Metadata::setReflectionType(char param) {reflectionType = param;}
    void Week3Metadata::setOutputChoice(char param) {outputChoice = param;}