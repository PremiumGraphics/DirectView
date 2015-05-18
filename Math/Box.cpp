#include "Box.h"

#include "Vector3d.h"

#include <cassert>

#include <sstream>
#include <algorithm>

using namespace Crystal::Math;


	
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

