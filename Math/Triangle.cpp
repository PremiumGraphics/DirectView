#include "Triangle.h"

using namespace Crystal::Math;

Vector3d Triangle::getNormal() const
{
	const Vector3d v01( v0, v1 );
	const Vector3d v02( v0, v2 );
	return v01.getOuterProduct( v02 ).getNormalized();
}



/*
Box Triangle::getBoundingBox() const
{
	Vector3dCollection vectors;
	vectors.push_back( v0 );
	vectors.push_back( v1 );
	vectors.push_back( v2 );
	return vectors.getBoundingBox();
}

Vector3dCollection Triangle::toPoints( const float divideLength ) const
{
	Vector3dCollection vectors;
	vectors.push_back( v0 );
	vectors.push_back( v1 );
	vectors.push_back( v2 );

	return vectors;
}
*/

Vector3d Triangle::getCenter() const
{
	return (v0 + v1 + v2) / 3.0f;
}

