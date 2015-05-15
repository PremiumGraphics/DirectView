#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Math{

class Vector3d final
{
public:
	
	Vector3d(void) : Vector3d(0.0f, 0.0f, 0.0f)
	{}

	Vector3d(float x, float y, float z) :
		x(x), y(y), z(z)
	{}

	Vector3d(const Vector3d& start, const Vector3d& end) :
		x(end.x - start.x),
		y(end.y - start.y),
		z(end.z - start.z)
	{}

	~Vector3d() = default;

	static Vector3d Zero() { return Vector3d( 0.0f, 0.0f, 0.0f ); }

	static Vector3d UnitX() { return Vector3d( 1.0f, 0.0f, 0.0f ); }

	static Vector3d UnitY() { return Vector3d( 0.0f, 1.0f, 0.0f ); }

	static Vector3d UnitZ() { return Vector3d( 0.0f, 0.0f, 1.0f ); }

	float getLengthSquared() const {
		return x * x + y * y + z * z;
	}

	float getLength() const {
		return ::sqrt( getLengthSquared() );
	}

	float getDistance(const Vector3d& rhs) const {
		return ::sqrt(getDistanceSquared(rhs));
	}

	float getDistanceSquared(const Vector3d& rhs) const {
		return pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2);
	}

	Vector3d& scale(const float factor) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d& scale(const float xFactor, const float yFactor, const float zFactor) {
		x *= xFactor;
		y *= yFactor;
		z *= zFactor;
		return *this;
	}

	Vector3d getScaled(const float factor) const {
		return Vector3d(x * factor, y * factor, z * factor);
	}

	Vector3d normalize();

	Vector3d getNormalized() const;

	bool isNormalized() const {
		return Tolerancef::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector3d &rhs ) const {
		return Tolerancef::isEqualLoosely( getDistanceSquared( rhs ) );
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

	Vector3d operator-=(const Vector3d& rhs);

	Vector3d operator*(const float factor) const;

	Vector3d operator/(const float factor) const;

	float getInnerProduct(const Vector3d& rhs) const {
		return x * rhs.x + y * rhs.y + z * rhs.z;
	}

	Vector3d getOuterProduct(const Vector3d& rhs) const {
		return Vector3d(
			y * rhs.z - z * rhs.y,
			-( x * rhs.z - z * rhs.x ),
			x * rhs.y - y * rhs.x );
	}
	
	Vector3d operator*=( const float factor ) { return scale( factor ); }

	Vector3d operator/=( const float factor ) { return scale( 1.0f / factor ); }

	void rotate(const Matrix3d<double>& matrix);

	Vector3d getRotated(const Matrix3d<double>& matrix) const;

	Vector3d getMult(const Matrix3d<float>& matrix) const;
	
	const Vector3d Vector3d::operator*( const Matrix3d<float>& rhs ) const;

public:
	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

	void setX( const float x ) { this->x = x; }

	void setY( const float y ) { this->y = y; }

	void setZ( const float z ) { this->z = z; }

	void set( const float x, const float y, const float z ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	std::vector< float > toArray() const { return std::vector < float > { x, y, z }; }

	static std::vector< float > toArray(const std::vector<Vector3d>& vectors);

private:
	float x;
	float y;
	float z;
};

using Vector3dVector = std::vector < Vector3d > ;

static Vector3d operator*( float factor, const Vector3d& rhs ) { return rhs.getScaled( factor ); }

static Vector3d operator/( float factor, const Vector3d& rhs ) { return rhs.getScaled( 1.0f / factor ); }


	}
}



#endif