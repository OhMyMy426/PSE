/*
 * ParticleContainer.h
 *
 *  Created on: 30.10.2022
 *      Author: Team-B
 */

#pragma once
#include <unordered_map>


class ParticleContainer {
private:
        /**
	* the container of the particle with the type unordered_map<int, Particle>
	*/
	std::unordered_map<int, Particle> Particles;
	
	/**
	* number of the particle
	*/
	int particle_counter = 0;

public:
	/**
	* the getter-function for the particle_counter
	*/
	const int getParticle_counter() const;

	/**
	* the getter-function for the container of the particle
	*/
	std::unordered_map<int, Particle>& getParticles();

	/**
	* one constructor for the class ParticleContainer with parameter-type unordered_map <int, Particle>& and int&
	*/
	ParticleContainer(std::unordered_map <int, Particle>& Particles_arg, int& particle_counter_arg);

	/**
	* another constructor for the class ParticleContainer with parameter-type ParticleContainer&
	*/
	ParticleContainer(const ParticleContainer& other);

	/**
	* destructor for the class ParticleContainer
	*/
	virtual ~ParticleContainer();

	/**
	* a setter-function for the class ParticleContainer with parameter-type int
	*/
	void setParticleCounter(int x);
};
