#ifndef __CRSYTAL_MATH_VECTOR_2D_H__
#define __CRSYTAL_MATH_VECTOR_2D_H__

#include <cmath>
#include <vector>
#include "Tolerance.h"

namespace Crystal{
	namespace Math{

template< typename T >
class Vector2d final
{
public:
	
	Vector2d::Vector2d(void) :
		x( 0.0 ), y( 0.0 )
	{}

	Vector2d( const T x, const T y ) :
		x( x), y( y)
	{}


	Vector2d( const Vector2d& start, const Vector2d& end ) :
		x( end.x - start.x ),
		y( end.y - start.y )
	{}

	static Vector2d Zero() { return Vector2d( 0.0f, 0.0f ); }

	static Vector2d UnitX() { return Vector2d( 1.0f, 0.0f ); }

	static Vector2d UnitY() { return Vector2d( 0.0f, 1.0f ); }

	T getLengthSquared() const {
		return x * x + y * y;
	}

	T getLength() const {
		return ::sqrt( getLengthSquared() );
	}
	
	T getDistance( const Vector2d& rhs ) const {
		return ::sqrt( getDistanceSquared( rhs ) );
	}

	T getDistanceSquared( const Vector2d& rhs ) const {
		return pow( x - rhs.x, 2 ) + pow( y - rhs.y, 2 );
	}

	Vector2d scale( const T factor ) {
		x *= factor;
		y *= factor;
		return *this;
	}

	Vector2d scale( const T xFactor, const T yFactor ) {
		x *= xFactor;
		y *= yFactor;
		return *this;
	}

	Vector2d getScaled( const T factor ) const {
		return Vector2d( x * factor, y * factor );
	}

	Vector2d normalize() {
		const T length = getLength();
		x /= length;
		y /= length;
		return *this;
	}

	Vector2d getNormalized() const {
		Vector2d<T> vector = *(this);
		return vector.normalize();
	}

	bool isNormalized() const {
		return Tolerance<T>::isEqualLoosely( getLength(), 1.0 );
	}

	bool equals( const Vector2d&rhs ) const {
		return Tolerance<T>::isEqualLoosely( getDistanceSquared( rhs ) );
	}

	bool operator==( const Vector2d& rhs ) const {
		return equals( rhs );
	}

	bool operator!=(const Vector2d& rhs) const {
		return !equals( rhs );
	}

	Vector2d operator+(const Vector2d& rhs) const {
		return Vector2d<T>( x + rhs.x, y + rhs.y );
	}

	Vector2d operator-(const Vector2d& rhs) const {
		return Vector2d( x - rhs.x, y - rhs.y );
	}

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

	Vector2d operator*(const T factor) const {
		Vector2d<T> vector( *this );
		return vector.scale( factor );
	}

	Vector2d operator/(const T factor) const {
		Vector2d<T> vector( *this );
		return vector.scale( 1.0f / factor );
	}
	
	Vector2d operator*=( const T factor ) { return scale( factor ); }

	Vector2d operator/=( const T factor ) { return scale( 1.0f / factor ); }

	/*
	Vector3d getMult(const Matrix2d& matrix) const;
	
	const Vector3d Vector3d::operator*( const Matrix3d& rhs ) const;
	*/

public:
	T getX() const { return x; }

	T getY() const { return y; }

	void setX( const T x ) { this->x = x; }

	void setY( const T y ) { this->y = y; }

	std::vector<T> toArray() const {
		std::vector<T> val(2);
		val[0] = x;
		val[1] = y;
		return val;
	}

private:
	T x;
	T y;
};


template< typename T >
static Vector2d<T> operator*( float factor, const Vector2d<T>& rhs ) { return rhs.getScaled( factor ); }

template< typename T >
static Vector2d<T> operator/( float factor, const Vector2d<T>& rhs ) { return rhs.getScaled( 1.0f / factor ); }

	}
}



#endif