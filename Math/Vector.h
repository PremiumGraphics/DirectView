#ifndef __CRYSTAL_MATH_VECTOR_H__
#define __CRYSTAL_MATH_VECTOR_H__

#include <cmath>
#include <vector>
#include <array>
#include <numeric>
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

	Vector(const std::array< T, DIM >& v) : v( v )
	{}
	
	Vector(const Vector& start, const Vector& end)
	{
		for (size_t i = 0; i < DIM; ++i) {
			v[i] = end.v[i] - start.v[i];
		}
	}

	T getLength() const {
		return ::sqrt(getLengthSquared());
	}

	T getLengthSquared() const {
		const auto func = [](const T v1, const T v2) { return v1 + v2 * v2; };
		return std::accumulate(v.begin(), v.end(), T(0), func);
	}

	T getInnerProduct(const Vector& rhs) const {
		return std::inner_product(v.begin(), v.end(), rhs.v.begin(), T(0));
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
		for (size_t i = 0; i < DIM; ++i) {
			if (!Tolerance<T>::isEqualLoosely(v[i], rhs.v[i])) {
				return false;
			}
		}
		return true;
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
	void set(const int i, const T v) { this->v[i] = v; }

	T get(const int i)  const { return this->v[i]; }


	std::array<T, DIM> toArray() const { return v; }

private:
	std::array<T, DIM> v;
};

template<typename T>
using Vector1d = Vector<T, 1>;

template<typename T>
using Vector2d = Vector<T, 2>;

template<typename T>
using Vector3d__ = Vector < T, 3 > ;

template< typename T >
static Vector2d<T> operator*(float factor, const Vector2d<T>& rhs) { return rhs.getScaled(factor); }

template< typename T >
static Vector2d<T> operator/(float factor, const Vector2d<T>& rhs) { return rhs.getScaled(1.0f / factor); }


	}
}

#endif