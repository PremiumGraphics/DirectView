#ifndef __CRYSTAL_MATH_QUAD_H__
#define __CRYSTAL_MATH_QUAD_H__

#include "Vector2d.h"

#include <vector>

namespace Crystal {
	namespace Math {

class Quad final {
public:
	Quad() : Quad( 1.0f, 1.0f )
	{};

	Quad(const Vector2d<float>& v1, const Vector2d<float>& v2) :
		Quad(v2.getX() - v1.getX(), v2.getY() - v1.getX(), (v1 * 0.5) + (v2 * 0.5) )
	{};

	Quad(const float lengthX, const float lengthY) : Quad(lengthX, lengthY, Vector2d<float>(0.0f, 0.0f))
	{}

	Quad(const float lengthX, const float lengthY, const Vector2d<float>& center) :
		lengthX(lengthX),
		lengthY(lengthY),
		center( center )
	{}

	void setCenter( const Vector2d<float>& center ) { this->center = center; }

	void setLengthX( const float& length ) { this->lengthX = length; }

	void setLengthY( const float& length ) { this->lengthY = length; }

	Vector2d<float> getCenter() const { return center; }

	float getLengthX() const { return lengthX; }

	float getLengthY() const { return lengthY; }

	float getArea() const { return lengthX * lengthY; }

	bool equals(const Quad& rhs) const {
		return
			center == rhs.getCenter() &&
			Tolerancef::isEqualStrictly( lengthX, rhs.lengthX ) &&
			Tolerancef::isEqualStrictly( lengthY, rhs.lengthY );
	}

	bool operator==(const Quad& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Quad& rhs) const {
		return !equals(rhs);
	}

private:
	Vector2d<float> center;

	float lengthX;
	float lengthY;
};

typedef std::vector< Quad > QuadVector;

	}
}

#endif