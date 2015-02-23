#ifndef __CRSYTAL_MATH_VECTOR_3D_H__
#define __CRSYTAL_MATH_VECTOR_3D_H__

#include <cmath>
#include <vector>
#include "Tolerances.h"

namespace Crystal{
	namespace Math{

class Box;
class Matrix3d;

class Vector3d
{
public:
	
	Vector3d( void ) :
		x( 0.0 ), y( 0.0 ), z( 0.0 )
	{}

	Vector3d( float x, float y, float z ) :
		x( x), y( y), z( z)
	{}

	Vector3d( const Vector3d& start, const Vector3d& end ) :
		x( end.x - start.x ),
		y( end.y - start.y ),
		z( end.z - start.z )
	{}

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
	
	float getDistance( const Vector3d& rhs ) const {
		return ::sqrt( getDistanceSquared( rhs ) );
	}

	float getDistanceSquared( const Vector3d& rhs ) const {
		return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 ) + pow( z - rhs.z, 2 );
	}

	Vector3d scale( const float factor ) {
		x *= factor;
		y *= factor;
		z *= factor;
		return *this;
	}

	Vector3d scale( const float xFactor, const float yFactor, const float zFactor ) {
		x *= xFactor;
		y *= yFactor;
		z *= zFactor;
		return *this;
	}

	Vector3d getScaled( const float factor ) const;

	Vector3d normalize();

	Vector3d getNormalized() const;

	bool isNormalized() const {
		return Tolerances::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector3d &rhs ) const {
		return Tolerances::isEqualLoosely( getDistance( rhs ) );
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

	void rotate(const Matrix3d& matrix);

	Vector3d getRotated(const Matrix3d& matrix) const;

	Vector3d getMult(const Matrix3d& matrix) const;
	
	const Vector3d Vector3d::operator*( const Matrix3d& rhs ) const;

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

private:
	float x;
	float y;
	float z;
};

typedef std::vector< Vector3d > Vector3dVector;

static Vector3d operator*( float factor, const Vector3d& rhs ) { return rhs.getScaled( factor ); }

static Vector3d operator/( float factor, const Vector3d& rhs ) { return rhs.getScaled( 1.0f / factor ); }

static std::vector< float > toArray( const std::vector<Vector3d>& vectors) {
	std::vector< float > values;
	for( const Math::Vector3d& v : vectors ) {
		const std::vector<float>& vs = v.toArray();
		values.insert( values.end(), vs.begin(), vs.end() );
	}
	return values;
}


	}
}



#endif