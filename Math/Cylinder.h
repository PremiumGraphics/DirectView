#ifndef __CRYSTAL_MATH_CYLINDER_H__
#define __CRYSTAL_MATH_CYLINDER_H__

#include "Vector.h"

#include "Triangle.h"

#include "Box.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {

template<typename T>
class Cylinder final
{
public:
	Cylinder() :
		center( Vector3d<T>::Zero() ),
		radius( 1.0f ),
		height( 1.0f )
	{}

	Cylinder( const Vector3d<T>& center, const float radius, const float height ) :
	center( center ),
	radius( radius ),
	height( height )
	{
	}

	Math::Box<T> getBoundingBox() const {
		const Vector3d<T> pos1(center.getX() - radius, center.getY() - height * 0.5f, center.getZ() - radius);
		const Vector3d<T> pos2(center.getX() + radius, center.getY() + height * 0.5f, center.getZ() + radius);
		return Math::Box<T>(pos1, pos2);
	}

	Vector3d<T> getCenter() const { return center; }

	T getVolume() const {
		return radius * radius * Tolerance<T>::getPI() * height;
	}

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	void setHeight(const float h) { height = h; }

	float getHeight() const { return this->height; }

	virtual bool isValid() const {
		return ( height > 0.0f ) && ( radius > 0.0f ) ;
	}

	void outerOffset(const float offsetLength) {};

	virtual void innerOffset(const float offsetLength) {};

	bool isInner(const Math::Vector3d<T>& point) const
	{
		// TODO. Judge by height.
		if (point.getDistanceSquared( center ) > height * height) {
			return false;
		}
		const Vector3d<T> p1(center.getX(), 0.0, center.getZ());
		const Vector3d<T> p2(point.getX(), 0.0, point.getZ());
		const float distSquared = p1.getDistanceSquared(p2);
		if (distSquared < radius * radius) {
			return true;
		}
		return false;
	}

	bool isOuter(const Math::Vector3d<T>& point)
	{
		return !isInner(point);
	}

private:
	Vector3d<T> center;
	float radius;
	float height;
};

	}
}

#endif