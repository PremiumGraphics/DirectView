#ifndef __NEIGHBOR_SEARCHER_H__
#define __NEIGHBOR_SEARCHER_H__

#include "Particle.h"
#include "ParticlePair.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class NeighborSearcher{
		public:
			static ParticlePairVector createPairs( ParticleSPtrVector particles, const float effectLength);
		};
	}
}

#endif