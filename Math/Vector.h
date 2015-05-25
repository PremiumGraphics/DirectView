#ifndef __CRYSTAL_MATH_VECTOR_H__
#define __CRYSTAL_MATH_VECTOR_H__

#include <cmath>
#include <vector>
#include <array>
#include "Tolerance.h"

namespace Crystal {
	namespace Math {


template< typename T, size_t DIM >
class Vector final
{
public:

	Vector(void)
	{
		v.fill(0);
	}

	explicit Vector(const T x) {
		v = { x };
	}

	/*
	Vector(const T x, const T y)
	{
		v = { x, y };
	}

	Vector(const T x, const T y, const T z)
	{
		v = { x, y, z };
	}
	*/
	Vector(const std::array< T, DIM >& v) : v( v )
	{}
	
	Vector(const Vector& start, const Vector& end)
	{
		for (size_t i = 0; i < DIM; ++i) {
			v[i] = end.v[i] - start.v[i];
		}
	}

	static Vector Zero() { return Vector(0, 0); }

	static Vector UnitX() { return Vector(1, 0); }

	static Vector UnitY() { return Vector(0, 1); }

	T getLengthSquared() const {
		T ls = 0;
		for (auto x : v) {
			ls += x * x;
		}
		return ls;
	}

	T getLength() const {
		return ::sqrt(getLengthSquared());
	}

	T getDistance(const Vector& rhs) const {
		return ::sqrt(getDistanceSquared(rhs));
	}

	T getDistanceSquared(const Vector& rhs) const {
		T ls = 0;
		for (size_t i = 0; i < DIM; ++i) {
			ls += pow(v[i] - rhs.v[i], 2);
		}
		return ls;
	}

	Vector scale(const T factor) {
		for (auto& x : v) {
			x *= factor;
		}
		return *this;
	}

	Vector scale(const Vector factor) {
		for (size_t i = 0; i < DIM; ++i) {
			v[i] *= factor[i];
		}
		return *this;
	}

	Vector getScaled(const T factor) const {
		auto dest = v;
		for (size_t i = 0; i < DIM; ++i) {
			dest[i] *= factor;
		}
		return Vector(dest);
	}

	Vector normalize() {
		const T length = getLength();
		x /= length;
		y /= length;
		return *this;
	}

	Vector getNormalized() const {
		Vector<T> vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const {
		return Tolerance<T>::isEqualLoosely(getLength(), 1.0);
	}

	bool equals(const Vector&rhs) const {
		return Tolerance<T>::isEqualLoosely(getDistanceSquared(rhs));
	}

	bool operator==(const Vector& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Vector& rhs) const {
		return !equals(rhs);
	}

	Vector operator+(const Vector& rhs) const {
		return Vector<T>(x + rhs.x, y + rhs.y);
	}

	Vector operator-(const Vector& rhs) const {
		return Vector(x - rhs.x, y - rhs.y);
	}

	Vector operator+=(const Vector& rhs) {
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vector operator-=(const Vector& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vector operator*(const T factor) const {
		Vector<T> vector(*this);
		return vector.scale(factor);
	}

	Vector operator/(const T factor) const {
		Vector<T> vector(*this);
		return vector.scale(1.0f / factor);
	}

	Vector operator*=(const T factor) { return scale(factor); }

	Vector operator/=(const T factor) { return scale(1.0f / factor); }

public:

	T getY() const { return v[1]; }

	template<size_t I>
	T get() const { return v[I]; }

	void setX(const T x) { this->v[0] = x; }

	void setY(const T y) { this->v[1] = y; }

	std::array<T, DIM> toArray() const { return v; }

private:
	std::array<T, DIM> v;
};

template<typename T>
using Vector1d = Vector<T, 1>;

template<typename T>
using Vector2d = Vector<T, 2>;

template< typename T >
static Vector2d<T> operator*(float factor, const Vector2d<T>& rhs) { return rhs.getScaled(factor); }

template< typename T >
static Vector2d<T> operator/(float factor, const Vector2d<T>& rhs) { return rhs.getScaled(1.0f / factor); }


	}
}

#endif