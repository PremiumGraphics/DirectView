#ifndef __CRYSTAL_MATH_QUAD_H__
#define __CRYSTAL_MATH_QUAD_H__

#include "Vector2d.h"
#include "Position2d.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Quad final {
public:
	Quad() : Quad( Vector2d<T>( 1.0f, 1.0f ) )
	{};

	Quad(const Position2d<T>& v1, const Position2d<T>& v2)
		//Quad( Vector2d<float>(v2.getX() - v1.getX(), v2.getY() - v1.getX() ), (v1.get * 0.5) + (v2 * 0.5) )
	{
		center = Position2d<T>(v1.getX() * 0.5f + v2.getX() * 0.5f, v1.getY() * 0.5f + v2.getY() * 0.5f);
		length = Vector2d<T>( v2.getX() - v1.getX(), v2.getY() - v1.getY() );

	};

	Quad(const Vector2d<T>& length) : Quad(length, Position2d<T>(0.0f, 0.0f))
	{}

	Quad(const Vector2d<T>& length, const Position2d<T>& center) :
		length( length ),
		center( center )
	{}

	Position2d<T> getCenter() const { return center; }

	T getLengthX() const { return length.getX(); }

	T getLengthY() const { return length.getY(); }

	T getArea() const { return getLengthX() * getLengthY(); }

	bool equals(const Quad& rhs) const {
		return
			center == rhs.getCenter() &&
			length == rhs.length;
	}

	bool operator==(const Quad& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Quad& rhs) const {
		return !equals(rhs);
	}

	bool hasIntersection(const Quad& rhs) const {
		const auto distx = std::fabs(center.getX() - rhs.getCenter().getX());
		const auto lx = length.getX() * 0.5 + rhs.getLengthX() * 0.5;

		const auto disty = std::fabs(center.getY() - rhs.getCenter().getY());
		const auto ly = length.getY() * 0.5 + rhs.getLengthY() * 0.5;
		return (distx < lx && disty < ly);
	}

private:
	Position2d<T> center;
	Vector2d<T> length;
};

template<typename T>
using QuadVector = std::vector< Quad<T> >;

	}
}

#endif