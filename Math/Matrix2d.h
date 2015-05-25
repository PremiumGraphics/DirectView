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
		Matrix2d(1, 0, 0, 1)
	{
	}
	
	Matrix2d(
		const T x00, const T x01, 
		const T x10, const T x11
		) 
	{
		x[0][0] = x00;
		x[0][1] = x01;
		x[1][0] = x10;
		x[1][1] = x11;

	}

	~Matrix2d()
	{};

	void setIdentity() {
		x[0][0] = 1;
		x[0][1] = 0;
		x[1][0] = 0;
		x[1][1] = 1;
	}

	void setRotate( const T angle ) {
		x[0][0] =  ::cos( angle );
		x[0][1] = -::sin( angle );
		x[1][0] =  ::sin( angle );
		x[1][1] =  ::cos( angle );
	}

	static Matrix2d Identity() {
		return Matrix2d( 1, 0, 0, 1 );
	}

	static Matrix2d<T> Zero() {
		return Matrix2d( 0, 0, 0, 0 );
	}

	static Matrix2d Rotate( const T angle )
	{
		Matrix2d matrix;
		matrix.setRotate( angle );
		return matrix;
	}

	bool equals( const Matrix2d& rhs ) const {
		return
			Tolerance<T>::isEqualStrictly( x[0][0], rhs.x[0][0] ) &&
			Tolerance<T>::isEqualStrictly( x[0][1], rhs.x[0][1] ) &&
			Tolerance<T>::isEqualStrictly( x[1][0], rhs.x[1][0] ) &&
			Tolerance<T>::isEqualStrictly( x[1][1], rhs.x[1][1] );
	}

	T getDeterminant() const {
		return x[0][0] * x[1][1] - x[1][0] * x[0][1];
	}

	bool hasInverse() const {
		const T denominator = getDeterminant();
		return !Tolerance<T>::isEqualStrictly( denominator, 0.0 );
	}

	Matrix2d getInverse() const {
		assert( hasInverse() );
		const T denominator = getDeterminant();
		//assert( !Tolerancef::isEqualStrictly( denominator ) );
	
		const T xx00 = x[1][1] / denominator;
		const T xx01 = -x[0][1] / denominator;
		const T xx10 = -x[1][0] / denominator;
		const T xx11 = x[0][0] / denominator;

		return Matrix2d<T>( xx00, xx01, xx10, xx11 );
	}

	Matrix2d<T> product( const Matrix2d<T>& rhs ) {
		return *this = getProduct(rhs);
	}

	Matrix2d getProduct( const Matrix2d& rhs ) const {
		return Matrix2d
			( 
				getX00() * rhs.getX00() + getX01() * rhs.getX10(),
				getX00() * rhs.getX01() + getX01() * rhs.getX11(),
				getX10() * rhs.getX00() + getX11() * rhs.getX10(),
				getX10() * rhs.getX01() + getX11() * rhs.getX11()
			);
	}

	Matrix2d scale( const T factor ) {
		x[0][0] *= factor;
		x[0][1] *= factor;
		x[1][0] *= factor;
		x[1][1] *= factor;
		return *this;
	}

	Matrix2d getScaled( const T factor ) const {
		Matrix2d matrix = *this;
		return matrix.scale( factor);
	}

	Matrix2d add( const Matrix2d& rhs ) {
		x[0][0] += rhs.x[0][0];
		x[0][1] += rhs.x[0][1];
		x[1][0] += rhs.x[1][0];
		x[1][1] += rhs.x[1][1];
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

	T getX00() const { return x[0][0]; }

	T getX01() const { return x[0][1]; }

	T getX10() const { return x[1][0]; }

	T getX11() const { return x[1][1]; }

	std::vector< T > toArray2x2() const {
		std::vector< T > val(4);
		val[0] = getX00(); val[1] = getX01(); 
		val[2] = getX10(); val[3] = getX11();
		return val;
	}

private:
	//T x00, x01;
	//T x10, x11;
	std::array<  std::array< T, 2 >, 2 > x;
};

	}
}

#endif