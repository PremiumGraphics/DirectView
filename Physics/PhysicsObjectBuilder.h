#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_BUILDER_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_BUILDER_H__

#include "../Util/UnCopyable.h"

#include "../Math/Box.h"
#include "../Math/Vector.h"

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

	PhysicsObjectSPtr create(const Math::Box<float>& box, const PhysicsObject::Type& type) {
		PhysicsParticle<float>::Constant constant;
		PhysicsParticleSPtrVector particles;
		for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
			for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
				for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
					particles.push_back(std::make_shared<PhysicsParticle<float> >(constant, Math::Vector3d<float>(x, y, z)));
					//object->add(p);
				}
			}
		}
		return std::make_shared<PhysicsObject>(particles);
	}

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