#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"

#include "Particle.h"

#include <list>

namespace Crystal {
	namespace Physics {

class ParticleObject {
public:
	void add(ParticleBase* p) { this->particles.push_back(p); }

	std::list<ParticleBase*> getParticles() const { return particles; }

	float getVolume() const;

	/*
	void add(const ParticleObject& object);

	void intersection(const ParticleObject& object);

	void sub(const ParticleBase& particle);
	*/

private:
	std::list<ParticleBase*> particles;
};

/*
class ParticleBooleanAlgo {

};
*/

class ParticleBuilder {
public:
	ParticleBuilder(const float divideLength) :
		divideLength(divideLength)
	{}

	std::list<ParticleBase*> build(const Math::Box& box);

	ParticleObject build(const Math::Sphere& s);

private:
	float divideLength;
};
	}
}

#endif