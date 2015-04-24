#ifndef __CRYSTAL_PARTICLE_PARTICLE_BASE_PAIR_H__
#define __CRYSTAL_PARTICLE_PARTICLE_BASE_PAIR_H__

#include "../Particle/ParticleBase.h"

namespace Crystal {
	namespace Particle {

class ParticleBasePair
{
public:
	ParticleBasePair()
	{}

	ParticleBasePair(const ParticleBaseSPtr& particle1, const ParticleBaseSPtr& particle2) :
		particle1( particle1 ),
		particle2( particle2 )
	{
	}

	ParticleBaseSPtr getParticle1() const { return particle1; }

	ParticleBaseSPtr getParticle2() const { return particle2; }

	bool isValid() const {
		return
			(particle1 != nullptr) &&
			(particle2 != nullptr);
	}

	void getDistance() const {
		particle1->getPosition().getDistance(particle2->getPosition());
	}

private:
	ParticleBaseSPtr particle1;
	ParticleBaseSPtr particle2;
};
	}
}

#endif