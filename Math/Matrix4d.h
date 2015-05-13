#ifndef __CRYSTAL_MATH_MATRIX_4D_H__
#define __CRYSTAL_MATH_MATRIX_4D_H__

#include "Tolerance.h"

#include <vector>

namespace Crystal{
	namespace Math {

template< typename T >
class Matrix4d
{
public:
	Matrix4d(void) :
	x( 16 )
	{
		x[0] = 1.0;		x[1] = 0.0;		x[2] = 0.0;		x[3] = 0.0;
		x[4] = 0.0;		x[5] = 1.0;		x[6] = 0.0;		x[7] = 0.0;
		x[8] = 0.0;		x[9] = 0.0;		x[10] = 1.0;	x[11] = 0.0;
		x[12] = 0.0;	x[13] = 0.0;	x[14] = 0.0;	x[15] = 1.0;	
	}

	Matrix4d (
		const T x00, const T x01, const T x02, const T x03, 
		const T x10, const T x11, const T x12, const T x13,
		const T x20, const T x21, const T x22, const T x23,
		const T x30, const T x31, const T x32, const T x33
		) :
	x( 16 )
	{
		x[0] = x00;		x[1] = x01;		x[2] = x02;		x[3] = x03;
		x[4] = x10;		x[5] = x11;		x[6] = x12;		x[7] = x13;
		x[8] = x20;		x[9] = x21;		x[10] = x22;	x[11] = x23;
		x[12] = x30;	x[13] = x31;	x[14] = x32;	x[15] = x33;
	}

	~Matrix4d(void)
	{}

	static Matrix4d Zero() {
		return Matrix4d
		(
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f
		);
	}

	static Matrix4d Identity() {
		return Matrix4d
		(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}

	static Matrix4d RotateX( const T angle ) {
		return Matrix4d
		(
			1.0, 0.0, 0.0, 0.0,
			0.0,  ::cos( angle ), ::sin( angle ), 0.0,
			0.0, -::sin( angle ), ::cos( angle ), 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}

	static Matrix4d RotateY( const T angle ) {
		return Matrix4d
		(
			::cos( angle ), 0.0, -::sin( angle ), 0.0,
			0.0, 1.0, 0.0, 0.0,
			::sin( angle ), 0.0, ::cos( angle ), 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}

	static Matrix4d RotateZ( const T angle ) {
		return Matrix4d
		(
			::cos( angle ), ::sin( angle ), 0.0, 0.0,
			-::sin( angle ),::cos( angle ), 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0
		);
	}

	void translate(const T x, const T y, const T z)
	{
		Matrix4d m;
		m.x[12] = x;
		m.x[13] = y;
		m.x[14] = z;
		(*this) *= m;
	}

	void setScale(const T x, const T y, const T z) {
		this->x[0] = x;
		this->x[5] = y;
		this->x[10] = z;
	}

	void multiple(const Matrix4d& rhs)
	{
		T y[16];
		for( int i = 0; i < 4; ++ i ) {
			y[0+i] = x[0+i] * rhs.x[0] + x[4+i] * rhs.x[1] + x[8+i] * rhs.x[2] + x[12+i] * rhs.x[3];
			y[4+i] = x[0+i] * rhs.x[4] + x[4+i] * rhs.x[5] + x[8+i] * rhs.x[6] + x[12+i] * rhs.x[7];
			y[8+i] = x[0+i] * rhs.x[8] + x[4+i] * rhs.x[9] + x[8+i] * rhs.x[10] + x[12+i] * rhs.x[11];
			y[12+i] = x[0+i] * rhs.x[12] + x[4+i] * rhs.x[13] + x[8+i] * rhs.x[14] + x[12+i] * rhs.x[15];
		}
		for( int i = 0; i < 16; ++i ) {
			this->x[i] = y[i];
		}
	}

	void operator*=(const Matrix4d& rhs) { multiple(rhs); }

	bool equals( const Matrix4d& rhs ) const {
		for( int i = 0; i < 16; ++i ) {
			if( !Tolerancef::isEqualLoosely( x[i], rhs.x[i] ) ) {
				return false;
			}
		}
		return true;
	}

	bool operator==( const Matrix4d& rhs ) const { return equals( rhs ); }

	bool operator!=( const Matrix4d& rhs ) const { return !equals( rhs ); }

	std::vector< T > toArray4x4() const {
		return x;
	}

	void setX00( const T v ) { x[0] = v; }

	void setX01( const T v ) { x[1] = v; }

	void setX02( const T v ) { x[2] = v; }

	void setX03( const T v ) { x[3] = v; }

	void setX10( const T v ) { x[4] = v; }

	void setX11( const T v ) { x[5] = v; }

	void setX12( const T v ) { x[6] = v; }

	void setX13( const T v ) { x[7] = v; }

	void setX20( const T v ) { x[8] = v; }

	void setX21( const T v ) { x[9] = v; }

	void setX22( const T v ) { x[10] = v; }

	void setX23( const T v ) { x[11] = v; }

	void setX30( const T v ) { x[12] = v; }

	void setX31( const T v ) { x[13] = v; }

	void setX32( const T v ) { x[14] = v; }

	void setX33( const T v ) { x[15] = v; }

	T getX00() const { return x[0]; }

	T getX01() const { return x[1]; }

	T getX02() const { return x[2]; }

	T getX03() const { return x[3]; }

	T getX10() const { return x[4]; }

	T getX11() const { return x[5]; }

	T getX12() const { return x[6]; }

	T getX13() const { return x[7]; }

	T getX20() const { return x[8]; }

	T getX21() const { return x[9]; }

	T getX22() const { return x[10]; }

	T getX23() const { return x[11]; }

	T getX30() const { return x[12]; }

	T getX31() const { return x[13]; }

	T getX32() const { return x[14]; }

	T getX33() const { return x[15]; }

private:
	std::vector< T > x;
};

	}
}

#endif