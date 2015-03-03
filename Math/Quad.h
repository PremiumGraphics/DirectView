#ifndef __CRYSTAL_MATH_QUAD_H__
#define __CRYSTAL_MATH_QUAD_H__

#include "Triangle.h"

#include "Vector3d.h"

#include <vector>

namespace Crystal {
	namespace Math {

class Quad {
public:
	Quad() :
		lengthX( 1.0f ),
		lengthY( 1.0f )
	{};

	Quad( const float lengthX, const float lengthY ) :
		lengthX( lengthX ), lengthY( lengthY )
	{
	}

	void setCenter( const Vector3d& center ) { this->center = center; }

	void setLengthX( const float& length ) { this->lengthX = length; }

	void setLengthY( const float& length ) { this->lengthY = length; }

	Vector3d getCenter() const { return center; }

	float getLengthX() const { return lengthX; }

	float getLengthY() const { return lengthY; }

private:
	Vector3d center;

	float lengthX;
	float lengthY;
};

typedef std::vector< Quad > QuadVector;

	}
}

#endif