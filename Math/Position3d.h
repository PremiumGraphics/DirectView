#ifndef __CRSYTAL_MATH_POSITION_3D_H__
#define __CRSYTAL_MATH_POSITION_3D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Vector3d.h"

namespace Crystal{
	namespace Math{

template< typename T >
class Position3d final
{
public:

	Position3d(void)
	{}

	Position3d(const T x, const T y, const T z) :
		v(x, y, z)
	{}

	explicit Position3d(const Vector3d& v) :
		v(v)
	{}

	T getDistance(const Position3d<T>& rhs) const {
		return v.getDistance(rhs.v);
	}

	T getDistanceSquared(const Position3d<T>& rhs) const {
		return v.getDistanceSquared(rhs.v);
	}

	bool equals(const Position3d<T>&rhs) const {
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	bool operator==(const Position3d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Position3d<T>& rhs) const {
		return !equals(rhs);
	}

	Vector3d_<T> diff(const Position3d<T>& rhs) const {
		return Vector3d_<T>(
			rhs.getX() - getX(),
			rhs.getY() - getY(),
			rhs.getZ() - getZ()
			);
	}

	Position3d<T> operator+(const Vector3d_<T>& rhs) const {
		return Position3d<T>(getX() + rhs.getX(), getY() + rhs.getY(), getZ() + rhs.getZ() );
	}

	Position3d<T> operator-(const Vector3d_<T>& rhs) const {
		return Position3d<T>(getX() - rhs.getX(), getY() - rhs.getY(), getZ() - rhs.getZ() );
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

	T getZ() const { return v.getZ(); }

	//void setX(const T x) { this->x = x; }

	//void setY(const T y) { this->y = y; }

	std::vector<T> toArray() const { return{ x, y, z }; }

private:
	Vector3d_<T> v;
};


	}
}



#endif