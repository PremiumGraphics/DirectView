#ifndef __CRYSTAL_MATH_PARTICLE_BASE_H__
#define __CRYSTAL_MATH_PARTICLE_BASE_H__

#include "../Util/UnCopyable.h"

#include "../Math/Vector3d.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Cylinder.h"

#include <memory>

namespace Crystal {
	namespace Math {

class ParticleBase : private UnCopyable {
public:
	ParticleBase(const float diameter, const Math::Vector3d& position, const unsigned int id) :
		diameter(diameter),
		position(position),
		density( 1.0f ),
		id(id)
	{}

	ParticleBase(const float diameter, const Math::Vector3d& position, const float density, const unsigned int id) :
		diameter(diameter),
		position(position),
		density(density),
		id(id)
	{}


	float getRadius() const { return diameter * 0.5f; }

	float getDiameter() const { return diameter; }

	Vector3d getPosition() const { return position; }

	float getDensity() const { return density; }

	float getVolume() const { return diameter * diameter * diameter; }

	float getMass() const { return getDensity() * getVolume(); }

	unsigned int getId() const { return id; }

private:
	float diameter;
	float density;
	Vector3d position;
	unsigned int id;
};

using ParticleBaseSPtr = std::shared_ptr < ParticleBase > ;

	}
}

#endif