
#include "FileReader.h"
#include "outputWriter/XYZWriter.h"
#include "outputWriter/VTKWriter.h"

#include "utils/ArrayUtils.h"

#include <iostream>
#include <list>

#include <unordered_map>
#include "ParticleContainer.h"
#include <string>
#include <unistd.h>

/**** forward declaration of the calculation functions ****/

/**
 * calculate the force for all particles
 */
void calculateF();

/**
 * calculate the position for all particles
 */
void calculateX(const double& delta_t);

/**
 * calculate the position for all particles
 */
void calculateV(const double& delta_t);

/**
 * plot the particles to a xyz-file
 */
void plotParticles(int iteration);

//new
void getOptions(double& end_time, double& delta_t, int argc, char* const* argsv, std::string& infile);


constexpr double start_time = 0;


// TODO: what data structure to pick?
std::unordered_map<int, Particle> particles;
int particle_counter = 0;
static ParticleContainer particleContainer(particles, particle_counter);

int main(int argc, char *argsv[]) {



    std::string infile = "";
    double end_time = 1000;
    double delta_t = 0.014;

    getOptions(end_time, delta_t, argc, argsv, infile);


  std::cout << "Hello from MolSim for PSE!" << std::endl;
  if (infile == "") {
    std::cerr << "It is neccessary to provide an input file, use -h Flag for help. \nThe programm will terminate! " <<std::endl;
    return -1; 
  }

  std::cout << "Your chosen Values are: " << std::endl; 
  std::cout << "\tdelta_t: " << delta_t << std::endl; 
  std::cout << "\tend_time: " << end_time << std::endl; 
  std::cout << "\tinput file: " << infile << std::endl; 


  FileReader fileReader;
  fileReader.readFile(particleContainer, infile);
  std::cout << "done" << std::endl;

 
 
  double current_time = start_time;

  int iteration = 0;

  // for this loop, we assume: current x, current f and current v are known
  while (current_time < end_time) {
    
    
    

    // calculate new x
    calculateX(delta_t);

    // calculate new f
    calculateF();
  
   
    // calculate new v
    calculateV(delta_t);
    

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
    particleContainer.getParticles().at(0).setOldF(particleContainer.getParticles().at(0).getF());
    particleContainer.getParticles().at(0).setF({ 0.,0.,0. });


    for (int i = 0; i < particleContainer.getParticle_counter(); ++i)
    {
        for (int j = i + 1; j < particleContainer.getParticle_counter(); ++j) {
            if (i == 0) {
                particleContainer.getParticles().at(j).setOldF(particleContainer.getParticles().at(j).getF());
                particleContainer.getParticles().at(j).setF({ 0.,0.,0. });

            }

            std::array<double, 3> tmpX = particleContainer.getParticles().at(i).getX() - particleContainer.getParticles().at(j).getX();
            double tmpdist = ArrayUtils::L2Norm(tmpX);
            double tmpM = particleContainer.getParticles().at(j).getM() * particleContainer.getParticles().at(i).getM();

            double tmpdist1 = tmpdist * tmpdist * tmpdist;
            

            for (auto& a : tmpX) {
                a = -a;
            }
            

            particleContainer.getParticles().at(i).setF(particleContainer.getParticles().at(i).getF() + (tmpM/tmpdist1)*tmpX);
            particleContainer.getParticles().at(j).setF(particleContainer.getParticles().at(j).getF() - (tmpM / tmpdist1) * tmpX);

        }
    }
    
    
}

void calculateX(const double& delta_t) {
    std::array<double, 3> x_arg;
    
    for (int i = 0; i < particleContainer.getParticle_counter(); ++i) {
        // @TODO: insert calculation of position updates here!

        for (int j = 0; j < 3; ++j) {
            x_arg.at(j) = particleContainer.getParticles().at(i).getX().at(j) + delta_t * particleContainer.getParticles().at(i).getV().at(j) + (delta_t * delta_t) * particleContainer.getParticles().at(i).getF().at(j)/(2 * particleContainer.getParticles().at(i).getM());
        }

        particleContainer.getParticles().at(i).setX(x_arg);
    }
}

void calculateV(const double& delta_t) {
    for (int a = 0; a < particleContainer.getParticle_counter(); ++a) {
        // @TODO: insert calculation of position updates here!
        std::array<double, 3> f;
        std::array<double, 3> v;

        
        for (size_t c = 0; c < f.size(); c++) {
            f[c] = particleContainer.getParticles().at(a).getF().at(c) + particleContainer.getParticles().at(a).getOldF().at(c);
        }
        
        for (size_t i = 0; i < f.size(); i++) {
            v[i] = particleContainer.getParticles().at(a).getV().at(i) + (delta_t * (f[i] / (2 * particleContainer.getParticles().at(a).getM())));
        }
        particleContainer.getParticles().at(a).setV(v);
    }
}

void plotParticles(int iteration) {

  std::string out_name("MD_vtk");
  outputWriter::VTKWriter writer;

  writer.initializeOutput(particleContainer.getParticle_counter());
  for (int i = 0; i < particleContainer.getParticle_counter(); ++i) {
      writer.plotParticle(particleContainer.getParticles().at(i));
  }
  writer.writeFile(out_name, iteration);
  //outputWriter::XYZWriter writer;
  //writer.plotParticles(particles, out_name, iteration);
  //writer.plotParticles(particleContainer.getParticles(), out_name, iteration);
}

void getOptions(double& end_time, double& delta_t, int argc, char* const* argsv, std::string& infile) {
    int opt;

    while((opt = getopt(argc, argsv, ":i:d:t:h")) != -1)
    {
        switch (opt) {
            case 'i':
                infile = optarg;
                break;
            case 'd':
                delta_t = strtod(optarg, nullptr);
                break;
            case 't': 
                end_time = strtod(optarg, nullptr);
                break;
            case 'h': 
                std::cout << "--------------------------HELP MENU-------------------------" << std::endl;
                std::cout << "There MUST be an input file, the flag is -i" << std::endl;
                std::cout << "There can be a:" << std::endl;
                std::cout << "\tdelta_t, the flag is -d. The standard value is 0.014 " << std::endl;
                std::cout << "\tend_t, the flag is -t. The standard value is 1000 " << std::endl;
                std::cout << "See you next time!" << std::endl;              
                exit(0);
            case ':':
                std::cout << "Option requires a value" << std::endl;
                break;
            case '?':
                std::cout << "Unknown option " << optopt << std::endl;
                break;
        }
    }
    for(; optind < argc; optind++){
        std::cout << "Argument ignored: " << argsv[optind] << std::endl;
    }
}
