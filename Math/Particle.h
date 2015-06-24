#ifndef __CRYSTAL_MATH_PARTICLE_H__
#define __CRYSTAL_MATH_PARTICLE_H__

#include <memory>
#include <list>

#include "Vector.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Particle3d
{
public:
	Particle3d() :
		radius(1),
		charge(1)
	{}

	Particle3d(const Vector3d<T>& center, const T radius, const T charge) :
		center(center),
		radius(radius),
		charge(charge)
	{}

	Particle3d& move(const Vector3d<T>& vector) {
		center += vector;
		return (*this);
	}

	T getRadius() const { return radius; }

	Vector3d<T> getCenter() const { return center; }

	Vector3d<T> getMinPosition() const { return Vector3d<T>(center.getX() - radius, center.getY() - radius, center.getZ() - radius); }

	Vector3d<T> getMaxPosition() const { return Vector3d<T>(center.getX() + radius, center.getY() + radius, center.getZ() + radius); }

	//Space3d<T> getSpace() const { return Space3d<T>( ) }

	T getValue(const Math::Vector3d<T>& pos) const
	{
		const auto dist = pos.getDistance(center);
		const auto v = 1.0f - dist / radius;
		return v * charge;
	}

private:
	Vector3d<float> center;
	T radius;
	T charge;
};

template<typename T>
using MetaballSPtr = std::shared_ptr < Particle3d<T> > ;

template<typename T>
using MetaballSPtrList = std::list < MetaballSPtr<T> > ;


	}
}
#endif