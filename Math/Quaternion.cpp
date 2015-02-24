#include "Quaternion.h"

#include "Matrix3d.h"
#include "Tolerances.h"

#include <cassert>

using namespace Crystal::Math;

Quaternion::Quaternion( void ) : 
	x( 0.0), y( 0.0), z( 0.0), w( 1.0) 
{
}
	
Quaternion::Quaternion( const float x, const float y, const float z, const float w ) : 
	x( x), y( y), z( z), w( w)
{
}
	
Quaternion::Quaternion( const Vector3d& axis, const float angle ) :
	x( axis.getX() * sin(angle * 0.5f) ), 
	y( axis.getY() * sin(angle * 0.5f) ), 
	z( axis.getZ() * sin(angle * 0.5f) ), 
	w( cos(angle * 0.5f) )
{
	assert( axis.isNormalized() );
}

Matrix3d<float> Quaternion::toMatrix() const
{
	const float x00 = ( 1.0f - 2.0f * y * y - 2.0f * z * z );
	const float x01 = ( 2.0f * x * y - 2.0f * z * w );
	const float x02 = ( 2.0f * x * z + 2.0f * y * w );

	const float x10 = ( 2.0f * x * y + 2.0f * z * w );
	const float x11 = ( 1.0f - 2.0f * x * x - 2.0f * z * z );
	const float x12 = ( 2.0f * y * z - 2.0f * x * w );
	
	const float x20 = ( 2.0f * x * z - 2.0f * y * w );
	const float x21 = ( 2.0f * y * z + 2.0f * x * w );
	const float x22 = ( 1.0f - 2.0f * x * x - 2.0f * y * y);

	return Matrix3d<float>(
		x00, x01, x02,
		x10, x11, x12,
		x20, x21, x22
		);
}

Quaternion& Quaternion::operator+=( const Quaternion& rhs )
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	w += rhs.w;
	return *(this);
}

float Quaternion::getNorm() const
{
	return sqrt( pow( x, 2 ) + pow( y, 2 ) + pow( z, 2 ) + pow( w, 2 ) );
}

Quaternion& Quaternion::normalize()
{
	const float norm = getNorm();
	x /= norm;
	y /= norm;
	z /= norm;
	z /= norm;
	assert( isNormalized() );
	return *this;
}
	
bool Quaternion::isNormalized() const
{
	return Tolerances::isEqualStrictly( getNorm(), 1.0 );
}

void Quaternion::getMult( const Quaternion& q1, const Quaternion& q2 )
{
	const float pw = q1.getW();
	const float px = q1.getX();
	const float py = q1.getY();
	const float pz = q1.getZ();

	const float qw = q2.getW();
	const float qx = q2.getX();
	const float qy = q2.getY();
	const float qz = q2.getZ();

	this->w = pw * qw - px * qx - py * qy - pz * qz;
	this->x = pw * qx + px * qw + py * qz - pz * qy;
	this->y = pw * qy - px * qz + py * qw + pz * qx;
	this->z = pw * qz + px * qy - py * qx + pz * qw;
}