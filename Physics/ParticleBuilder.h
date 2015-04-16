#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"
#include "../Math/ParticleBase.h"

#include "Particle.h"
#include "ParticleObject.h"

#include <list>

namespace Crystal {
	namespace Physics {


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

	std::list<Math::ParticleBase*> getParticles() const { return particles; }

private:
	float divideLength;
	std::list<Math::ParticleBase*> particles;
	unsigned int nextId;
};
	}
}

#endif