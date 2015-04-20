#ifndef __CRYSTAL_MATH_PARTICLE_BASE_H__
#define __CRYSTAL_MATH_PARTICLE_BASE_H__

#include "../Util/UnCopyable.h"

#include "Vector3d.h"

#include "Box.h"
#include "Sphere.h"
#include "Cylinder.h"

#include <memory>

namespace Crystal {
	namespace Math {

class ParticleBase : private UnCopyable {
public:
	ParticleBase(const float diameter, const Math::Vector3d& position, const unsigned int id) :
		diameter(diameter),
		position(position),
		id(id)
	{}

	float getRadius() const { return diameter * 0.5f; }

	float getDiameter() const { return diameter; }

	Vector3d getPosition() const { return position; }

	float getVolume() const { return diameter * diameter * diameter; }

	unsigned int getId() const { return id; }

private:
	float diameter;
	Vector3d position;
	unsigned int id;
};

using ParticleBaseSPtr = std::shared_ptr < ParticleBase > ;

class ParticleBuilder : private UnCopyable {
public:
	ParticleBuilder() :
		nextId(0)
	{}

	ParticleBuilder(const float diameter) :
		divideLength( diameter ),
		nextId(0)
	{}

	std::vector<ParticleBase*> create(const Box& box);

	std::vector<ParticleBase*> create(const Sphere& sphere);

	std::vector<ParticleBase*> create(const Cylinder& cylinder);

private:
	float divideLength;
	unsigned int nextId;
};
	}
}

#endif