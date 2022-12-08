#include "LinkedCellContainer2D.h"
#include <forward_list>
#include <array>
#include <vector>
#include "Particle.h"
#include "utils/ArrayUtils.h"
#include <memory>
#include <algorithm>
#include <iostream>


/*
for indexing in the 3D Space represented as a 1D vector, we use x, y, z (Dimensions of the cube after adding the holo cells)
a row in x direction is just 0 < i < x
to iterate in y direction, you use 0 < i*x < y
to iterate in z direction, you use 0 < i*x*y < z
so a random Cell in the middle of the Cube is defined by a (x-axis) + b*x (y-axis) + c*x*y (z-axis)
*/


//helper functions
double resize(int domainSizePart, double cutoff) {
    //amount of cells as integer
    int resultingSizeInt = (int) (domainSizePart / cutoff);   
    //amount of cells as double
    double resultingSizeDouble = domainSizePart/cutoff;
    //if they are equal, we can return the cutoff as domainSize in that direction
    if(resultingSizeDouble == resultingSizeInt) return cutoff;
    //if not, we need to spread the rest to the different cells equally
    else {
        cutoff += (domainSizePart - resultingSizeInt*cutoff)/resultingSizeInt;
        return cutoff;
    }


}

//default constructor/destrucor
LinkedCellContainer2D::LinkedCellContainer2D() = default;
LinkedCellContainer2D::~LinkedCellContainer2D() = default;

//extra constructors
LinkedCellContainer2D::LinkedCellContainer2D(std::array<double, 3>& domainsize_arg, double cutoffRadius_arg):
    linkedCells({}), domainSize(domainsize_arg), cutoffRadius(cutoffRadius_arg), amountOfCells ({0,0,0}), cellSize({.0,.0,.0}), upperBorderCells({}), lowerBorderCells({}), leftBorderCells({}), rightBorderCells({}), cornerCells({})
    {
            for (int i = 0; i < 2; i++)
            {
            cellSize.at(i) = resize(domainSize.at(i), cutoffRadius);
            amountOfCells.at(i) = (int) domainSize.at(i)/cellSize.at(i)+2; //+2 for the halo cells
            }
            //2D, so just 1 layer of cells
            amountOfCells.at(2) = 1;
            cellSize.at(2) = 0;
            //we adjust the stored domainSize to include the halo cells -> now on each end of the quader, halo cells got added the size of normal cells
            domainSize = domainSize + 2*cellSize;
            //resize the linked cell vector to the needed size
            linkedCells.resize((int) (amountOfCells.at(0)*amountOfCells.at(1)));
            //initialise the vector with linked lists
            for(auto& v : linkedCells) {
                v = std::forward_list<Particle>();
            }
            cornerHaloCells.reserve(4);
            cornerHaloCells.emplace_back(0);
            cornerHaloCells.emplace_back(amountOfCells.at(0)-1);
            cornerHaloCells.emplace_back(amountOfCells.at(0)*(amountOfCells.at(1)-1));
            cornerHaloCells.emplace_back(amountOfCells.at(1)*amountOfCells.at(0) - 1);

            
            //get the halo cell indexes
            for (int j = 1; j < amountOfCells.at(0)-1; ++j)
                { 
                    lowerHaloCells.emplace_back(j);//first row
                    upperHaloCells.emplace_back((amountOfCells.at(1)-1)+j);//last row
                }
            for (int j = 1; j < amountOfCells.at(1)-1; ++j)
                { 
                    leftHaloCells.emplace_back(j*amountOfCells.at(0));//left row
                    rightHaloCells.emplace_back(j*amountOfCells.at(0)+(amountOfCells.at(0)-1));//right row
                }
            
            allHaloCells.reserve((int) upperHaloCells.size() + lowerHaloCells.size() + leftHaloCells.size() + rightHaloCells.size() + cornerHaloCells.size());

            for (auto x : upperHaloCells) {
                allHaloCells.emplace_back(x);
            }
            for (auto x : lowerHaloCells) {
                allHaloCells.emplace_back(x);
            }
            for (auto x : leftHaloCells) {
                allHaloCells.emplace_back(x);
            }
            for (auto x : rightHaloCells) {
                allHaloCells.emplace_back(x);
            }
            for (auto x : cornerHaloCells) {
                allHaloCells.emplace_back(x);
            }
            
            //now we search the indexes of the border cells. we differenciate the borders for different behaviour
            //lower border and upper border
            lowerBorderCells.reserve(amountOfCells.at(0)-4);
            upperBorderCells.reserve(amountOfCells.at(0)-4);
            for(int i = 2; i < amountOfCells.at(0)-2; ++i) 
                {
                    lowerBorderCells.emplace_back(i+(amountOfCells.at(0)));
                    upperBorderCells.emplace_back(i+(amountOfCells.at(0)*((amountOfCells.at(1)-2))));                
                }
            //right and left border cells
            lowerBorderCells.reserve(amountOfCells.at(1)-4);
            upperBorderCells.reserve(amountOfCells.at(1)-4);
            for(int i = 2; i < amountOfCells.at(1)-2; ++i) 
                {
                    leftBorderCells.emplace_back(1+i*amountOfCells.at(0));
                    rightBorderCells.emplace_back(8+i*amountOfCells.at(0));                
                }
            //Corners 
            //------------------ NOTE!!!!!!!-------------------- the order is important -> where can the particle have come from!!!!!!
            cornerCells.reserve(4);
            cornerCells.emplace_back(amountOfCells.at(0)+1);
            cornerCells.emplace_back(amountOfCells.at(0)+(amountOfCells.at(0)-2));
            cornerCells.emplace_back((amountOfCells.at(1)-2)*amountOfCells.at(0)+1);
            cornerCells.emplace_back((amountOfCells.at(1)-2)*amountOfCells.at(0)+(amountOfCells.at(0)-2));
        
    }


//getters and setters
std::vector<std::forward_list<Particle>>& LinkedCellContainer2D::getLinkedCells(){return linkedCells;}
std::array<double,3>& LinkedCellContainer2D::getDomainSize(){return domainSize;}
std::array<int, 3>& LinkedCellContainer2D::getAmountOfCells(){return amountOfCells;}
double LinkedCellContainer2D::getCutoffRadius() const{return cutoffRadius;}
std::array<double, 3>& LinkedCellContainer2D::getCellSize() {return cellSize;}
std::vector<int>& LinkedCellContainer2D::getUpperHaloCells(){return upperHaloCells;}
std::vector<int>& LinkedCellContainer2D::getLowerHaloCells(){return lowerHaloCells;}
std::vector<int>& LinkedCellContainer2D::getLeftHaloCells(){return leftHaloCells;}
std::vector<int>& LinkedCellContainer2D::getRightHaloCells(){return rightHaloCells;}
std::vector<int>& LinkedCellContainer2D::getCornerHaloCells(){return cornerHaloCells;}
std::vector<int>& LinkedCellContainer2D::getAllHaloCells(){return allHaloCells;}
std::vector<int>& LinkedCellContainer2D::getUpperBorderCells(){return upperBorderCells;}
std::vector<int>& LinkedCellContainer2D::getLowerBorderCells(){return lowerBorderCells;}
std::vector<int>& LinkedCellContainer2D::getLeftBorderCells(){return leftBorderCells;}
std::vector<int>& LinkedCellContainer2D::getRightBorderCells(){return rightBorderCells;}
std::vector<int>& LinkedCellContainer2D::getCornerCells(){return cornerCells;}
void LinkedCellContainer2D::setLinkedList(std::vector<std::forward_list<Particle>>& parameter){linkedCells = parameter;}
void LinkedCellContainer2D::setDomainSize(std::array<double, 3>& parameter){domainSize = parameter;}
void LinkedCellContainer2D::setAmountOfCells(std::array<int, 3> &parameter) {amountOfCells = parameter;}
void LinkedCellContainer2D::setCutoffRadius(double parameter){cutoffRadius = parameter;}
void LinkedCellContainer2D::setCellSize(std::array<double, 3>& parameter) {cellSize = parameter;}

/**
 * @brief Cleaers all the Particles in the HaloCells
 * 
 */
void LinkedCellContainer2D::deleteUpperHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(upperHaloCells.begin(), upperHaloCells.end(), i) != upperHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}
void LinkedCellContainer2D::deleteLowerHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(lowerHaloCells.begin(), lowerHaloCells.end(), i) != lowerHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}
void LinkedCellContainer2D::deleteLeftHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(leftHaloCells.begin(), leftHaloCells.end(), i) != leftHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}
void LinkedCellContainer2D::deleteRightHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(rightHaloCells.begin(), rightHaloCells.end(), i) != rightHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}
void LinkedCellContainer2D::deleteCornerHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(cornerHaloCells.begin(), cornerHaloCells.end(), i) != cornerHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}

void LinkedCellContainer2D::deleteHalo() {
    for(int i = 0; i < (int) linkedCells.size(); ++i) {
         if (std::find(allHaloCells.begin(), allHaloCells.end(), i) != allHaloCells.end()) {
            linkedCells.at(i).clear();
        }
    }
}

/**
 * @brief adds the Generated Particles to the LinkedCell list, enabeling the linkedCellMethod
 * 
 * @param particleVector The vector with the particles generated by the Generator
 */
void LinkedCellContainer2D::initialiseCells(std::vector<Particle>& particleVector) {
    for (int i = 0; i < (int) particleVector.size(); ++i)
    {
        Particle& particleToMap = particleVector.at(i);
        particleToMap.setX(particleToMap.getX()+cellSize);      //set the index in a coordinate system with the left lower halo cell corner as 0/0
        int Xindex = particleToMap.getX().at(0)/cellSize.at(0); // the x - index of the particle, after halo cells
        int Yindex = particleToMap.getX().at(1)/cellSize.at(1); // the y-index of the particle, after halo cells
        linkedCells.at(Xindex + amountOfCells.at(0)*Yindex).emplace_front(particleToMap);//add the particle to the corresponding forward list
    }
    
}

