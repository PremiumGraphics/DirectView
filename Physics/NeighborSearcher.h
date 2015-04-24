#ifndef __CRYSTAL_PHYSICS_NEIGHBOR_SEARCHER_H__
#define __CRYSTAL_PHYSICS_NEIGHBOR_SEARCHER_H__

#include "PhysicsParticle.h"
#include "PhysicsParticlePair.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class NeighborSearcher{
		public:
			static ParticlePairVector createPairs( PhysicsParticleSPtrVector particles, const float effectLength);
		};
	}
}

#endif