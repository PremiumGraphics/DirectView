#ifndef __NEIGHBOR_SEARCHER_H__
#define __NEIGHBOR_SEARCHER_H__

#include "Particle.h"

#include <vector>

namespace Crystal{
	namespace Physics{
		class NeighborSearcher{
		public:
			static ParticlePairVector createPairs( ParticleVector particles, const float effectLength);
		};
	}
}

#endif