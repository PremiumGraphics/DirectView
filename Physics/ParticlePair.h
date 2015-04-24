#ifndef __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__
#define __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__

#include "PhysicsParticle.h"

namespace Crystal {
	namespace Physics {

struct ParticlePair{
	ParticlePair(PhysicsParticle* particle1, PhysicsParticle* particle2) :
		particle1(particle1), particle2(particle2)
	{
	}
	PhysicsParticle* particle1;
	PhysicsParticle* particle2;

	Math::Vector3d getDistanceVector() const {
		return Math::Vector3d(particle1->getCenter() - particle2->getCenter());
	}

	float getDistance() const {
		return getDistanceVector().getLength();
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
};

typedef std::vector<ParticlePair> ParticlePairVector;

	}
}

#endif