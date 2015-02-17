#ifndef __CRYSTAL_MATH_QUATERNION_H__
#define __CRYSTAL_MATH_QUATERNION_H__

#include "Vector3d.h"

namespace Crystal{
	namespace Math{


class Matrix3d;

class Quaternion
{
public:
	
	Quaternion(void);
	
	Quaternion(const float x, const float y, const float z, const float w);
	
	Quaternion(const Vector3d& axis, const float angle);

	Matrix3d toMatrix() const;
	
	Quaternion& operator+=( const Quaternion& rhs );

	float getNorm() const;

	Quaternion& normalize();

	bool isNormalized() const;

	float getX() const { return x; }

	float getY() const { return y; }

	float getZ() const { return z; }

	float getW() const { return w; }

	void setX( const float x ) { this->x = x; }

	void setY( const float y ) { this->y = y; }

	void setZ( const float z ) { this->z = z; }

	void setW( const float w ) { this->w = w; }

	void getMult( const Quaternion& q1, const Quaternion& q2 );

private:
	float x;
	float y;
	float z;
	float w;
};

	}
}

#endif