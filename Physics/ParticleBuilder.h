#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

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

	*/
	void sub(ParticleBase* particle);

	void sub(const ParticleObject& rhs);

	bool isInner(ParticleBase* particle) const;

	bool isOuter(ParticleBase* particle) const;

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
		divideLength(divideLength),
		nextId(0)
	{}

	void clear();

	ParticleObject build(const Math::Box& box);

	ParticleObject build(const Math::Sphere& s);

	ParticleObject build(const Math::Cylinder& c);

	std::list<ParticleBase*> getParticles() const { return particles; }

private:
	float divideLength;
	std::list<ParticleBase*> particles;
	unsigned int nextId;
};
	}
}

#endif