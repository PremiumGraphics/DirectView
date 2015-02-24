#include "Vector3d.h"

#include "Matrix3d.h"
#include "Box.h"

#include <sstream>
#include <cassert>

using namespace Crystal::Math;


Vector3d Vector3d::getScaled( const float factor ) const
{
	return Vector3d( x * factor, y * factor, z * factor );
}


bool Vector3d::isZero() const
{
	return Tolerances::isEqualLoosely( getLength() );
}

Vector3d Vector3d::normalize()
{
	const float length = getLength();
	x /= length;
	y /= length;
	z /= length;
	return *this;
}

Vector3d Vector3d::getNormalized() const
{
	Vector3d vector = *(this);
	return vector.normalize();
}


void Vector3d::rotate(const Matrix3d<double>& matrix)
{
	*(this) = getRotated( matrix );
}

Vector3d Vector3d::getRotated( const Matrix3d<double>& matrix ) const
{
	const float x = matrix.getX00() * this->x + matrix.getX01() * this->y + matrix.getX02() * this->z;
	const float y = matrix.getX10() * this->x + matrix.getX11() * this->y + matrix.getX12() * this->z;
	const float z = matrix.getX20() * this->x + matrix.getX21() * this->y + matrix.getX22() * this->z;
		
	return Vector3d( x, y, z );
}

Vector3d Vector3d::getMult( const Matrix3d<float>& matrix ) const
{
	return Vector3d
		( 
		x * matrix.getX00() + y * matrix.getX10() + z * matrix.getX20(),
		x * matrix.getX01() + y * matrix.getX11() + z * matrix.getX21(),
		x * matrix.getX02() + y * matrix.getX12() + z * matrix.getX22()
		);
}
	
const Vector3d Vector3d::operator*( const Matrix3d<float>& rhs ) const 
{
	return getMult( rhs );
}


Vector3d Vector3d::operator-=( const Vector3d& rhs )
{
	x -= rhs.x;
	y -= rhs.y;
	z -= rhs.z;
	return *this;
}

Vector3d Vector3d::operator*( const float factor ) const
{
	Vector3d vector( *this );
	return vector.scale( factor );
}

Vector3d Vector3d::operator/( const float factor ) const
{
	Vector3d vector( *this );
	return vector.scale( 1.0f / factor );
}

