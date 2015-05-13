#ifndef __CRYSTAL_MATH_CONE_H__
#define __CRYSTAL_MATH_CONE_H__

#include "Primitive.h"

#include "Vector3d.h"

#include "Box.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {
		class Box;

class Cone : public Primitive
{
public:
	Cone() :
		center( Vector3d::Zero() ),
		radius( 1.0f ),
		height( 1.0f )
	{}

	Cone( const Vector3d& center, float radius ) :
	center( center ),
	radius( radius )
	{
	}

	Cone( const Math::Box& boundingBox )
	{
		assert( false );
	}

	virtual Math::Box getBoundingBox() const
	{
		assert( false );
		return Math::Box();
	}

	virtual Type getType() const { return Primitive::Cone; }

	virtual Vector3dVector toPoints(const float divideLength ) const {
		assert( false );
		return Vector3dVector();
	}

	virtual Vector3d getCenter() const { return center; }

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	void setHeight(const float h) { this->height = h; }

	float getHeight() const { return height; }

	virtual bool isValid() const {
		return ( height > 0.0f ) && ( radius > 0.0f ) ;
	}

	float getVolume() const {
		return radius * radius * Tolerancef::getPI() * height / 3.0f;
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

private:
	Vector3d center;
	float radius;
	float height;
};

	}
}

#endif