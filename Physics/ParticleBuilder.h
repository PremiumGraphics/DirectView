#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "PhysicsParticle.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {
		class Sphere;
		class Cylinder;
	}
	namespace Particle {
		class ParticleBase;
	}
	namespace Physics {

class ParticleBuilder final : private UnCopyable {
public:
	ParticleBuilder() :
		nextId(0),
		divideLength( 1.0f )
	{}

	~ParticleBuilder() = default;

	unsigned int getNextId() const { return nextId; }

	float getDivideLength() const { return divideLength; }

	PhysicsParticleSPtr create(const Crystal::Particle::ParticleBase& origin);

	PhysicsParticleSPtrVector create(const Math::Box& box);

	PhysicsParticleSPtrVector create(const Math::Sphere& sphere);

	PhysicsParticleSPtrVector create(const Math::Cylinder& cylinder);

	PhysicsParticleSPtrVector create(const Math::Vector3dVector& positions);

private:
	unsigned int nextId;
	float divideLength;
	PhysicsParticle::Constant constant;
};

	}
}

#endif