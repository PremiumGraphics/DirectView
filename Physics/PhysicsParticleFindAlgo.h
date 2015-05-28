#ifndef __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__

#include "Particle.h"
#include "PhysicsParticlePair.h"

#include "../Util/UnCopyable.h"

#include <vector>

namespace Crystal{
	namespace Physics{

class PhysicsParticleFindAlgo final : private UnCopyable{
public:
	PhysicsParticleFindAlgo() = default;

	~PhysicsParticleFindAlgo() = default;

	void createPairs( ParticleSPtrVector particles, const float effectLength);

	ParticlePairVector getPairs() const { return pairs; }

private:
	ParticlePairVector pairs;

	ParticlePairVector search1(const ParticleSPtrVector& particles, ParticleSPtrVector::const_iterator startIter, ParticleSPtrVector::const_iterator endIter, const float effectLengthSquared);

	ParticlePairVector search2(const ParticleSPtrVector& particles, ParticleSPtrVector::const_iterator startIter, ParticleSPtrVector::const_iterator endIter, const float effectLengthSquared);
};

	}
}

#endif