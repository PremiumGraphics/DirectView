#include "../Particle/ParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Particle;

std::vector<ParticleBasePair> ParticleFindAlgo::findPairs(const std::list<ParticleBaseSPtr>& particles) const
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


ParticleBaseMap ParticleFindAlgo::buildMap(const std::list<ParticleBaseSPtr>& particles) const
{
	ParticleBaseMap map;
	const auto& pairs = findPairs(particles);

	for (const auto& pair : pairs) {
		const auto& p1 = pair.getParticle1();
		const auto& p2 = pair.getParticle2();
		map.insert(std::make_pair(p1, p2));
	}
	return map;

}