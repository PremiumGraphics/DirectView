#include "Matrix3d.h"

#include <cassert>

using namespace Crystal::Math;



void Matrix3d::setRotateY( const float angle )
{
	x00 = ::cos( angle );
	x01 = 0.0f;
	x02 = ::sin( angle );

	x10 = 0.0f;
	x11 = 1.0f;
	x12 = 0.0f;

	x20 = -::sin( angle );
	x21 = 0.0f;
	x22 = ::cos( angle );
}

void Matrix3d::setRotateZ( const float angle )
{
	x00 = ::cos( angle );
	x01 = -::sin( angle );
	x02 = 0.0f;

	x10 = ::sin( angle );
	x11 = ::cos( angle );
	x12 = 0.0f;

	x20 = 0.0f;
	x21 = 0.0f;
	x22 = 1.0f;

}



Matrix3d Matrix3d::Zero() {
	return Matrix3d(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f );
}
	
bool Matrix3d::isZero() const
{
	return this->equals( Matrix3d::Zero() );
}

Matrix3d Matrix3d::scale(const float factor)
{
	x00 *= factor; x01 *= factor; x02 *= factor;
	x10 *= factor; x11 *= factor; x12 *= factor;
	x20 *= factor; x21 *= factor; x22 *= factor;
	return *this;
}

bool Matrix3d::isIdentity() const
{
	Matrix3d identityMatrix( 
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0);
	return this->equals( identityMatrix );
}


Matrix3d Matrix3d::getInverse() const
{
	const float denominator = getDeterminant();
	assert( !Tolerances::isEqualStrictly( denominator ) );
	
	const float i00 = x11 * x22 - x12 * x21;
	const float i01 = x21 * x02 - x22 * x01;
	const float i02 = x01 * x12 - x02 * x11;

	const float i10 = x12 * x20 - x10 * x22;
	const float i11 = x22 * x00 - x20 * x02;
	const float i12 = x02 * x10 - x00 * x12;

	const float i20 = x10 * x21 - x11 * x20;
	const float i21 = x20 * x01 - x21 * x00;
	const float i22 = x00 * x11 - x01 * x10;

	Matrix3d matrix( i00, i01, i02,
		i10, i11, i12,
		i20, i21, i22 );
	matrix.scale( 1.0f / denominator );
	return matrix;
}

Matrix3d Matrix3d::product(const Matrix3d& rhs)
{
	return *this = getProduct(rhs);
}



float Matrix3d::getDeterminant() const
{
	return 
		x00 * x11 * x22
		+ x02 * x10 * x21
		+ x20 * x01 * x12
		- x02 * x11 * x20
		- x00 * x12 * x21
		- x01 * x10 * x22;
}



Matrix3d Matrix3d::getScaled(const float factor) const
{
	Matrix3d matrix = *this;
	return matrix.scale( factor);
}

Matrix3d Matrix3d::getAdd(const Matrix3d& rhs) const
{
	Matrix3d matrix = *this;
	return matrix.add( rhs);
}

bool Matrix3d::operator==(const Matrix3d& rhs) const
{
	return this->equals(rhs);
}

Matrix3d Matrix3d::operator+(const Matrix3d& rhs) const
{
	return getAdd( rhs);
}

const Matrix3d Matrix3d::operator+=(const Matrix3d& rhs)
{
	return add( rhs);
}

Matrix3d Matrix3d::operator-(const Matrix3d& rhs) const
{
	return getAdd( rhs.getScaled( -1.0) );
}
	
const Matrix3d Matrix3d::operator-=(const Matrix3d& rhs)
{
	return add( rhs.getScaled( -1.0) );
}
	
Matrix3d Matrix3d::operator*(const Matrix3d& rhs) const
{
	return getProduct( rhs);
}
	
const Matrix3d Matrix3d::operator*=(const Matrix3d& rhs)
{
	return product( rhs);
}

