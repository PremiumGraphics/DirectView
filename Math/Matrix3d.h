#ifndef __CRYSTAL_MATH_MATRIX_3D_H__
#define __CRYSTAL_MATH_MATRIX_3D_H__

#include "Tolerances.h"

#include <vector>
#include <cassert>

namespace Crystal {
	namespace Math {

class Matrix3d 
{
public:
	Matrix3d(void) :
		x00( 1.0), x01( 0.0), x02( 0.0),
		x10( 0.0), x11( 1.0), x12( 0.0),
		x20( 0.0), x21( 0.0), x22( 1.0)
	{}
	
	Matrix3d(
		const float x00, const float x01, const float x02, 
		const float x10, const float x11, const float x12, 
		const float x20, const float x21, const float x22
		):
		x00( x00), x01( x01), x02( x02),
		x10( x10), x11( x11), x12( x12),
		x20( x20), x21( x21), x22( x22)
	{
	}

	~Matrix3d()
	{};

	void setIdentity() {
		x00 = 1.0; x01 = 0.0; x02 = 0.0;
		x10 = 0.0; x11 = 1.0; x12 = 0.0;
		x20 = 0.0; x21 = 0.0; x22 = 1.0;
		assert( isIdentity() );
	}

	void setRotateX( const float angle ) {
		x00 = 1.0f;
		x01 = 0.0f;
		x02 = 0.0f;

		x10 = 0.0f;
		x11 = ::cos( angle );
		x12 = -::sin( angle );

		x20 = 0.0f;
		x21 = ::sin( angle );
		x22 = ::cos( angle );
	}

	void setRotateY( const float angle );

	void setRotateZ( const float angle );

	static Matrix3d Identity() {
		return Matrix3d(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f );
	}

	static Matrix3d Zero();

	static Matrix3d RotateX( const float angle ) {
		Matrix3d matrix;
		matrix.setRotateX( angle );
		return matrix;
	}

	static Matrix3d RotateY( const float angle ) {
		Matrix3d matrix;
		matrix.setRotateY( angle );
		return matrix;
	}

	static Matrix3d RotateZ( const float angle ) {
		Matrix3d matrix;
		matrix.setRotateZ( angle );
		return matrix;
	}

	bool isZero() const;
	
	bool isIdentity() const;

	bool equals( const Matrix3d& rhs ) const {
		return
			Tolerances::isEqualStrictly( x00, rhs.x00 ) &&
			Tolerances::isEqualStrictly( x01, rhs.x01 ) &&
			Tolerances::isEqualStrictly( x02, rhs.x02 ) &&
			Tolerances::isEqualStrictly( x10, rhs.x10 ) &&
			Tolerances::isEqualStrictly( x11, rhs.x11 ) &&
			Tolerances::isEqualStrictly( x12, rhs.x12 ) &&
			Tolerances::isEqualStrictly( x20, rhs.x20 ) &&
			Tolerances::isEqualStrictly( x21, rhs.x21 ) &&
			Tolerances::isEqualStrictly( x22, rhs.x22 );
	}

	float getDeterminant() const;

	Matrix3d getInverse() const;

	Matrix3d product( const Matrix3d& rhs );

	Matrix3d getProduct( const Matrix3d& rhs ) const {
		return Matrix3d( 
				x00 * rhs.x00 + x01 * rhs.x10 + x02 * rhs.x20,
				x00 * rhs.x01 + x01 * rhs.x11 + x02 * rhs.x21,
				x00 * rhs.x02 + x01 * rhs.x12 + x02 * rhs.x22,
				x10 * rhs.x00 + x11 * rhs.x10 + x12 * rhs.x20,
				x10 * rhs.x01 + x11 * rhs.x11 + x12 * rhs.x21,
				x10 * rhs.x02 + x11 * rhs.x12 + x12 * rhs.x22,
				x20 * rhs.x00 + x21 * rhs.x10 + x22 * rhs.x20,
				x20 * rhs.x01 + x21 * rhs.x11 + x22 * rhs.x21,
				x20 * rhs.x02 + x21 * rhs.x12 + x22 * rhs.x22);
	}

	Matrix3d scale( const float factor );

	Matrix3d getScaled( const float factor ) const;

	Matrix3d add( const Matrix3d& rhs ) {
		x00 += rhs.x00;
		x01 += rhs.x01;
		x02 += rhs.x02;

		x10 += rhs.x10;
		x11 += rhs.x11;
		x12 += rhs.x12;

		x20 += rhs.x20;
		x21 += rhs.x21;
		x22 += rhs.x22;

		return *this;
	}

	Matrix3d getAdd( const Matrix3d& rhs ) const;

	bool operator==( const Matrix3d& rhs ) const;

	Matrix3d operator+( const Matrix3d& rhs ) const;

	const Matrix3d operator+=(const Matrix3d& rhs);

	Matrix3d operator-( const Matrix3d& rhs ) const;
	
	const Matrix3d operator-=( const Matrix3d& rhs );
	
	Matrix3d operator*( const Matrix3d& rhs ) const;
	
	const Matrix3d operator*=( const Matrix3d& rhs );

	float getX00() const { return x00; }

	float getX01() const { return x01; }

	float getX02() const { return x02; }

	float getX10() const { return x10; }

	float getX11() const { return x11; }

	float getX12() const { return x12; }

	float getX20() const { return x20; }

	float getX21() const { return x21; }

	float getX22() const { return x22; }

	std::vector< float > toArray4x4() const {
		std::vector< float > val(16);
		val[0] = x00; val[1] = x01; val[2] = x02; val[3] = 0.0f;
		val[4] = x10; val[5] = x11; val[6] = x12; val[7] = 0.0f;
		val[8] = x20; val[9] = x21; val[10] = x22; val[11] = 0.0f;
		val[12] = 0.0f; val[13] = 0.0f; val[14] = 0.0f; val[15] = 1.0f;
		return val;
	}

private:
	float x00, x01, x02;
	float x10, x11, x12;
	float x20, x21, x22;
};

	}
}

#endif