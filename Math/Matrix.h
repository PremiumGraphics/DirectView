#ifndef __CRYSTAL_MATH_MATRIX_3D_H__
#define __CRYSTAL_MATH_MATRIX_3D_H__

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

	void setRotate(const T angle) {
		x[0][0] = ::cos(angle);
		x[0][1] = -::sin(angle);
		x[1][0] = ::sin(angle);
		x[1][1] = ::cos(angle);
	}

	static Matrix Identity() {
		return Matrix(1, 0, 0, 1);
	}

	static Matrix<T, DIM> Zero() {
		return Matrix(0, 0, 0, 0);
	}

	static Matrix Rotate(const T angle)
	{
		Matrix matrix;
		matrix.setRotate(angle);
		return matrix;
	}

	bool equals(const Matrix& rhs) const {
		return
			Tolerance<T>::isEqualStrictly(x[0][0], rhs.x[0][0]) &&
			Tolerance<T>::isEqualStrictly(x[0][1], rhs.x[0][1]) &&
			Tolerance<T>::isEqualStrictly(x[1][0], rhs.x[1][0]) &&
			Tolerance<T>::isEqualStrictly(x[1][1], rhs.x[1][1]);
	}

	T getDeterminant() const {
		return x[0][0] * x[1][1] - x[1][0] * x[0][1];
	}

	bool hasInverse() const {
		const T denominator = getDeterminant();
		return !Tolerance<T>::isEqualStrictly(denominator, 0.0);
	}

	Matrix getInverse() const {
		assert(hasInverse());
		const T denominator = getDeterminant();
		//assert( !Tolerancef::isEqualStrictly( denominator ) );

		const T xx00 = x[1][1] / denominator;
		const T xx01 = -x[0][1] / denominator;
		const T xx10 = -x[1][0] / denominator;
		const T xx11 = x[0][0] / denominator;

		return Matrix(xx00, xx01, xx10, xx11);
	}

	Matrix<T, DIM> product(const Matrix& rhs) {
		return *this = getProduct(rhs);
	}

	Matrix<T, DIM> getProduct(const Matrix& rhs) const {
		return Matrix
			(
			getX00() * rhs.getX00() + getX01() * rhs.getX10(),
			getX00() * rhs.getX01() + getX01() * rhs.getX11(),
			getX10() * rhs.getX00() + getX11() * rhs.getX10(),
			getX10() * rhs.getX01() + getX11() * rhs.getX11()
			);
	}

	Matrix scale(const T factor) {
		for (auto i = 0; i < 2; ++i) {
			for (auto j = 0; j < 2; ++j) {
				x[i][j] *= factor;
			}
		}
		return *this;
	}

	Matrix getScaled(const T factor) const {
		Matrix matrix = *this;
		return matrix.scale(factor);
	}

	Matrix add(const Matrix& rhs) {
		for (auto i = 0; i < DIM; ++i) {
			for (auto j = 0; j < DIM; ++j) {
				x[i][j] += factor;
			}
		}
		return *this;
	}

	Matrix getAdd(const Matrix& rhs) const {
		Matrix matrix = *this;
		return matrix.add(rhs);
	}

	bool operator==(const Matrix& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Matrix& rhs) const {
		return !equals(rhs);
	}

	Matrix operator+(const Matrix& rhs) const {
		return getAdd(rhs);
	}

	const Matrix operator+=(const Matrix& rhs) {
		return add(rhs);
	}

	Matrix operator-(const Matrix& rhs) const {
		return getAdd(rhs.getScaled(-1.0));
	}

	const Matrix operator-=(const Matrix& rhs) {
		return add(rhs.getScaled(-1.0));
	}

	Matrix operator*(const Matrix& rhs) const {
		return getProduct(rhs);
	}

	const Matrix operator*=(const Matrix& rhs) {
		return product(rhs);
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
using Matrix2d = Matrix < T, 2 >;


template<typename T>
class Matrix3d final
{
public:
	Matrix3d(void) :
		x00( 1.0), x01( 0.0), x02( 0.0),
		x10( 0.0), x11( 1.0), x12( 0.0),
		x20( 0.0), x21( 0.0), x22( 1.0)
	{}
	
	Matrix3d(
		const T x00, const T x01, const T x02, 
		const T x10, const T x11, const T x12, 
		const T x20, const T x21, const T x22
		):
		x00( x00), x01( x01), x02( x02),
		x10( x10), x11( x11), x12( x12),
		x20( x20), x21( x21), x22( x22)
	{
	}

	~Matrix3d() = default;

	void setIdentity() { *this = Identity();  }

	void setRotateX( const T angle ) { *this = RotateX( angle ); }

	void setRotateY(const T angle) { *this = RotateY( angle ); }

	void setRotateZ(const T angle) { *this = RotateZ(angle); }

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

	static Matrix3d RotateX( const T angle ) {
		return Matrix3d(
			1.0f, 0.0f, 0.0f,
			0.0f, ::cos(angle), -::sin(angle),
			0.0f, ::sin(angle), ::cos(angle));
	}

	static Matrix3d RotateY( const T angle ) {
		return Matrix3d
			(
			::cos(angle), 0.0f,::sin(angle),
			0.0f, 1.0f, 0.0f,
			-::sin(angle), 0.0f, ::cos(angle)
			);
	}

	static Matrix3d RotateZ( const T angle ) {
		return Matrix3d
			(
			::cos(angle), -::sin(angle), 0.0f,
			::sin(angle), ::cos(angle), 0.0f,
			0.0f, 0.0f, 1.0f
			);
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
			Tolerance<T>::isEqualLoosely( x00, rhs.x00 ) &&
			Tolerance<T>::isEqualLoosely( x01, rhs.x01 ) &&
			Tolerance<T>::isEqualLoosely( x02, rhs.x02 ) &&
			Tolerance<T>::isEqualLoosely( x10, rhs.x10 ) &&
			Tolerance<T>::isEqualLoosely( x11, rhs.x11 ) &&
			Tolerance<T>::isEqualLoosely( x12, rhs.x12 ) &&
			Tolerance<T>::isEqualLoosely( x20, rhs.x20 ) &&
			Tolerance<T>::isEqualLoosely( x21, rhs.x21 ) &&
			Tolerance<T>::isEqualLoosely( x22, rhs.x22 );
	}

	T getDeterminant() const {
		return
			x00 * x11 * x22
			+ x02 * x10 * x21
			+ x20 * x01 * x12
			- x02 * x11 * x20
			- x00 * x12 * x21
			- x01 * x10 * x22;
	}

	Matrix3d getInverse() const {
		const T denominator = getDeterminant();
		assert(!Tolerance<T>::isEqualStrictly(denominator));

		const T i00 = x11 * x22 - x12 * x21;
		const T i01 = x21 * x02 - x22 * x01;
		const T i02 = x01 * x12 - x02 * x11;

		const T i10 = x12 * x20 - x10 * x22;
		const T i11 = x22 * x00 - x20 * x02;
		const T i12 = x02 * x10 - x00 * x12;

		const T i20 = x10 * x21 - x11 * x20;
		const T i21 = x20 * x01 - x21 * x00;
		const T i22 = x00 * x11 - x01 * x10;

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

	Matrix3d scale(const T factor) {
		x00 *= factor; x01 *= factor; x02 *= factor;
		x10 *= factor; x11 *= factor; x12 *= factor;
		x20 *= factor; x21 *= factor; x22 *= factor;
		return *this;
	}

	Matrix3d getScaled(const T factor) const {
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

	void setX00(const T x) { this->x00 = x; }

	void setX01(const T x) { this->x01 = x; }

	void setX02(const T x) { this->x02 = x; }

	void setX10(const T x) { this->x10 = x; }

	void setX11(const T x) { this->x11 = x; }

	void setX12(const T x) { this->x12 = x; }

	void setX20(const T x) { this->x20 = x; }

	void setX21(const T x) { this->x21 = x; }

	void setX22(const T x) { this->x22 = x; }

	T getX00() const { return x00; }

	T getX01() const { return x01; }

	T getX02() const { return x02; }

	T getX10() const { return x10; }

	T getX11() const { return x11; }

	T getX12() const { return x12; }

	T getX20() const { return x20; }

	T getX21() const { return x21; }

	T getX22() const { return x22; }

	std::vector< T > toArray4x4() const {
		return {
			x00, x01, x02, 0.0f,
			x10, x11, x12, 0.0f,
			x20, x21, x22, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
		};
	}

private:
	T x00, x01, x02;
	T x10, x11, x12;
	T x20, x21, x22;
};

template< typename T >
class Matrix4d
{
public:
	Matrix4d(void) :
		x(16)
	{
		x[0] = 1.0;		x[1] = 0.0;		x[2] = 0.0;		x[3] = 0.0;
		x[4] = 0.0;		x[5] = 1.0;		x[6] = 0.0;		x[7] = 0.0;
		x[8] = 0.0;		x[9] = 0.0;		x[10] = 1.0;	x[11] = 0.0;
		x[12] = 0.0;	x[13] = 0.0;	x[14] = 0.0;	x[15] = 1.0;
	}

	Matrix4d(
		const T x00, const T x01, const T x02, const T x03,
		const T x10, const T x11, const T x12, const T x13,
		const T x20, const T x21, const T x22, const T x23,
		const T x30, const T x31, const T x32, const T x33
		) :
		x(16)
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

	static Matrix4d RotateX(const T angle) {
		return Matrix4d
			(
			1.0, 0.0, 0.0, 0.0,
			0.0, ::cos(angle), ::sin(angle), 0.0,
			0.0, -::sin(angle), ::cos(angle), 0.0,
			0.0, 0.0, 0.0, 1.0
			);
	}

	static Matrix4d RotateY(const T angle) {
		return Matrix4d
			(
			::cos(angle), 0.0, -::sin(angle), 0.0,
			0.0, 1.0, 0.0, 0.0,
			::sin(angle), 0.0, ::cos(angle), 0.0,
			0.0, 0.0, 0.0, 1.0
			);
	}

	static Matrix4d RotateZ(const T angle) {
		return Matrix4d
			(
			::cos(angle), ::sin(angle), 0.0, 0.0,
			-::sin(angle), ::cos(angle), 0.0, 0.0,
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
		for (int i = 0; i < 4; ++i) {
			y[0 + i] = x[0 + i] * rhs.x[0] + x[4 + i] * rhs.x[1] + x[8 + i] * rhs.x[2] + x[12 + i] * rhs.x[3];
			y[4 + i] = x[0 + i] * rhs.x[4] + x[4 + i] * rhs.x[5] + x[8 + i] * rhs.x[6] + x[12 + i] * rhs.x[7];
			y[8 + i] = x[0 + i] * rhs.x[8] + x[4 + i] * rhs.x[9] + x[8 + i] * rhs.x[10] + x[12 + i] * rhs.x[11];
			y[12 + i] = x[0 + i] * rhs.x[12] + x[4 + i] * rhs.x[13] + x[8 + i] * rhs.x[14] + x[12 + i] * rhs.x[15];
		}
		for (int i = 0; i < 16; ++i) {
			this->x[i] = y[i];
		}
	}

	void operator*=(const Matrix4d& rhs) { multiple(rhs); }

	bool equals(const Matrix4d& rhs) const {
		for (int i = 0; i < 16; ++i) {
			if (!Tolerance<T>::isEqualLoosely(x[i], rhs.x[i])) {
				return false;
			}
		}
		return true;
	}

	bool operator==(const Matrix4d& rhs) const { return equals(rhs); }

	bool operator!=(const Matrix4d& rhs) const { return !equals(rhs); }

	std::vector< T > toArray4x4() const {
		return x;
	}

	void setX00(const T v) { x[0] = v; }

	void setX01(const T v) { x[1] = v; }

	void setX02(const T v) { x[2] = v; }

	void setX03(const T v) { x[3] = v; }

	void setX10(const T v) { x[4] = v; }

	void setX11(const T v) { x[5] = v; }

	void setX12(const T v) { x[6] = v; }

	void setX13(const T v) { x[7] = v; }

	void setX20(const T v) { x[8] = v; }

	void setX21(const T v) { x[9] = v; }

	void setX22(const T v) { x[10] = v; }

	void setX23(const T v) { x[11] = v; }

	void setX30(const T v) { x[12] = v; }

	void setX31(const T v) { x[13] = v; }

	void setX32(const T v) { x[14] = v; }

	void setX33(const T v) { x[15] = v; }

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