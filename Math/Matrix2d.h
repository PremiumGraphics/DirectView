#ifndef __CRYSTAL_MATH_MATRIX_2D_H__
#define __CRYSTAL_MATH_MATRIX_2D_H__


#include "Tolerance.h"

#include <vector>
#include <cassert>
#include <array>

namespace Crystal {
	namespace Math {

template< typename T, size_t DIM >
class Matrix
{
public:
	Matrix(void) : 
		Matrix(1, 0, 0, 1)
	{
	}
	
	Matrix(
		const T x00, const T x01, 
		const T x10, const T x11
		) 
	{
		x[0][0] = x00;
		x[0][1] = x01;
		x[1][0] = x10;
		x[1][1] = x11;

	}

	~Matrix()
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

	static Matrix Identity() {
		return Matrix( 1, 0, 0, 1 );
	}

	static Matrix<T,DIM> Zero() {
		return Matrix( 0, 0, 0, 0 );
	}

	static Matrix Rotate( const T angle )
	{
		Matrix matrix;
		matrix.setRotate( angle );
		return matrix;
	}

	bool equals( const Matrix& rhs ) const {
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

	Matrix getInverse() const {
		assert( hasInverse() );
		const T denominator = getDeterminant();
		//assert( !Tolerancef::isEqualStrictly( denominator ) );
	
		const T xx00 = x[1][1] / denominator;
		const T xx01 = -x[0][1] / denominator;
		const T xx10 = -x[1][0] / denominator;
		const T xx11 = x[0][0] / denominator;

		return Matrix( xx00, xx01, xx10, xx11 );
	}

	Matrix<T,DIM> product( const Matrix& rhs ) {
		return *this = getProduct(rhs);
	}

	Matrix<T,DIM> getProduct( const Matrix& rhs ) const {
		return Matrix
			( 
				getX00() * rhs.getX00() + getX01() * rhs.getX10(),
				getX00() * rhs.getX01() + getX01() * rhs.getX11(),
				getX10() * rhs.getX00() + getX11() * rhs.getX10(),
				getX10() * rhs.getX01() + getX11() * rhs.getX11()
			);
	}

	Matrix scale( const T factor ) {
		for (auto i = 0; i < 2; ++i) {
			for (auto j = 0; j < 2; ++j) {
				x[i][j] *= factor;
			}
		}
		return *this;
	}

	Matrix getScaled( const T factor ) const {
		Matrix matrix = *this;
		return matrix.scale( factor);
	}

	Matrix add( const Matrix& rhs ) {
		for (auto i = 0; i < DIM; ++i) {
			for (auto j = 0; j < DIM; ++j) {
				x[i][j] += factor;
			}
		}
		return *this;
	}

	Matrix getAdd( const Matrix& rhs ) const {
		Matrix matrix = *this;
		return matrix.add( rhs);
	}

	bool operator==( const Matrix& rhs ) const {
		return equals( rhs );
	}

	bool operator!=( const Matrix& rhs ) const {
		return !equals( rhs );
	}

	Matrix operator+( const Matrix& rhs ) const {
		return getAdd( rhs);
	}

	const Matrix operator+=(const Matrix& rhs ) {
		return add( rhs );
	}

	Matrix operator-( const Matrix& rhs ) const {
		return getAdd( rhs.getScaled( -1.0) );
	}

	const Matrix operator-=( const Matrix& rhs ) {
		return add( rhs.getScaled( -1.0) );
	}

	Matrix operator*( const Matrix& rhs ) const {
		return getProduct( rhs);
	}
	
	const Matrix operator*=( const Matrix& rhs ) {
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
	std::array<  std::array< T, DIM >, DIM > x;
};

template<typename T>
using Matrix2d = Matrix < T, 2 > ;
	}
}

#endif