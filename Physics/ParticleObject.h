#ifndef __CRYSTAL_PHYSICS_PARTICLE_OBJECT_H__
#define __CRYSTAL_PHYSICS_PARTICLE_OBJECT_H__

#include "Particle.h"

#include "../Math/ParticleBase.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Physics {

class ParticleObject {
public:
	void add(Math::ParticleBase* p) { this->particles.push_back(p); }

	std::list<Math::ParticleBase*> getParticles() const { return particles; }

	float getVolume() const;

	/*
	void add(const ParticleObject& object);

	void intersection(const ParticleObject& object);

	*/
	void remove(Math::ParticleBase* particle);

	void sub(const ParticleObject& rhs);

	bool isInner(Math::ParticleBase* particle) const;

	bool isOuter(Math::ParticleBase* particle) const;

	Math::Box getBoundingBox() const;

private:
	std::list<Math::ParticleBase*> particles;
};


	}
}

#endif