#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "Particle.h"

namespace Crystal {
	namespace Math {
		class Box;
		class Sphere;
		class Cylinder;
	}
	namespace Particle {
		class ParticleBase;
	}
	namespace Physics {

class ParticleBuilder {
public:
	ParticleBuilder() :
		nextId(0),
		divideLength( 1.0f )
	{}

	PhysicsParticleSPtr create(const Crystal::Particle::ParticleBase& origin);

	PhysicsParticleSPtrVector create(const Math::Box& box);

	PhysicsParticleSPtrVector create(const Math::Sphere& sphere);

	PhysicsParticleSPtrVector create(const Math::Cylinder& cylinder);

private:
	unsigned int nextId;
	float divideLength;
	PhysicsParticle::Constant constant;
};

	}
}

#endif