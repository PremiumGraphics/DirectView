#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "../Math/Box.h"

#include "Particle.h"

#include <list>

namespace Crystal {
	namespace Physics {

class ParticleObject {
public:
	void add(ParticleBase p) { this->particles.push_back(p); }

	std::list<ParticleBase> getParticles() const { return particles; }

	float getVolume() const;

private:
	std::list<ParticleBase> particles;
};

class ParticleBuilder {
public:
	ParticleBuilder(const float divideLength) :
		divideLength(divideLength)
	{}

	std::list<ParticleBase> build(const Math::Box& box);

private:
	float divideLength;
};
	}
}

#endif