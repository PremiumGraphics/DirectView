#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"
#include "Matrix.h"

namespace Crystal{
	namespace Math{

template<typename T>
class Vector3d final
{
public:
	
	Vector3d(void) : Vector3d(0, 0, 0)
	{}

	Vector3d(T x, T y, T z) :
		x(x), y(y), z(z)
	{}

	Vector3d(const Vector3d& start, const Vector3d& end) :
		x(end.x - start.x),
		y(end.y - start.y),
		z(end.z - start.z)
	{}

	~Vector3d() = default;

	static Vector3d Zero() { return Vector3d( 0, 0, 0 ); }

	static Vector3d UnitX() { return Vector3d( 1, 0, 0 ); }

	static Vector3d UnitY() { return Vector3d( 0, 1, 0 ); }

	static Vector3d UnitZ() { return Vector3d( 0, 0, 1 ); }


	T getLengthSquared() const {
		return x * x + y * y + z * z;
	}

	T getLength() const {
		return ::sqrt( getLengthSquared() );
	}

	T getDistance(const Vector3d& rhs) const {
		return ::sqrt(getDistanceSquared(rhs));
	}

	T getDistanceSquared(const Vector3d& rhs) const {
		return pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2);
	}

	Vector3d& scale(const T factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d& scale(const T xFactor, const T yFactor, const T zFactor) {
		x *= xFactor;
		y *= yFactor;
		z *= zFactor;
		return *this;
	}

	Vector3d getScaled(const T factor) const {
		return Vector3d(x * factor, y * factor, z * factor);
	}

	Vector3d normalize() {
		const auto length = getLength();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vector3d getNormalized() const {
		Vector3d vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const {
		return Tolerance<T>::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector3d&rhs ) const {
		return Tolerance<T>::isEqualLoosely( getDistanceSquared( rhs ) );
	}

	bool isZero() const {
		return equals( Zero() );
	}

	bool operator==( const Vector3d& rhs ) const {
		return equals( rhs );
	}

	bool operator!=(const Vector3d& rhs) const {
		return !equals( rhs );
	}

	Vector3d operator+(const Vector3d& rhs) const {
		return Vector3d( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	Vector3d operator-(const Vector3d& rhs) const {
		return Vector3d( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	Vector3d operator+=( const Vector3d& rhs ) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3d operator-=(const Vector3d& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3d operator-() {
		return Vector3d(-x, -y, -z);
	}

	Vector3d operator*(const float factor) const {
		Vector3d vector(*this);
		return vector.scale(factor);
	}

	Vector3d operator/(const float factor) const {
		Vector3d vector(*this);
		return vector.scale(1.0f / factor);
	}

	T getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d(
			y * rhs.z - z * rhs.y,
			-( x * rhs.z - z * rhs.x ),
			x * rhs.y - y * rhs.x );
	}
	
	Vector3d operator*=( const T factor ) { return scale( factor ); }

	Vector3d operator/=( const T factor ) { return scale( T(1) / factor ); }

	void rotate(const Matrix3d<T>& matrix) {
		*(this) = getMult(matrix);
	}

	Vector3d getMult(const Matrix3d<T>& matrix) const {
		return Vector3d
			(
			x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20(),
			x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21(),
			x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22()
			);
	}
	
	const Vector3d operator*( const Matrix3d<T>& rhs ) const {
		return getMult(rhs);
	}


public:
	T getX() const { return x; }

	T getY() const { return y; }

	T getZ() const { return z; }

	void setX( const T x ) { this->x = x; }

	void setY( const T y ) { this->y = y; }

	void setZ( const T z ) { this->z = z; }

	void set( const T x, const T y, const T z ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	std::vector< T > toArray() const { return std::vector < T > { x, y, z }; }

	std::array< T, 3 > toArray3() const { return std::array < T, 3 > { x, y, z }; }

	static std::vector< T > toArray(const std::vector<Vector3d>& vectors) {
		std::vector< T > values;
		for (const Math::Vector3d<T>& v : vectors) {
			const std::vector<T>& vs = v.toArray();
			values.insert(values.end(), vs.begin(), vs.end());
		}
		return values;
	}

private:
	T x;
	T y;
	T z;
};


template<typename T>
using Vector3dVector = std::vector < Vector3d<T> > ;

template<typename T>
static Vector3d<T> operator*( float factor, const Vector3d<T>& rhs ) { return rhs.getScaled( factor ); }

template<typename T>
static Vector3d<T> operator/( float factor, const Vector3d<T>& rhs ) { return rhs.getScaled( 1.0f / factor ); }


	}
}



#endif