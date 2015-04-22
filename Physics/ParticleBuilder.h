#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "Particle.h"

namespace Crystal {
	namespace Math {
		class Box;
		class Sphere;
		class Cylinder;
		class ParticleBase;
	}
	namespace Physics {

class ParticleBuilder {
public:
	ParticleBuilder() :
		nextId(0),
		divideLength( 1.0f )
	{}

	ParticleSPtr create(const Math::ParticleBase& origin);

	ParticleSPtrVector create(const Math::Box& box);

	ParticleSPtrVector create(const Math::Sphere& sphere);

	ParticleSPtrVector create(const Math::Cylinder& cylinder);

private:
	unsigned int nextId;
	float divideLength;
	Particle::Constant constant;
};

	}
}

#endif