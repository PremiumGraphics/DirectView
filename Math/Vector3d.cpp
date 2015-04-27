#include "Vector3d.h"

#include "Matrix3d.h"
#include "Box.h"

#include <sstream>
#include <cassert>

using namespace Crystal::Math;

Vector3d::Vector3d(void) : Vector3d( 0.0f, 0.0f, 0.0f)
{}

Vector3d::Vector3d(float x, float y, float z) :
x(x), y(y), z(z)
{}

Vector3d::Vector3d(const Vector3d& start, const Vector3d& end) :
x(end.x - start.x),
y(end.y - start.y),
z(end.z - start.z)
{}

float Vector3d::getLengthSquared() const
{
	return x * x + y * y + z * z;
}

float Vector3d::getLength() const
{
	return ::sqrt(getLengthSquared());
}


float Vector3d::getDistance(const Vector3d& rhs) const
{
	return ::sqrt(getDistanceSquared(rhs));
}

float Vector3d::getDistanceSquared(const Vector3d& rhs) const
{
	return pow(x - rhs.x, 2) + pow(y - rhs.y, 2) + pow(z - rhs.z, 2);
}

Vector3d Vector3d::scale(const float factor)
{
	x *= factor;
	y *= factor;
	z *= factor;
	return *this;
}

Vector3d Vector3d::scale(const float xFactor, const float yFactor, const float zFactor)
{
	x *= xFactor;
	y *= yFactor;
	z *= zFactor;
	return *this;
}

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
	const auto x = matrix.getX00() * this->x + matrix.getX01() * this->y + matrix.getX02() * this->z;
	const auto y = matrix.getX10() * this->x + matrix.getX11() * this->y + matrix.getX12() * this->z;
	const auto z = matrix.getX20() * this->x + matrix.getX21() * this->y + matrix.getX22() * this->z;
		
	return Vector3d( static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) );
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

std::vector< float > Vector3d::toArray(const std::vector<Vector3d>& vectors) {
	std::vector< float > values;
	for (const Math::Vector3d& v : vectors) {
		const std::vector<float>& vs = v.toArray();
		values.insert(values.end(), vs.begin(), vs.end());
	}
	return values;
}
