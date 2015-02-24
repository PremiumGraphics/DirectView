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

	void setIdentity() { *this = Identity();  }

	void setRotateX( const float angle ) { *this = RotateX( angle ); }

	void setRotateY(const float angle) { *this = RotateZ( angle ); }

	void setRotateZ(const float angle) {
		x00 = ::cos(angle);
		x01 = -::sin(angle);
		x02 = 0.0f;

		x10 = ::sin(angle);
		x11 = ::cos(angle);
		x12 = 0.0f;

		x20 = 0.0f;
		x21 = 0.0f;
		x22 = 1.0f;
	}

	static Matrix3d Identity() {
		return Matrix3d(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f );
	}

	static Matrix3d Zero() {
		return Matrix3d(
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f);
	}

	static Matrix3d RotateX( const float angle ) {
		return Matrix3d(
			1.0f, 0.0f, 0.0f,
			0.0f, ::cos(angle), -::sin(angle),
			0.0f, ::sin(angle), ::cos(angle));
	}

	static Matrix3d RotateY( const float angle ) {
		return Matrix3d
			(
			::cos(angle), 0.0f,::sin(angle),
			0.0f, 1.0f, 0.0f,
			-::sin(angle), 0.0f, ::cos(angle)
			);
	}

	static Matrix3d RotateZ( const float angle ) {
		Matrix3d matrix;
		matrix.setRotateZ( angle );
		return matrix;
	}

	bool isZero() const { return this->equals(Matrix3d::Zero()); }
	
	bool isIdentity() const {
		Matrix3d identityMatrix(
			1.0, 0.0, 0.0,
			0.0, 1.0, 0.0,
			0.0, 0.0, 1.0);
		return this->equals(identityMatrix);
	}

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

	float getDeterminant() const {
		return
			x00 * x11 * x22
			+ x02 * x10 * x21
			+ x20 * x01 * x12
			- x02 * x11 * x20
			- x00 * x12 * x21
			- x01 * x10 * x22;
	}

	Matrix3d getInverse() const {
		const float denominator = getDeterminant();
		assert(!Tolerances::isEqualStrictly(denominator));

		const float i00 = x11 * x22 - x12 * x21;
		const float i01 = x21 * x02 - x22 * x01;
		const float i02 = x01 * x12 - x02 * x11;

		const float i10 = x12 * x20 - x10 * x22;
		const float i11 = x22 * x00 - x20 * x02;
		const float i12 = x02 * x10 - x00 * x12;

		const float i20 = x10 * x21 - x11 * x20;
		const float i21 = x20 * x01 - x21 * x00;
		const float i22 = x00 * x11 - x01 * x10;

		Matrix3d matrix(i00, i01, i02,
			i10, i11, i12,
			i20, i21, i22);
		matrix.scale(1.0f / denominator);
		return matrix;
	}

	Matrix3d product(const Matrix3d& rhs) { return *this = getProduct(rhs); }

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

	Matrix3d scale(const float factor) {
		x00 *= factor; x01 *= factor; x02 *= factor;
		x10 *= factor; x11 *= factor; x12 *= factor;
		x20 *= factor; x21 *= factor; x22 *= factor;
		return *this;
	}

	Matrix3d getScaled(const float factor) const {
		Matrix3d matrix = *this;
		return matrix.scale(factor);
	}

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

	Matrix3d getAdd(const Matrix3d& rhs) const {
		Matrix3d matrix = *this;
		return matrix.add(rhs);
	}

	bool operator==(const Matrix3d& rhs) const { return this->equals(rhs); }

	Matrix3d operator+(const Matrix3d& rhs) const { return getAdd(rhs); }

	const Matrix3d operator+=(const Matrix3d& rhs) { return add(rhs); }

	Matrix3d operator-(const Matrix3d& rhs) const { return getAdd(rhs.getScaled(-1.0)); }
	
	const Matrix3d operator-=(const Matrix3d& rhs) { return add(rhs.getScaled(-1.0)); }
	
	Matrix3d operator*(const Matrix3d& rhs) const { return getProduct(rhs); }
	
	const Matrix3d operator*=(const Matrix3d& rhs) { return product(rhs); }

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
		return {
			x00, x01, x02, 0.0f,
			x10, x11, x12, 0.0f,
			x20, x21, x22, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

private:
	float x00, x01, x02;
	float x10, x11, x12;
	float x20, x21, x22;
};

	}
}

#endif