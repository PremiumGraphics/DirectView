#ifndef __CRYSTAL_MATH_PARTICLE_OBJECT_H__
#define __CRYSTAL_MATH_PARTICLE_OBJECT_H__

#include "ParticleBase.h"

#include "../Math/ParticleBase.h"
#include "../Math/Box.h"

#include "../Util/UnCopyable.h"

#include <list>

#include <memory>

namespace Crystal {
	namespace Math {

class ParticleObject : private UnCopyable {
public:
	ParticleObject(const unsigned int id) :
		id(id)
	{}

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

	//bool isOn(ParticleBase* particle) const;

	Math::Box getBoundingBox() const;

	std::vector< float > toPositionArray() const;

	std::vector< unsigned int > toIdArray() const;

	unsigned int getId() const { return id; }

private:
	std::list<Math::ParticleBase*> particles;
	unsigned int id;
};

using ParticleObjectSPtr = std::shared_ptr< ParticleObject >;

class ParticleBooleanAlgo {
public:
	std::list<ParticleBase*> createUnion(const ParticleObject& lhs, const ParticleObject& rhs);

	std::list<ParticleBase*> createIntersection(const ParticleObject& lhs, const ParticleObject& rhs);

	std::list<ParticleBase*> createDiff(const ParticleObject& lhs, const ParticleObject& rhs);
};

	}
}

#endif