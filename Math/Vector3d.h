#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include "Tolerances.h"
#include "Matrix3d.h"

namespace Crystal{
	namespace Math{

class Box;

class Vector3d
{
public:
	
	Vector3d(void);

	Vector3d(float x, float y, float z);

	Vector3d(const Vector3d& start, const Vector3d& end);

	static Vector3d Zero() { return Vector3d( 0.0f, 0.0f, 0.0f ); }

	static Vector3d UnitX() { return Vector3d( 1.0f, 0.0f, 0.0f ); }

	static Vector3d UnitY() { return Vector3d( 0.0f, 1.0f, 0.0f ); }

	static Vector3d UnitZ() { return Vector3d( 0.0f, 0.0f, 1.0f ); }

	float getLengthSquared() const;

	float getLength() const;

	float getDistance(const Vector3d& rhs) const;

	float getDistanceSquared(const Vector3d& rhs) const;

	Vector3d scale(const float factor);

	Vector3d scale(const float xFactor, const float yFactor, const float zFactor);

	Vector3d getScaled( const float factor ) const;

	Vector3d normalize();

	Vector3d getNormalized() const;

	bool isNormalized() const {
		return Tolerances::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector3d &rhs ) const {
		return Tolerances::isEqualLoosely( getDistanceSquared( rhs ) );
	}

	bool isZero() const;

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