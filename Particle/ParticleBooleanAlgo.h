#ifndef __CRYSTAL_PARTCIEL_PARTICLE_BOOLEAN_ALGO_H__
#define __CRYSTAL_PARTCIEL_PARTICLE_BOOLEAN_ALGO_H__

#include <list>

#include "ParticleBase.h"
#include "ParticleObject.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Particle {

class ParticleBooleanAlgo : private UnCopyable {
public:
	ParticleBaseSPtrList createUnion(const ParticleObject& lhs, const ParticleObject& rhs);

	ParticleBaseSPtrList createIntersection(const ParticleObject& lhs, const ParticleObject& rhs);

	ParticleBaseSPtrList createDiff(const ParticleObject& lhs, const ParticleObject& rhs);

private:
};

	}
}

#endif