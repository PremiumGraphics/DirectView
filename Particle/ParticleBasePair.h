#ifndef __CRYSTAL_PARTICLE_PARTICLE_BASE_PAIR_H__
#define __CRYSTAL_PARTICLE_PARTICLE_BASE_PAIR_H__

#include "../Particle/ParticleBase.h"

namespace Crystal {
	namespace Particle {

class ParticleBasePair
{
public:
	ParticleBasePair() :
		particle1( nullptr ),
		particle2( nullptr )
	{}

	ParticleBasePair(const ParticleBaseSPtr& particle1, const ParticleBaseSPtr& particle2) :
		particle1( particle1 ),
		particle2( particle2 )
	{
		assert( isValid() );
	}

	ParticleBaseSPtr getParticle1() const { return particle1; }

	ParticleBaseSPtr getParticle2() const { return particle2; }

	bool isValid() const;

	Math::Vector3d getDistanceVector() const;

	float getDistance() const;

	bool isNeighbor() const;

private:
	ParticleBaseSPtr particle1;
	ParticleBaseSPtr particle2;
};

using ParticleBasePairVector = std::vector < ParticleBasePair > ;
	}
}

#endif