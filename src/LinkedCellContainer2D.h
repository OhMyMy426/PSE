#pragma once
#include <vector>
#include <array>
#include <forward_list>
#include "Particle.h"


class LinkedCellContainer2D {
private:
    /**
   * The linked cells used for the calculations
   */
    std::vector<std::forward_list<Particle>> linkedCells;
    /**
   * The domainsize: might be adapted at initialisation dependent on the constructor
   */
    std::array<double, 3> domainSize;
    /**
   * The cutoff radius as given by input
   */
    double cutoffRadius;
    /**
   * The the amount of cells in x y z direction
   */
    std::array<int,3> amountOfCells;
    /**
   * The size of a single cell in x y z direction
   */
    std::array<double, 3> cellSize;
    /**
   * The indexes of the halo cells and all halo cells
   */
    std::vector<int> upperHaloCells;
    std::vector<int> lowerHaloCells;
    std::vector<int> leftHaloCells;
    std::vector<int> rightHaloCells;
    std::vector<int> cornerHaloCells;
    std::vector<int> allHaloCells;
    /**
   * The indexes of the border cells
   */
    std::vector<int> upperBorderCells;
    std::vector<int> lowerBorderCells;
    std::vector<int> leftBorderCells;
    std::vector<int> rightBorderCells;
    std::vector<int> cornerCells;

public:
    LinkedCellContainer2D();
    LinkedCellContainer2D(std::array<double, 3>& domainsize_arg, double cutoffRadius_arg);
    virtual ~LinkedCellContainer2D();
    std::vector<std::forward_list<Particle>>& getLinkedCells();
    std::array<double, 3>& getDomainSize();
    double getCutoffRadius() const;
    std::array<double, 3>& getCellSize();
    std::array<int, 3>& getAmountOfCells();
    std::vector<int>& getUpperHaloCells();
    std::vector<int>& getLowerHaloCells();
    std::vector<int>& getLeftHaloCells();
    std::vector<int>& getRightHaloCells();
    std::vector<int>& getCornerHaloCells();
    std::vector<int>& getAllHaloCells();
    std::vector<int>& getUpperBorderCells();
    std::vector<int>& getLowerBorderCells();
    std::vector<int>& getLeftBorderCells();
    std::vector<int>& getRightBorderCells();
    std::vector<int>& getCornerCells();
    void setLinkedList(std::vector<std::forward_list<Particle>>& parameter);
    void setDomainSize(std::array<double, 3>& parameter);
    void setAmountOfCells(std::array<int, 3>& parameter);
    void setCutoffRadius(double parameter);
    void setCellSize(std::array<double, 3>& parameter);
    
    //utility methods
    void deleteUpperHalo();
    void deleteLowerHalo();
    void deleteLeftHalo();
    void deleteRightHalo();
    void deleteCornerHalo();
    void deleteHalo();
    
    void initialiseCells(std::vector<Particle>& particleVector);
};

