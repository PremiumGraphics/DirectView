#ifndef __CRYSTAL_MATH_CYLINDER_H__
#define __CRYSTAL_MATH_CYLINDER_H__

#include "Vector3d.h"

#include "Triangle.h"

#include "Box.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {

class Cylinder final
{
public:
	Cylinder() :
		center( Vector3d::Zero() ),
		radius( 1.0f ),
		height( 1.0f )
	{}

	Cylinder( const Vector3d& center, const float radius, const float height ) :
	center( center ),
	radius( radius ),
	height( height )
	{
	}

	Cylinder( const Math::Box& boundingBox )
	{
		assert( false );
	}

	virtual Math::Box getBoundingBox() const {
		const Vector3d pos1(center.getX() - radius, center.getY() - height * 0.5f, center.getZ() - radius);
		const Vector3d pos2(center.getX() + radius, center.getY() + height * 0.5f, center.getZ() + radius);
		return Math::Box(pos1, pos2);
	}

	virtual Vector3dVector toPoints(const float divideLength ) const {
		assert( false );
		return Vector3dVector();
	}

	virtual Vector3d getCenter() const { return center; }

	float getVolume() const {
		return radius * radius * Tolerancef::getPI() * height;
	}

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	void setHeight(const float h) { height = h; }

	float getHeight() const { return this->height; }

	virtual bool isValid() const {
		return ( height > 0.0f ) && ( radius > 0.0f ) ;
	}

	void outerOffset(const float offsetLength) {};
	
	/*
	Sphere getOuterOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius += offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}*/

	virtual void innerOffset(const float offsetLength) {};

	/*Sphere getInnerOffset(const float offsetLength) const {
		Sphere sphere = *this;
		sphere.radius -= offsetLength;
		assert( sphere.isValid() );
		return sphere;
	}
	*/

	bool isInner(const Math::Vector3d& point) const
	{
		// TODO. Judge by height.
		if (point.getDistanceSquared( center ) > height * height) {
			return false;
		}
		const Vector3d p1(center.getX(), 0.0, center.getZ());
		const Vector3d p2(point.getX(), 0.0, point.getZ());
		const float distSquared = p1.getDistanceSquared(p2);
		if (distSquared < radius * radius) {
			return true;
		}
		return false;
	}

	bool isOuter(const Math::Vector3d& point)
	{
		return !isInner(point);
	}

private:
	Vector3d center;
	float radius;
	float height;
};

	}
}

#endif