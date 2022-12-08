#pragma once


class Week3Metadata {
private:
/**
 * The end_time for the simulation
 */
    double end_time;
/**
 * The delta_t for the simulation
 */
    double delta_t; 
/**
 * The epsilon for the simulation
 */    
    double epsilon; 
/**
 * The sigma for the simulation
 */
    double sigma;
/**
 * The boundary condition for the upper boundary. Allowed are 'o' (outflow), 'x' (reflective)
 */
    char upperBoundary;
/**
 * The boundary condition for the lower boundary. Allowed are 'o' (outflow), 'x' (reflective)
 */
    char lowerBoundary;
/**
 * The boundary condition for the left boundary. Allowed are 'o' (outflow), 'x' (reflective)
 */
    char leftBoundary;
/**
 * The boundary condition for the right boundary. Allowed are 'o' (outflow), 'x' (reflective)
 */
    char rightBoundary;
/**
 * The type of reflection. Allowed are 'r' (reflective), 'c' (crossover), 'm' (map). Everything else will go as outflow
 */
    char reflectionType;
/**
 * The choice of time measurement or not. Allowed are 'Y' and 'N', failure will result in time measurement (since faster than output)
 */
    char outputChoice;

public:
    Week3Metadata(double end_time_arg, double delta_t_arg, double epsilon_arg, double sigma_arg, char upperBoundary_arg, char lowerBoundary_arg, char leftBoundary_arg, char rightBoundary_arg, char type_arg, char output_arg);
    Week3Metadata();
    virtual ~Week3Metadata();

    double& getEndTime();
    double& getDeltaT();
    double& getEpsilon();
    double& getSigma();
    char getUpperBoundary();
    char getLowerBoundary();
    char getLeftBoundary();
    char getRightBoundary();
    char getReflectionType();
    char getOutputChoice();
    void setEndTime(double param);
    void setDeltaT(double param);
    void setEpsilon(double param);
    void setSigma(double param);
    void setUpperBoundary(char param);
    void setLowerBoundary(char param);
    void setLeftBoundary(char param);
    void setRightBoundary(char param);
    void setReflectionType(char param);
    void setOutputChoice(char param);
 
};
