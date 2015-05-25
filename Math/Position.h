#ifndef __CRSYTAL_MATH_POSITION_H__
#define __CRSYTAL_MATH_POSITION_H__

#include <cmath>
#include <vector>
#include <array>
#include <numeric>
#include "Tolerance.h"


namespace Crystal {
	namespace Math{

template< typename T, size_t DIM >
class Position final
{
public:
	Position(void)
	{
		v.fill(0);
	}

	explicit Position(const std::array<T, DIM>& v) :
		v(v)
	{}

	T getDistance(const Position& rhs) const {
		return ::sqrt(getDistanceSquared(rhs));
	}

	T getDistanceSquared(const Position& rhs) const {
		const auto func1 = [](const T v1, const T v2) { return v1 + v2; };
		const auto func2 = [](const T v1, const T v2) { return std::pow(v1 - v2, 2); };
		return std::inner_product(v.begin(), v.end(), rhs.v.begin(), T(0), func1, func2);
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
	T get(const size_t i) const { return v[i]; }

	void set(const size_t i, const T& v) { this->v[i] = v; }

	std::vector<T> toArray() const { return{ x, y }; }

private:
	std::array<T, DIM> v;
};

template<typename T>
using Position1d = Position < T, 1 >;


template<typename T>
using Position1dVector = std::vector < Position1d<T> >;

template<typename T>
using Position2d = Position < T, 2 >;

template<typename T>
using Position2dVector = std::vector < Position2d<T> >;

template<typename T>
using Position3d_ = Position < T, 3 >;


	}
}

#endif