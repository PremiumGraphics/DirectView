#ifndef __CRYSTAL_MATH_QUAD_H__
#define __CRYSTAL_MATH_QUAD_H__

#include "Vector.h"
#include "Position.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Quad final {
public:
	Quad() : Quad(Vector2d<T>({ 1.0f, 1.0f }))
	{};

	Quad(const Position2d<T>& start) :
		start(start),
		length({ 1, 1 })
	{}


	Quad(const Position2d<T>& v1, const Position2d<T>& v2) :
		start( v1 ),
		length({ v2.getX() - v1.getX(), v2.getY() - v1.getY() })
	{
	};

	Quad(const Vector2d<T>& length) : Quad(Position2d<T>({ 0, 0 }), length)
	{}

	Quad( const Position2d<T>& start,const Vector2d<T>& length) :
		start(start),
		length( length )
	{}

	Position2d<T> getStart() const {
		return start;
	}

	Position2d<T> getEnd() const {
		const auto x = start.getX() + length.getX();
		const auto y = start.getY() + length.getY();
		return Position2d<T>({ x, y });
	}

	Position2d<T> getCenter() const {
		const auto x = start.getX() + length.getX() * T(0.5);
		const auto y = start.getY() + length.getY() * T(0.5);
		return Position2d<T>({ x, y });
	}

	T getLengthX() const { return length.getX(); }

	T getLengthY() const { return length.getY(); }

	Vector2d<T> getLength() const { return length; }

	T getArea() const { return getLengthX() * getLengthY(); }

	bool equals(const Quad& rhs) const {
		return
			getStart() == rhs.getStart() &&
			getLength() == rhs.getLength();
	}

	bool operator==(const Quad& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Quad& rhs) const {
		return !equals(rhs);
	}

	bool hasIntersection(const Quad& rhs) const {
		const auto distx = std::fabs( getCenter().getX() - rhs.getCenter().getX());
		const auto lx = length.getX() * 0.5 + rhs.getLengthX() * 0.5;

		const auto disty = std::fabs( getCenter().getY() - rhs.getCenter().getY());
		const auto ly = length.getY() * 0.5 + rhs.getLengthY() * 0.5;
		return (distx < lx && disty < ly);
	}

	Quad<T> getOverlapped(const Quad<T>& rhs) const {
		assert( hasIntersection(rhs));
		const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
		const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());

		const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
		const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());

		Position2d<T> min({ minx, miny });
		Position2d<T> max({ maxx, maxy });
		return Quad<T>(min, max);
	}

private:
	Position2d<T> start;
	Vector2d<T> length;
};

template<typename T>
using QuadVector = std::vector< Quad<T> >;

	}
}

#endif