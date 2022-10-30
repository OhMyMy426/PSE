
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

#include <unordered_map>
#include "ParticleContainer.h"

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF_easy(ParticleContainer &particleContainer);

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
std::unordered_map<int, Particle> particles;
int particle_counter = 0;

int main(int argc, char *argsv[]) {

  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (argc != 2) {
    std::cout << "Erroneous programme call! " << std::endl;
    std::cout << "./molsym filename" << std::endl;
  }

  FileReader fileReader;
  fileReader.readFile(particles, argsv[1], particle_counter);
  ParticleContainer particleContainer(particles, particle_counter);
  

  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    // calculate new x
    calculateX();
    // calculate new f
    calculateF_easy(particleContainer);
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

void calculateF_easy(ParticleContainer &particleContainer) {
    particleContainer.getParticles().at(0).setOldF(particleContainer.getParticles().at(0).getF());
    particleContainer.getParticles().at(0).setF({ 0.,0.,0. });


    for (int i = 0; i <= particleContainer.getParticle_counter() / 2; ++i)
    {
        for (int j = i + 1; j <= particleContainer.getParticle_counter(); ++j) {
            if (i == 1) {
                particleContainer.getParticles().at(j).setOldF(particleContainer.getParticles().at(j).getF());
                particleContainer.getParticles().at(j).setF({ 0.,0.,0. });

            }
            std::array<double, 3> tmpX = { particleContainer.getParticles().at(i).getX().at(0) - particleContainer.getParticles().at(j).getX().at(0),
                                          particleContainer.getParticles().at(i).getX().at(1) - particleContainer.getParticles().at(j).getX().at(1),
                                          particleContainer.getParticles().at(i).getX().at(2) - particleContainer.getParticles().at(j).getX().at(2)
            };
            double tmpM = particleContainer.getParticles().at(j).getM() * particleContainer.getParticles().at(i).getM();
            double tmpdist = sqrt(tmpX.at(0) * tmpX.at(0) + tmpX.at(1) * tmpX.at(1) + tmpX.at(2) * tmpX.at(2));
            tmpdist = tmpdist * tmpdist * tmpdist;
            for (auto a : tmpX) {
                a = -a;
            }
            particleContainer.getParticles().at(i).setF(particleContainer.getParticles().at(i).getF() + (tmpM/tmpdist)*tmpX);
            particleContainer.getParticles().at(j).setF(particleContainer.getParticles().at(j).getF() - (tmpM / tmpdist) * tmpX);

        }
    }
}

void calculateX() {
  for (auto &p : particles) {
    // @TODO: insert calculation of position updates here!
  }
}

void calculateV() {
  for (auto &p : particles) {
    // @TODO: insert calculation of veclocity updates here!
  }
}

void plotParticles(int iteration) {

  std::string out_name("MD_vtk");

  

  outputWriter::XYZWriter writer;
  writer.plotParticles(particles, out_name, iteration);
}
