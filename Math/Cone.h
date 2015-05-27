#ifndef __CRYSTAL_MATH_CONE_H__
#define __CRYSTAL_MATH_CONE_H__

#include "Vector3d.h"

#include "Box.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {

template<typename T>
class Cone final
{
public:
	Cone() :
		center( Vector3d<T>::Zero() ),
		radius( 1.0f ),
		height( 1.0f )
	{}

	Cone( const Vector3d<T>& center, float radius ) :
	center( center ),
	radius( radius )
	{
	}

	Vector3d<T> getCenter() const { return center; }

	void setRadius(const float r) { this->radius = r; }

	float getRadius() const { return radius; }

	void setHeight(const float h) { this->height = h; }

	float getHeight() const { return height; }

	bool isValid() const {
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
	Vector3d<T> center;
	float radius;
	float height;
};

	}
}

#endif