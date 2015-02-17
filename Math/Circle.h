#ifndef __CRYSTAL_MATH_CIRCLE_H__
#define __CRYSTAL_MATH_CIRCLE_H__

#include "Vector3d.h"
#include "Matrix3d.h"

#include <cassert>

namespace Crystal {
	namespace Math {

class Circle {
public:
	Circle() :
		radius( 1.0f ),
		center( Vector3d::Zero() )
	{};

	explicit Circle( const float radius ) :
		radius( radius ),
		center( Vector3d::Zero() )
	{};

	Circle( const float radius, const Vector3d& center ) :
		radius( radius ),
		center( center )
	{};

	float getRadius() const { return radius; }

	Vector3d getCenter() const { return center; }

	VectorVector toPoints( const float divideAngle ) const {
		VectorVector points;

		for( float angle = 0.0f; angle <= 360.0f; angle += divideAngle ) {
			const float angle1 = angle / 180.0f * Tolerances::getPI();
			Vector3d pos = center;
			pos += Vector3d( radius * ::sin( angle1 ), 0.0f, radius * ::cos( angle1 ) );
			points.push_back( pos );
		}

		return points;
	}

	void innerOffset( const float length) {
		radius -= length;
		assert( isValid() );
	}

	void outerOffset( const float length) {
		radius += length;
		assert( isValid() );
	}

	bool isShrinked() const {
		return Tolerances::isEqualLoosely( radius, 0.0f );
	}

	bool isValid() const {
		return radius >= 0.0f;
	}

	bool equals( const Circle& rhs ) const {
		return
			Tolerances::isEqualLoosely( radius, rhs.radius ) &&
			radius == rhs.radius;
	}

private:
	float radius;
	Vector3d center;
};

	}
}

#endif