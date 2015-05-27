#ifndef __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__
#define __CRYSTAL_PHYSICS_PARTICLE_BUILDER_H__

#include "PhysicsParticle.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
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

	PhysicsParticleSPtrVector create(const Math::Box<float>& box);

	PhysicsParticleSPtrVector create(const Math::Sphere<float>& sphere);

	PhysicsParticleSPtrVector create(const Math::Cylinder<float>& cylinder);

	PhysicsParticleSPtrVector create(const Math::Vector3dVector<float>& positions);

private:
	unsigned int nextId;
	float divideLength;
	PhysicsParticle<float>::Constant constant;
};

	}
}

#endif