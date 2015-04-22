#ifndef __CRYSTAL_PARTICLE_PARTICLE_OBJECT_H__
#define __CRYSTAL_PARTICLE_PARTICLE_OBJECT_H__

#include "ParticleBase.h"

#include "ParticleBase.h"
#include "../Math/Box.h"

#include "../Util/UnCopyable.h"

#include <list>

#include <memory>

namespace Crystal {
	namespace Particle {

class ParticleObject : private UnCopyable {
public:
	ParticleObject(const unsigned int id) :
		id(id)
	{}

	void add(ParticleBaseSPtr p) { this->particles.push_back(p); }

	std::list<ParticleBaseSPtr> getParticles() const { return particles; }

	float getVolume() const;

	float getMass() const;

	void remove(ParticleBaseSPtr particle);

	void sub(const ParticleObject& rhs);

	bool isInner(ParticleBase* particle) const;

	bool isOuter(ParticleBase* particle) const;

	//bool isOn(ParticleBase* particle) const;

	Math::Box getBoundingBox() const;

	bool hasSelfIntersection() const;

	std::vector< float > toPositionArray() const;

	std::vector< unsigned int > toIdArray() const;

	unsigned int getId() const { return id; }

private:
	std::list<ParticleBaseSPtr> particles;
	unsigned int id;
};

using ParticleObjectSPtr = std::shared_ptr< ParticleObject >;


	}
}

#endif