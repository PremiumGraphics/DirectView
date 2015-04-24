#ifndef __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PARTICLE_PARTICLE_FIND_ALGO_H__

#include "../Util/UnCopyable.h"

#include "ParticleBasePair.h"

namespace Crystal {
	namespace Particle {

class CollisionFindAlgo : private UnCopyable {
public:
	bool hasCollision(const ParticleBasePair& pair, const float threshold);
private:
	
};

	}
}

#endif