#ifndef __CRYSTAL_PHYSICS_NEIGHBOR_SEARCHER_H__
#define __CRYSTAL_PHYSICS_NEIGHBOR_SEARCHER_H__

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

};

	}
}

#endif