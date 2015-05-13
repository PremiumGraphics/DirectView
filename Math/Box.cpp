#include "Box.h"

#include "Vector3d.h"

#include <cassert>

#include <sstream>
#include <algorithm>

using namespace Crystal::Math;

Box::Box() : Box( Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f) )
{
}

Box::Box(const Vector3d& pointX, const Vector3d& pointY) :
	maxX( (pointX.getX() > pointY.getX() ) ? pointX.getX() : pointY.getX() ),
	minX( (pointX.getX() < pointY.getX() ) ? pointX.getX() : pointY.getX() ),
	maxY( (pointX.getY() > pointY.getY() ) ? pointX.getY() : pointY.getY() ),
	minY( (pointX.getY() < pointY.getY() ) ? pointX.getY() : pointY.getY() ),
	maxZ( (pointX.getZ() > pointY.getZ() ) ? pointX.getZ() : pointY.getZ() ),
	minZ( (pointX.getZ() < pointY.getZ() ) ? pointX.getZ() : pointY.getZ() )
{
	assert( isValid() );
}

Box Box::Unit()
{
	return Box();
}

void Box::add(const Vector3d& v)
{
	minX = std::min( minX, v.getX() );
	minY = std::min( minY, v.getY() );
	minZ = std::min( minZ, v.getZ() );

	maxX = std::max( maxX, v.getX() );
	maxY = std::max( maxY, v.getY() );
	maxZ = std::max( maxZ, v.getZ() );
}

void Box::add(const Box& b)
{
	minX = std::min( minX, b.getMinX() );
	minY = std::min( minY, b.getMinY() );
	minZ = std::min( minZ, b.getMinZ() );

	maxX = std::max( maxX, b.getMaxX() );
	maxY = std::max( maxY, b.getMaxY() );
	maxZ = std::max( maxZ, b.getMaxZ() );
}

Vector3d Box::getCenter() const
{
	return Vector3d( (getMin() + getMax()).scale( 0.5 ) );
}
	
float Box::getVolume() const
{
	return (maxX - minX) * (maxY - minY) * (maxZ - minZ);
}
	
Vector3d Box::getMax() const
{
	return Vector3d( maxX, maxY, maxZ );
}
	
Vector3d Box::getMin() const
{
	return Vector3d( minX, minY, minZ );
}

bool Box::isInterior(const Vector3d &point) const
{
	const bool xIsInterior = ( minX < point.getX() && point.getX() < maxX );
	const bool yIsInterior = ( minY < point.getY() && point.getY() < maxY );
	const bool zIsInterior = ( minZ < point.getZ() && point.getZ() < maxZ );
	return xIsInterior && yIsInterior && zIsInterior;
}
	
bool Box::isExterior(const Vector3d &point) const 
{
	return !isInterior(point);
}
	
void Box::outerOffset(const float offsetLength)
{
	minX -= offsetLength;
	minY -= offsetLength;
	minZ -= offsetLength;
	maxX += offsetLength;
	maxY += offsetLength;
	maxZ += offsetLength;
	assert( isValid() );
}
	
Box Box::getOuterOffset(const float offsetLength) const
{
	Box box = *this;
	box.outerOffset( offsetLength );
	return box;
}

void Box::innerOffset(const float offsetLength)
{
	outerOffset( -offsetLength );
	assert( isValid() );
}

Box Box::getInnerOffset(const float offsetLength) const
{
	return getOuterOffset( -offsetLength );
}

Vector3dVector Box::toPoints( const float divideLength ) const
{
	Vector3dVector points;
	for( float x = minX; x <= maxX; x+= divideLength ) {
		for( float y = minY; y <= maxY; y += divideLength ) {
			for( float z = minZ; z <= maxZ; z += divideLength ) {
				points.push_back( Vector3d( x, y, z ) );
			}
		}
	}
	return points;
}

Vector3d Box::getLength() const {
	return Vector3d( maxX - minX, maxY - minY, maxZ - minZ );
}

bool Box::isValid() const
{
	// k‘Þ‚µ‚Ä‚¢‚Ä‚à‘Ã“–‚Æ‰¼’èD
	return 
		( minX <= maxX ) && ( minY <= maxY ) && ( minZ <= maxZ );
}

bool Box::isShirinked() const
{
	return
		( minX == maxX ) && ( minY == maxY ) && ( minZ == maxZ );
}

bool Box::equals(const Box& rhs) const
{
	return
		Tolerancef::isEqualLoosely( minX, rhs.minX ) &&
		Tolerancef::isEqualLoosely( minY, rhs.minY ) &&
		Tolerancef::isEqualLoosely( minZ, rhs.minZ ) &&
		Tolerancef::isEqualLoosely( maxX, rhs.maxX ) &&
		Tolerancef::isEqualLoosely( maxY, rhs.maxY ) &&
		Tolerancef::isEqualLoosely( maxZ, rhs.maxZ );
}