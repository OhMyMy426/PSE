//This class handles everything in regard to the output of the program and can be extended to suit other output formats. Planned are new Methods


#include "OutputWriter.h"
#include "outputWriter/VTKWriter.h"
#include <string>
#include "ParticleContainer.h"

OutputWriter::OutputWriter() = default;

OutputWriter::~OutputWriter() = default;

/**
 *  Handles the output in a VTK-Format
 * 
 * @param particleContainer The ParticleContainer which particles should be written
 * @param iteration The iteration being written
 * @param out_name The general name of the output file
 */

void OutputWriter::VTKOutput(ParticleContainer& particleContainer, int iteration, std::string out_name) {
    outputWriter::VTKWriter writer;
    writer.initializeOutput(particleContainer.getParticle_counter());
    for (int i = 0; i < particleContainer.getParticle_counter(); ++i) {
      writer.plotParticle(particleContainer.getParticles().at(i));
  }    
  writer.writeFile(out_name, iteration);

}



