#ifndef __CRYSTAL_PARTICLE_PARTICLE_TOPOLOGY_H__
#define __CRYSTAL_PARTICLE_PARTICLE_TOPOLOGY_H__

#include "ParticleBase.h"

namespace Crystal {
	namespace Particle {

class ParticleTopology
{
public:
	ParticleTopology() : ParticleTopology(nullptr) {}

	ParticleTopology(const ParticleBaseSPtr& center) :
		center(center),
		uplus(nullptr),
		uminus(nullptr),
		vplus(nullptr),
		vminus(nullptr),
		wplus(nullptr),
		wminus(nullptr)
	{}

	ParticleBaseSPtr getCenter() const { return center; }

	void setUplus(const ParticleBaseSPtr& p){ this->uplus = p; }

	void setUMinus(const ParticleBaseSPtr& p){ this->uminus = p; }

	ParticleBaseSPtr getUplus() const { return uplus; }

	ParticleBaseSPtr getUminus() const { return uminus; }

	void setVplus(const ParticleBaseSPtr& p){ this->vplus = p; }

	void setVMinus(const ParticleBaseSPtr& p){ this->vminus = p; }

	ParticleBaseSPtr getVplus() const { return vplus; }

	ParticleBaseSPtr getVminus() const { return vminus; }

	void setWplus(const ParticleBaseSPtr& p){ this->wplus = p; }

	void setWMinus(const ParticleBaseSPtr& p){ this->wminus = p; }

	ParticleBaseSPtr getWplus() const { return wplus; }

	ParticleBaseSPtr getWminus() const { return wminus; }

private:
	ParticleBaseSPtr center;
	ParticleBaseSPtr uplus;
	ParticleBaseSPtr uminus;
	ParticleBaseSPtr vplus;
	ParticleBaseSPtr vminus;
	ParticleBaseSPtr wplus;
	ParticleBaseSPtr wminus;
};

	}
}

#endif