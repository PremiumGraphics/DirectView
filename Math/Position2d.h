#ifndef __CRSYTAL_MATH_POSITION_2D_H__
#define __CRSYTAL_MATH_POSITION_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Vector.h"

namespace Crystal{
	namespace Math{

template< typename T, size_t DIM >
class Position final
{
public:

	Position(void)
	{}

	explicit Position(const std::array<T,DIM>& v) :
		v(v)
	{}

	explicit Position(const Vector2d<T>& v) :
		v(v)
	{}

	T getDistance(const Position& rhs) const {
		return v.getDistance(rhs.v);
	}

	T getDistanceSquared(const Position& rhs) const {
		return v.getDistanceSquared(rhs.v);
	}

	bool equals(const Position&rhs) const {
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	bool operator==(const Position& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position& rhs) const {
		return !equals(rhs);
	}

	Position operator+(const Vector2d<T>& rhs) const {
		return Position(getX() + rhs.x, getY() + rhs.y);
	}

	Position operator-(const Vector2d<T>& rhs) const {
		return Position(getX() - rhs.x, getY() - rhs.y);
	}

	/*
	Vector2d operator+=(const Vector2d& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector2d operator-=(const Vector2d& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	*/

public:
	T getX() const { return v.getX(); }

	T getY() const { return v.getY(); }

	//void setX(const T x) { this->x = x; }

	//void setY(const T y) { this->y = y; }

	std::vector<T> toArray() const { return{ x, y }; }

private:
	Vector<T, DIM> v;
};

template<typename T>
using Position2d = Position < T, 2 > ;

template<typename T>
using Position2dVector = std::vector < Position2d<T> >;

	}
}



#endif