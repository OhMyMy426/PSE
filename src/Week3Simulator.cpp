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
    if (week3data.getOutputChoice == 'N') timeSelection = 'N';



    //Setting up time measurement
    auto start = std::chrono::high_resolution_clock::now();

    char reflexMode;
    switch(week3data.getReflectionType){
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
            reflexMode = 'c';
            break;
        default: 
            reflexMode = 'o';
    }

    //this particle is here for the reflection method. one initialisation, a lot of bounces
    Particle bounceParticle(0);
    //this is the cutoff for the reflective way
    double cutoff = pow(2, 1/6)*week3data.getSigma() / 2;





    //_______________________________________________________________________Simulation ________________________________________________________________
    while (current_time < end_time) {

    //here the crossover way of reflection kicks 

    //calculate new x
    for (auto x& : linkedCellContainer.getLinkedCells()) {
        for (auto y& : x) {
            calculator.calculateX(x, week3data.getDeltaT());
        }
    }

    //remap all particles to the new cells -> here map reflective way kicks

    //delete the halo cells at this point. every cell needed should be in the border cells, regardless of the boundry condition or mode
    linkedCellContainer.deleteHalo();
    
    //set the f to old_f
    for (auto x& : linkedCellContainer.getLinkedCells()) {
        for (auto y& : x) {
            y.setOldF(y.getF());
            y.setF(std::array<double, 3> {.0,.0,.0});
        }
    }

    //calculate F   
    //here the reflective way of reflection kicks
    for (int i = 0; (int) i < linkedCellContainer.getLinkedCells().size(); ++i){    
        //we ignore halo cells
         if (std::find(linkedCellContainer.getAllHaloCells().begin(), linkedCellContainer.getAllHaloCells().end(), i) != linkedCellContainer.getAllHaloCells().end()) {
            continue;
         }
         else if (std::find(linkedCellContainer.getCornerCells().begin(), linkedCellContainer.getCornerCells().end(), i) != linkedCellContainer.getCornerCells().end()) {
            //handle Corner Cell
         }
         else if (std::find(linkedCellContainer.getUpperBorderCells().begin(), linkedCellContainer.getUpperBorderCells().end(), i) != linkedCellContainer.getUpperBorderCells().end()) {
            //handle Border Cell
         }
         else if (std::find(linkedCellContainer.getLowerBorderCells().begin(), linkedCellContainer.getLowerBorderCells().end(), i) != linkedCellContainer.getLowerBorderCells().end()) {
            //handle Border Cell
         }
         else if (std::find(linkedCellContainer.getLeftBorderCells().begin(), linkedCellContainer.getLeftBorderCells().end(), i) != linkedCellContainer.getLeftBorderCells().end()) {
            //handle Border Cell
         }
         else if (std::find(linkedCellContainer.getRightBorderCells().begin(), linkedCellContainer.getRightBorderCells().end(), i) != linkedCellContainer.getRightBorderCells().end()) {
            //handle Border Cell
         }
         else {
            //a "normal" Cell -> calculate Force with others in the cell and the cells to the right, above and to the right above
         }

         
    }


    
    //calculate v
    for (auto x& : linkedCellContainer.getLinkedCells()) {
        for (auto y& : x) {
            calculator.calculateV(x, week3data.getDeltaT());
        }
    }
    


    //_______________________________________________Output____________________________________________
    iteration++;
    if (iteration % 10 == 0 && timeSelection == 'N') {
    outputWriter.VTKOutput(particleContainer, iteration, "Simulation2");
    }
    current_time += delta_t;
    }


    //if asked, we output the time for the raw Simulation
    auto stop = std::chrono::high_resolution_clock::now();
    if (timeSelection == 'Y') {
    auto endtime_s = std::chrono::duration_cast<std::chrono::seconds>(stop - start).count();
    auto endtime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    spdlog::info ("Elapsed time in seconds: {} seconds, or {} in milliseconds.", endtime_s, endtime_ms);      
    }

  
}