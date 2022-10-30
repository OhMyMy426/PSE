#pragma once
#include <unordered_map>


class ParticleContainer {
private:
	int particle_counter = 0;
	std::unordered_map<int, Particle> Particles;

public:
	const int getParticle_counter() const;

	std::unordered_map<int, Particle> &getParticles();

	ParticleContainer(std::unordered_map <int, Particle>  Particles_arg, int particle_counter_arg);

	ParticleContainer(const ParticleContainer& other);
	virtual ~ParticleContainer();


};