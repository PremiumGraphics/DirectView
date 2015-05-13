#ifndef __CRYSTAL_MATH_MATRIX_2D_H__
#define __CRYSTAL_MATH_MATRIX_2D_H__


#include "Tolerance.h"

#include "Vector2d.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {

template< typename T >
class Matrix2d
{
public:
	Matrix2d(void) : 
		x00( 1.0), x01( 0.0),
		x10( 0.0), x11( 1.0)
	{}
	
	Matrix2d(
		const T x00, const T x01, 
		const T x10, const T x11
		) : x00( x00), x01( x01),
		x10( x10), x11( x11)
	{}

	~Matrix2d()
	{};

	void setIdentity() {
		x00 = 1.0; x01 = 0.0;
		x10 = 0.0; x11 = 1.0;
	}

	void setRotate( const T angle ) {
		x00 =  ::cos( angle );
		x01 = -::sin( angle );
		x10 =  ::sin( angle );
		x11 =  ::cos( angle );
	}

	static Matrix2d Identity() {
		return Matrix2d
		(
		1.0f, 0.0f,
		0.0f, 1.0f
		);
	}

	static Matrix2d<T> Zero() {
		return Matrix2d
		(
		0.0f, 0.0f,
		0.0f, 0.0f
		);
	}

	static Matrix2d Rotate( const T angle )
	{
		Matrix2d matrix;
		matrix.setRotate( angle );
		return matrix;
	}

	bool equals( const Matrix2d& rhs ) const {
		return
			Tolerance<T>::isEqualStrictly( x00, rhs.x00 ) &&
			Tolerance<T>::isEqualStrictly( x01, rhs.x01 ) &&
			Tolerance<T>::isEqualStrictly( x10, rhs.x10 ) &&
			Tolerance<T>::isEqualStrictly( x11, rhs.x11 );
	}

	T getDeterminant() const {
		return x00 * x11 - x10 * x01;
	}

	bool hasInverse() const {
		const T denominator = getDeterminant();
		return !Tolerance<T>::isEqualStrictly( denominator, 0.0 );
	}

	Matrix2d getInverse() const {
		assert( hasInverse() );
		const T denominator = getDeterminant();
		//assert( !Tolerancef::isEqualStrictly( denominator ) );
	
		const T xx00 = x11 / denominator;
		const T xx01 = -x01 / denominator;
		const T xx10 = -x10 / denominator;
		const T xx11 = x00 / denominator;

		return Matrix2d<T>( xx00, xx01, xx10, xx11 );
	}

	Matrix2d<T> product( const Matrix2d<T>& rhs ) {
		return *this = getProduct(rhs);
	}

	Matrix2d getProduct( const Matrix2d& rhs ) const {
		return Matrix2d
			( 
				x00 * rhs.x00 + x01 * rhs.x10,
				x00 * rhs.x01 + x01 * rhs.x11,
				x10 * rhs.x00 + x11 * rhs.x10,
				x10 * rhs.x01 + x11 * rhs.x11
			);
	}

	Matrix2d scale( const T factor ) {
		x00 *= factor; x01 *= factor;
		x10 *= factor; x11 *= factor;
		return *this;
	}

	Matrix2d getScaled( const T factor ) const {
		Matrix2d matrix = *this;
		return matrix.scale( factor);
	}

	Matrix2d add( const Matrix2d& rhs ) {
		x00 += rhs.x00;
		x01 += rhs.x01;
		x10 += rhs.x10;
		x11 += rhs.x11;
		return *this;
	}

	Matrix2d getAdd( const Matrix2d& rhs ) const {
		Matrix2d matrix = *this;
		return matrix.add( rhs);
	}

	bool operator==( const Matrix2d& rhs ) const {
		return equals( rhs );
	}

	bool operator!=( const Matrix2d& rhs ) const {
		return !equals( rhs );
	}

	Matrix2d operator+( const Matrix2d& rhs ) const {
		return getAdd( rhs);
	}

	const Matrix2d operator+=(const Matrix2d& rhs ) {
		return add( rhs );
	}

	Matrix2d operator-( const Matrix2d& rhs ) const {
		return getAdd( rhs.getScaled( -1.0) );
	}

	const Matrix2d<T> operator-=( const Matrix2d<T>& rhs ) {
		return add( rhs.getScaled( -1.0) );
	}

	Matrix2d operator*( const Matrix2d& rhs ) const {
		return getProduct( rhs);
	}
	
	const Matrix2d operator*=( const Matrix2d& rhs ) {
		return product( rhs);
	}

	T getX00() const { return x00; }

	T getX01() const { return x01; }

	T getX10() const { return x10; }

	T getX11() const { return x11; }

	std::vector< T > toArray2x2() const {
		std::vector< T > val(4);
		val[0] = x00; val[1] = x01; 
		val[2] = x10; val[3] = x11;
		return val;
	}

private:
	T x00, x01;
	T x10, x11;
};

	}
}

#endif