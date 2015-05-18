#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Math{

template<typename T>
class Vector3d_ final
{
public:
	
	Vector3d_(void) : Vector3d_(0.0f, 0.0f, 0.0f)
	{}

	Vector3d_(T x, T y, T z) :
		x(x), y(y), z(z)
	{}

	Vector3d_(const Vector3d_& start, const Vector3d_& end) :
		x(end.x - start.x),
		y(end.y - start.y),
		z(end.z - start.z)
	{}

	~Vector3d_() = default;

	static Vector3d_ Zero() { return Vector3d_( 0.0f, 0.0f, 0.0f ); }

	static Vector3d_ UnitX() { return Vector3d_( 1.0f, 0.0f, 0.0f ); }

	static Vector3d_ UnitY() { return Vector3d_( 0.0f, 1.0f, 0.0f ); }

	static Vector3d_ UnitZ() { return Vector3d_( 0.0f, 0.0f, 1.0f ); }

	T getLengthSquared() const {
		return x * x + y * y + z * z;
	}

	T getLength() const {
		return ::sqrt( getLengthSquared() );
	}

	T getDistance(const Vector3d_& rhs) const {
		return ::sqrt(getDistanceSquared(rhs));
	}

	T getDistanceSquared(const Vector3d_& rhs) const {
		return pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2);
	}

	Vector3d_& scale(const T factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d_& scale(const T xFactor, const T yFactor, const T zFactor) {
		x *= xFactor;
		y *= yFactor;
		z *= zFactor;
		return *this;
	}

	Vector3d_ getScaled(const T factor) const {
		return Vector3d_(x * factor, y * factor, z * factor);
	}

	Vector3d_ normalize() {
		const auto length = getLength();
		x /= length;
		y /= length;
		z /= length;
		return *this;
	}

	Vector3d_ getNormalized() const {
		Vector3d_ vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const {
		return Tolerance<T>::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector3d_&rhs ) const {
		return Tolerance<T>::isEqualLoosely( getDistanceSquared( rhs ) );
	}

	bool isZero() const {
		return equals( Zero() );
	}

	bool operator==( const Vector3d_& rhs ) const {
		return equals( rhs );
	}

	bool operator!=(const Vector3d_& rhs) const {
		return !equals( rhs );
	}

	Vector3d_ operator+(const Vector3d_& rhs) const {
		return Vector3d_( x + rhs.x, y + rhs.y, z + rhs.z );
	}

	Vector3d_ operator-(const Vector3d_& rhs) const {
		return Vector3d_( x - rhs.x, y - rhs.y, z - rhs.z );
	}

	Vector3d_ operator+=( const Vector3d_& rhs ) {
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;
		return *this;
	}

	Vector3d_ operator-=(const Vector3d_& rhs) {
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;
		return *this;
	}

	Vector3d_ operator*(const float factor) const {
		Vector3d_ vector(*this);
		return vector.scale(factor);
	}

	Vector3d_ operator/(const float factor) const {
		Vector3d_ vector(*this);
		return vector.scale(1.0f / factor);
	}

	T getInnerProduct(const Vector3d_& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3d_ getOuterProduct(const Vector3d_& rhs) const {
		return Vector3d_(
			y * rhs.z - z * rhs.y,
			-( x * rhs.z - z * rhs.x ),
			x * rhs.y - y * rhs.x );
	}
	
	Vector3d_ operator*=( const T factor ) { return scale( factor ); }

	Vector3d_ operator/=( const T factor ) { return scale( 1.0 / factor ); }

	void rotate(const Matrix3d<T>& matrix) {
		*(this) = getRotated(matrix);
	}

	Vector3d_ getRotated(const Matrix3d<T>& matrix) const {
		const auto x = matrix.getX00() * this->x + matrix.getX01() * this->y + matrix.getX02() * this->z;
		const auto y = matrix.getX10() * this->x + matrix.getX11() * this->y + matrix.getX12() * this->z;
		const auto z = matrix.getX20() * this->x + matrix.getX21() * this->y + matrix.getX22() * this->z;

		return Vector3d_( x, y, z );
	}

	Vector3d_ getMult(const Matrix3d<T>& matrix) const {
		return Vector3d_
			(
			x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20(),
			x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21(),
			x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22()
			);
	}
	
	const Vector3d_ operator*( const Matrix3d<T>& rhs ) const {
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

	static std::vector< T > toArray(const std::vector<Vector3d_>& vectors) {
		std::vector< T > values;
		for (const Math::Vector3d_<T>& v : vectors) {
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

using Vector3d = Vector3d_ < float > ;

using Vector3dd = Vector3d_ < double > ;

using Vector3dVector = std::vector < Vector3d > ;

static Vector3d operator*( float factor, const Vector3d& rhs ) { return rhs.getScaled( factor ); }

static Vector3d operator/( float factor, const Vector3d& rhs ) { return rhs.getScaled( 1.0f / factor ); }


	}
}



#endif