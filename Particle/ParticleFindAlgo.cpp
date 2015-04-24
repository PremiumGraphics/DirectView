#include "../Particle/ParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

std::vector<ParticleBasePair> ParticleFindAlgo::getPairs(const std::list<ParticleBaseSPtr>& particles) const
{
	std::vector<ParticleBasePair> pairs;

	for (const ParticleBaseSPtr& p1 : particles) {
		for (const ParticleBaseSPtr& p2 : particles) {
			if (p1 == p2) {
				continue;
			}
			ParticleBasePair pair(p1, p2);
			if (pair.isNeighbor()) {
				ParticleBasePair pair(p1, p2);
				pairs.push_back(pair);
			}
			//if ( hasCo)
		}
	}

	return pairs;
}
