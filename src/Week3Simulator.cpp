#include "Week3Simulator.h"
#include "Week3Metadata.h"
#include "LinkedCellContainer2D.h"
#include "Particle.h"
#include "LJCalculator.h"
#include "OutputWriter.h"
#include "spdlog/spdlog.h"
#include <array>
#include <vector>
#include <cmath>
#include "utils/ArrayUtils.h"
#include <bits/stdc++.h>

  Week3Simulator::Week3Simulator() = default;
  Week3Simulator::~Week3Simulator() = default;

/**
 * Runs the entire simulation for week 2. Can benchmark.
 *
 * @param particleContainer the ParticleContainer with the particles to simulate
 * @param week3data The Metadata for the Simulation
 */


void Week3Simulator::runSimulation(LinkedCellContainer2D& linkedCellContainer, Week3Metadata& week3data) {
 //___________________________________________________________________________Setup_____________________________________________________________________
    LJCalculator calculator;
    OutputWriter outputWriter;
    const double start_time = 0;
    double current_time = start_time;
    int iteration = 0;
    char timeSelection = 'Y';
    if (week3data.getOutputChoice() == 'N') timeSelection = 'N';



 

    char reflexMode;
    switch(week3data.getReflectionType()){
        case 'm':
        case 'M':
            reflexMode = 'm';
            break;
        case 'r':
        case 'R':
            reflexMode = 'r';
            break;
        case 'c':
        case 'C':
            reflexMode = 'o'; //originally crossover, but no time to implement rn. Please see the presentation for the idea
            break;
        default: 
            reflexMode = 'o';
    }

    //this particle is here for the reflection method. one initialisation, a lot of bounces
    Particle bounceParticle(0);
    //this is the cutoff for the reflective way
    double cutoff = pow(2, 1/6)*week3data.getSigma() / 2;



   //Setting up time measurement
    auto start = std::chrono::high_resolution_clock::now();






    //_______________________________________________________________________Simulation ________________________________________________________________
    while (current_time < week3data.getEndTime()) {

    //here the crossover way of reflection kicks 

    //calculate new x
    for (auto& x : linkedCellContainer.getLinkedCells()) {
        for (auto& y : x) {
            calculator.calculateX(y, week3data.getDeltaT());
        }
    }

//the remapping -> if a particle is outside his cell, it gets inserted in the one it belongs to and gets erased from the original one
    for(int i = 0; i < (int) linkedCellContainer.getLinkedCells().size(); ++i) {
        for(auto& y: linkedCellContainer.getLinkedCells().at(i)) {
        int Xindex = y.getX().at(0)/linkedCellContainer.getCellSize().at(0); 
        int Yindex = y.getX().at(1)/linkedCellContainer.getCellSize().at(1); 
        if (Xindex + linkedCellContainer.getAmountOfCells().at(0)*Yindex != i) {
            linkedCellContainer.getLinkedCells().at(Xindex + linkedCellContainer.getAmountOfCells().at(0)*Yindex).emplace_front(y); 
            y.setType(-1); 
        }
        }
        auto j = linkedCellContainer.getLinkedCells().at(i).before_begin();
        while (j != linkedCellContainer.getLinkedCells().at(i).end()) {
            auto k = ++j;
            while(k -> getType() == -1) {
                linkedCellContainer.getLinkedCells().at(i).erase_after(j);
            }
            ++j;
        }
    }

    //remapped all particles to the new cells -> here map reflective way kicks
    //check each border individually -> assuming small enough timesteps, there should not be particles in the corners of the halo ring, so we jsut check the sides
    

    //delete the halo cells at this point. every cell needed should be in the border cells, regardless of the boundry condition or mode
    linkedCellContainer.deleteHalo();
    
    //set the f to old_f
    for (auto& x : linkedCellContainer.getLinkedCells()) {
        for (auto& y : x) {
            y.setOldF(y.getF());
            y.setF(std::array<double, 3> {.0,.0,.0});
        }
    }

    //calculate F  
    //DEAR Sam/Fabio, the following method is a bit... hard to read :/ Here is how it works 
    //here the reflective way of reflection kicks
    // we check what cell type we are in. 
    //Halo Cells are ignored
    //normal cells are just handeled like a cell
    //border cells calculate only the needed cells
    //same with the edge cells
    //then a particle is placed that helps with the reflection by mirroring the other particles path and guiding it in a curve (so not a straight "bounce")
    //
    for (int i = 0; i < (int) linkedCellContainer.getLinkedCells().size(); ++i){    
        //we ignore halo cells
         if (std::find(linkedCellContainer.getAllHaloCells().begin(), linkedCellContainer.getAllHaloCells().end(), i) != linkedCellContainer.getAllHaloCells().end()) {
            continue;
         }
         else if (std::find(linkedCellContainer.getCornerCells().begin(), linkedCellContainer.getCornerCells().end(), i) != linkedCellContainer.getCornerCells().end()) {
        //handle Corner Cells
        //left lower corner first
            if (i == linkedCellContainer.getCornerCells().at(0)){
                for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //right
            for (auto& x: linkedCellContainer.getLinkedCells().at(i)){
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            //above
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            //above and right
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            }
            if (week3data.getLeftBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. 
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(0) - linkedCellContainer.getCellSize().at(0));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(0) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
             if (week3data.getLowerBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the lower border, the start of the halo cell below is getCellSize.at(1)-0.000000000000000000000001 ~ getCellSize + 1
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(1) - linkedCellContainer.getCellSize().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
            }
            //right lower corner
            else if (i == linkedCellContainer.getCornerCells().at(1)){
                for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //the other cells:
              for (auto& x: linkedCellContainer.getLinkedCells().at(i))
                {
                //the one above
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                    //above and left
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)-1)){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                }
                if (week3data.getRightBoundary() == 'x' && reflexMode == 'r'){
                 //now the reflective border. 
                    for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                        double distanceToBorder = ((linkedCellContainer.getAmountOfCells().at(0)-2) * linkedCellContainer.getCellSize().at(0) - x.getX().at(0));
                        //if the distance is below the cutoff
                        if (distanceToBorder <= cutoff) {
                            //we place a second particle in the halo, mirrored along the top border and with the same m
                            bounceParticle.setM(x.getM());
                            //init the multiplication
                            std::array<double,3> displacement = {.0,.0,.0};
                            displacement.at(0) = 2*distanceToBorder;
                            bounceParticle.setX(x.getX() + displacement);
                            //calculate the res 
                            calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                        }
                    }
            } 
             if (week3data.getLowerBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the lower border, the start of the halo cell below is getCellSize.at(1)-0.000000000000000000000001 ~ getCellSize + 1
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(1) - linkedCellContainer.getCellSize().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }

            }
            //left upper corner
            else if (i == linkedCellContainer.getCornerCells().at(2)){
                for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //right
            for (auto& x: linkedCellContainer.getLinkedCells().at(i)){
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            }
            if (week3data.getLeftBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. 
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(0) - linkedCellContainer.getCellSize().at(0));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(0) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
            if (week3data.getUpperBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the upper border, the start of the new cell above is (amountOfCells.at(1)-2)*cellsize.at(1)
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (linkedCellContainer.getAmountOfCells().at(1)-2)*linkedCellContainer.getCellSize().at(1)-(x.getX().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() + displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
            }
            //right upper corner
            else if (i == linkedCellContainer.getCornerCells().at(3)){
                for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            if (week3data.getUpperBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the upper border, the start of the new cell above is (amountOfCells.at(1)-2)*cellsize.at(1)
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (linkedCellContainer.getAmountOfCells().at(1)-2)*linkedCellContainer.getCellSize().at(1)-(x.getX().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() + displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
             if (week3data.getRightBoundary() == 'x' && reflexMode == 'r'){
                 //now the reflective border. 
                    for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                        double distanceToBorder = ((linkedCellContainer.getAmountOfCells().at(0)-2) * linkedCellContainer.getCellSize().at(0) - x.getX().at(0));
                        //if the distance is below the cutoff
                        if (distanceToBorder <= cutoff) {
                            //we place a second particle in the halo, mirrored along the top border and with the same m
                            bounceParticle.setM(x.getM());
                            //init the multiplication
                            std::array<double,3> displacement = {.0,.0,.0};
                            displacement.at(0) = 2*distanceToBorder;
                            bounceParticle.setX(x.getX() + displacement);
                            //calculate the res 
                            calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                        }
                    }
            } 
            }

         //handle border cells here   
         }
         else if (std::find(linkedCellContainer.getUpperBorderCells().begin(), linkedCellContainer.getUpperBorderCells().end(), i) != linkedCellContainer.getUpperBorderCells().end()) {
        //handle upper Border Cell -> everything needed is itself and the cell to the right (since we ignore halo cells rn)
            for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //right
            for (auto& x: linkedCellContainer.getLinkedCells().at(i)){
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                    if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                    calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                    }
                }
            }
            if (week3data.getUpperBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the upper border, the start of the new cell above is (amountOfCells.at(1)-2)*cellsize.at(1)
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (linkedCellContainer.getAmountOfCells().at(1)-2)*linkedCellContainer.getCellSize().at(1)-(x.getX().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() + displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
            
         }
         else if (std::find(linkedCellContainer.getLowerBorderCells().begin(), linkedCellContainer.getLowerBorderCells().end(), i) != linkedCellContainer.getLowerBorderCells().end()) {
            //handle lower Border Cell -> nothing really changes but with the reflection
            for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //right
            for (auto& x: linkedCellContainer.getLinkedCells().at(i)){
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                    if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                    calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                    }
                }
            //above
            for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                    if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                    calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                    }
            }
            //above and left
            for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)-1)){
                double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                    if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                    calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                    }
            }
            //above and right
            for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)+1)){
                double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                    if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                    calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                    }
            }
            }
            if (week3data.getLowerBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. since it is the lower border, the start of the halo cell below is getCellSize.at(1)-0.000000000000000000000001 ~ getCellSize + 1
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(1) - linkedCellContainer.getCellSize().at(1));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(1) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
         }
         else if (std::find(linkedCellContainer.getLeftBorderCells().begin(), linkedCellContainer.getLeftBorderCells().end(), i) != linkedCellContainer.getLeftBorderCells().end()) {
            //handle left Border Cell -> everything but left upper cell is important
            for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //right
            for (auto& x: linkedCellContainer.getLinkedCells().at(i)){
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            //above
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
                //above and right
                for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)+1)){
                    double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                }
            }
            if (week3data.getLeftBoundary() == 'x' && reflexMode == 'r'){
            //now the reflective border. 
                for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                    double distanceToBorder = (x.getX().at(0) - linkedCellContainer.getCellSize().at(0));
                    //if the distance is below the cutoff
                    if (distanceToBorder <= cutoff) {
                        //we place a second particle in the halo, mirrored along the top border and with the same m
                        bounceParticle.setM(x.getM());
                        //init the multiplication
                        std::array<double,3> displacement = {.0,.0,.0};
                        displacement.at(0) = 2*distanceToBorder;
                        bounceParticle.setX(x.getX() - displacement);
                        //calculate the res 
                        calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                    }
                }
            }
         }
         
         else if (std::find(linkedCellContainer.getRightBorderCells().begin(), linkedCellContainer.getRightBorderCells().end(), i) != linkedCellContainer.getRightBorderCells().end()) {
            //handle right Border Cell
             for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //the other cells:
              for (auto& x: linkedCellContainer.getLinkedCells().at(i))
                {
                //the one above
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                    //above and left
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)-1)){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                }
                if (week3data.getRightBoundary() == 'x' && reflexMode == 'r'){
                 //now the reflective border. 
                    for (auto& x: linkedCellContainer.getLinkedCells().at(i)) {
                        double distanceToBorder = ((linkedCellContainer.getAmountOfCells().at(0)-2) * linkedCellContainer.getCellSize().at(0) - x.getX().at(0));
                        //if the distance is below the cutoff
                        if (distanceToBorder <= cutoff) {
                            //we place a second particle in the halo, mirrored along the top border and with the same m
                            bounceParticle.setM(x.getM());
                            //init the multiplication
                            std::array<double,3> displacement = {.0,.0,.0};
                            displacement.at(0) = 2*distanceToBorder;
                            bounceParticle.setX(x.getX() + displacement);
                            //calculate the res 
                            calculator.calculateF_LJ(x, bounceParticle, week3data.getSigma(), week3data.getEpsilon());
                        }
                    }
            } 
         }
         else {
            //a "normal" Cell -> calculate Force with others in the cell and the cells to the right, above, left above and right above
            //multiply with all other Particles in the same cell that that particle wasn´t multiplied yet
            for (auto z = linkedCellContainer.getLinkedCells().at(i).begin(); z != linkedCellContainer.getLinkedCells().at(i).end(); ++z)
                {
                for (auto j = ++z; j != linkedCellContainer.getLinkedCells().at(i).end(); ++j)
                 {
                  calculator.calculateF_LJ(*z, *j, week3data.getSigma(), week3data.getEpsilon());
                 }
                }
            //the other cells:
              for (auto& x: linkedCellContainer.getLinkedCells().at(i))
                {
                //the one above
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0))){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                    //above and left
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)-1)){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                    //avove and right
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+linkedCellContainer.getAmountOfCells().at(0)+1)){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                    //right
                    for(auto& y: linkedCellContainer.getLinkedCells().at(i+1)){
                        double distanceToEach = ArrayUtils::L2Norm(x.getX() - y.getX());
                        if (distanceToEach <= linkedCellContainer.getCutoffRadius()) {
                        calculator.calculateF_LJ(x, y, week3data.getSigma(), week3data.getEpsilon(), distanceToEach);
                        }
                    }
                }
            }
         
    }


    
    //calculate v
    for (auto& x : linkedCellContainer.getLinkedCells()) {
        for (auto& y : x) {
            calculator.calculateV(y, week3data.getDeltaT());
        }
    }
    


    //_______________________________________________Output____________________________________________
/*    iteration++;
    if (iteration % 10 == 0 && timeSelection == 'N') {
    outputWriter.VTKOutput(particleContainer, iteration, "Simulation2");
    }*/
    current_time += week3data.getDeltaT();
    }
    

//_______________________________________________End of Simulation_____________________________________
    //if asked, we output the time for the raw Simulation
    auto stop = std::chrono::high_resolution_clock::now();
    if (timeSelection == 'Y') {
    auto endtime_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    auto endtime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    spdlog::info ("Elapsed time in seconds: {} seconds, or {} in milliseconds.", endtime_s, endtime_ms);      
    }

    
}