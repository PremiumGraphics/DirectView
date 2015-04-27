#ifndef __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__

#include "PhysicsParticle.h"
#include "PhysicsParticlePair.h"

#include "../Util/UnCopyable.h"

#include <vector>

namespace Crystal{
	namespace Physics{

class PhysicsParticleFindAlgo final : private UnCopyable{
public:
	PhysicsParticleFindAlgo() = default;

	~PhysicsParticleFindAlgo() = default;

	void createPairs( PhysicsParticleSPtrVector particles, const float effectLength);

	ParticlePairVector getPairs() const { return pairs; }

private:
	ParticlePairVector pairs;

	ParticlePairVector search1(const PhysicsParticleSPtrVector& particles, PhysicsParticleSPtrVector::const_iterator startIter, PhysicsParticleSPtrVector::const_iterator endIter, const float effectLengthSquared);

	ParticlePairVector search2(const PhysicsParticleSPtrVector& particles, PhysicsParticleSPtrVector::const_iterator startIter, PhysicsParticleSPtrVector::const_iterator endIter, const float effectLengthSquared);
};

	}
}

#endif