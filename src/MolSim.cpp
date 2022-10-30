
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX();

/**
 * calculate the position for all particles
 */
void calculateV();

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

constexpr double start_time = 0;
constexpr double end_time = 1000;
constexpr double delta_t = 0.014;

// TODO: what data structure to pick?
std::list<Particle> particles;

int main(int argc, char* argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1]);

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF();
    // calculate new v
    calculateV();

    iteration++;
    if (iteration % 10 == 0) {
      plotParticles(iteration);
    }
    std::cout << "Iteration " << iteration << " finished." << std::endl;

    current_time += delta_t;
  }

  std::cout << "output written. Terminating..." << std::endl;
  return 0;
}

void calculateF() {
  std::list<Particle>::iterator iterator;
  iterator = particles.begin();

  for (auto& p1 : particles) {
    for (auto& p2 : particles) {
      // @TODO: insert calculation of forces here!
    }
  }
}

void calculateX() {
  for (auto& p : particles) {
    // @TODO: insert calculation of position updates here!
    std::array<double, 3> x_arg;
    std::array<double, 3> v_arg;
    for (int i = 0; i < 3;i++) {
      x_arg[i] = p.getX()[i] + delta_t * p.getV()[i] + delta_t * delta_t * p.getF()[i] / 2 * p.getM();
      v_arg[i] = p.getV()[i];
    }
    Particle other(x_arg, v_arg, p.getM(), p.getType());
    p = other;
  }
}

void calculateV() {
    for (auto &p : particles) {
        // @TODO: insert calculation of position updates here!
        std::array<double, 3> f;
        std::array<double, 3> v;
        int c=0;
        for (c = 0; c < f.size(); c++) {
            f[c] = p.getF()[c] + p.getOldF()[c];
        }
        int i=0;
        for (i= 0; i < f.size(); i++) {
            v[c] = p.getV()[i]+(delta_t*(f[i]/(2*p.getM())));
        }
        p.setv(v);
    }
}

void plotParticles(int iteration) {

  std::string out_name("MD_vtk");

  outputWriter::XYZWriter writer;
  writer.plotParticles(particles, out_name, iteration);
}
