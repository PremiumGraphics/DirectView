#ifndef __CRYSTAL_MATH_PARTICLE_BOOLEAN_ALGO_H__
#define __CRYSTAL_MATH_PARTICLE_BOOLEAN_ALGO_H__

#include <list>

#include "ParticleBase.h"
#include "ParticleObject.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {

class ParticleBooleanAlgo : private UnCopyable {
public:
	std::list<ParticleBaseSPtr> createUnion(const ParticleObject& lhs, const ParticleObject& rhs);

	std::list<ParticleBaseSPtr> createIntersection(const ParticleObject& lhs, const ParticleObject& rhs);

	std::list<ParticleBaseSPtr> createDiff(const ParticleObject& lhs, const ParticleObject& rhs);
};

	}
}

#endif