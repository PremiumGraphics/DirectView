#ifndef __CRSYTAL_MATH_POSITION_2D_H__
#define __CRSYTAL_MATH_POSITION_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Vector2d.h"

namespace Crystal{
	namespace Math{

template< typename T >
class Position2d final
{
public:

	Position2d(void)
	{}

	Position2d(const T x, const T y) :
		v(x,y)
	{}

	explicit Position2d(const Vector2d<T>& v) :
		v(x,y)
	{}

	T getDistance(const Position2d<T>& rhs) const {
		return v.getDistance(rhs.v);
	}

	T getDistanceSquared(const Position2d<T>& rhs) const {
		return v.getDistanceSquared(rhs.v);
	}

	bool equals(const Position2d<T>&rhs) const {
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	bool operator==(const Position2d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position2d<T>& rhs) const {
		return !equals(rhs);
	}

	Position2d<T> operator+(const Vector2d<T>& rhs) const {
		return Position2d<T>(getX() + rhs.x, getY() + rhs.y);
	}

	Position2d<T> operator-(const Vector2d<T>& rhs) const {
		return Position2d<T>(getX() - rhs.x, getY() - rhs.y);
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
	Vector2d<T> v;
};


	}
}



#endif