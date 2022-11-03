#pragma once
#include <unordered_map>


class ParticleContainer {
private:

	std::unordered_map<int, Particle> Particles;
    int particle_counter = 0;

public:
	const int getParticle_counter() const;

	std::unordered_map<int, Particle> &getParticles();

	ParticleContainer(std::unordered_map <int, Particle>&  Particles_arg, int& particle_counter_arg);

	ParticleContainer(const ParticleContainer& other);
	virtual ~ParticleContainer();
    void setParticleCounter(int x);

};