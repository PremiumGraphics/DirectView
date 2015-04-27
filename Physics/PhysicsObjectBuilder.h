#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_BUILDER_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_BUILDER_H__

#include "../Util/UnCopyable.h"
#include "PhysicsParticle.h"
#include "PhysicsObject.h"

namespace Crystal {
	namespace Physics {

class PhysicsObjectBuilder final : private UnCopyable
{
public:
	PhysicsObjectBuilder() :
		nextId(0),
		density(1.0f),
		divideLength( 1.0f )
	{}

	~PhysicsObjectBuilder() = default;

	PhysicsObjectSPtr create(const Math::Box& box, const PhysicsObject::Type& type);

private:
	float divideLength;
	float density;
	unsigned int nextId;
	/*
	ParticleBaseBuilder() :
		nextId(0),
		density(1.0f)
	{}

	ParticleBaseBuilder(const float diameter) :
		divideLength(diameter),
		density(1.0f),
		nextId(0)
	{}

	float getDivideLength() const { return divideLength; }

	float getDensity() const { return density; }

	void setDivideLength(const float l) { this->divideLength = l; }

	void setDensity(const float d) { this->density = density; }

	std::list<ParticleBaseSPtr> create(const Box& box);

	std::list<ParticleBaseSPtr> create(const Sphere& sphere);

	std::list<ParticleBaseSPtr> create(const Cylinder& cylinder);

private:
	float divideLength;
	float density;
	unsigned int nextId;
	*/
};
	}
}

#endif