#ifndef __CRSYTAL_MATH_POSITION_H__
#define __CRSYTAL_MATH_POSITION_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

#include "Vector.h"

namespace Crystal {
	namespace Math{

template< typename T, size_t DIM >
class Position final
{
public:

	Position(void)
	{}

	explicit Position(const std::array<T, DIM>& v) :
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

	/*
	Position operator+(const Vector<T,DIM>& rhs) const {
		return Position(get<0>() + rhs.get<0>(), get<1>() + rhs.get<1>());
	}

	Position operator-(const Vector<T,DIM>& rhs) const {
		return Position(get<0>() - rhs.x, get<1>() - rhs.y);
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
	template<size_t I>
	T get() const { return v.get<I>(); }

	T get_(const size_t i) const { return v.get_(i); }

	void set(const size_t i, const T& v) { this->v.set(i,v); }

	std::vector<T> toArray() const { return{ x, y }; }

private:
	Vector<T, DIM> v;
};

template<typename T>
using Position1d = Position < T, 1 >;


template<typename T>
using Position1dVector = std::vector < Position1d<T> >;

template<typename T>
using Position2d = Position < T, 2 >;

template<typename T>
using Position2dVector = std::vector < Position2d<T> >;


	}
}

#endif