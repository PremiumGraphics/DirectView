#ifndef __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__

#include "../Util/UnCopyable.h"

#include "ParticleBasePair.h"

#include <list>

namespace Crystal {
	namespace Particle {

class ParticleFindAlgo final : private UnCopyable {
public:

	std::vector<ParticleBasePair> findPairs(const std::list<ParticleBaseSPtr>& particles) const;
private:
	
};

	}
}

#endif