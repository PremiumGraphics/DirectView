#ifndef __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__

#include "../Util/UnCopyable.h"

#include "ParticleBasePair.h"

#include <list>

#include <map>

namespace Crystal {
	namespace Particle {

using ParticleBaseMap = std::multimap < ParticleBaseSPtr, ParticleBaseSPtr > ;

class ParticleFindAlgo final : private UnCopyable {
public:

	std::vector<ParticleBasePair> findPairs(const std::list<ParticleBaseSPtr>& particles) const;

	ParticleBaseMap buildMap(const std::list<ParticleBaseSPtr>& particles) const;
private:
	
};

	}
}

#endif