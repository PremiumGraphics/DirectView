#ifndef __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__
#define __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__

#include "PhysicsParticle.h"

namespace Crystal {
	namespace Physics {

class PhysicsParticlePair
{
public:
	PhysicsParticlePair() :
		particle1( nullptr ),
		particle2( nullptr )
	{}

	PhysicsParticlePair(const PhysicsParticleSPtr& particle1, const PhysicsParticleSPtr& particle2) :
		particle1(particle1),
		particle2(particle2)
	{
	}

	Math::Vector3d getDistanceVector() const {
		return Math::Vector3d(particle1->getCenter() - particle2->getCenter());
	}

	float getDistance() const {
		return getDistanceVector().getLength();
	}

	float getDistanceSquared() const {
		return particle1->getCenter().getDistanceSquared(particle2->getCenter());
	}

	float getPressure() const {
		return (particle1->getPressure() + particle2->getPressure()) * 0.5f;
	}

	float getViscosityCoe() const {
		return (particle1->getViscosityCoe() + particle2->getViscosityCoe()) * 0.5f;
	}

	Math::Vector3d getVelocityDiff() const {
		return Math::Vector3d(particle1->getVelocity(), particle2->getVelocity());
	}

	bool isValid() const {
		return
			particle1 != nullptr &&
			particle2 != nullptr &&
			particle1 != particle2;
	}

	PhysicsParticleSPtr getParticle1() const { return particle1; }

	PhysicsParticleSPtr getParticle2() const { return particle2; }

private:
	PhysicsParticleSPtr particle1;
	PhysicsParticleSPtr particle2;
};

using ParticlePairVector = std::vector<PhysicsParticlePair>;

	}
}

#endif