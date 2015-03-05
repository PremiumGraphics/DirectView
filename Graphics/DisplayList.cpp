#include "DisplayList.h"

#include "Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Face* f)
{
	const Vector3dVector& positions = f->getPositions();
	this->vertices = toArray(positions);
}


DisplayList::DisplayList(Polygon* polygon)
{
	this->vertices = toArray( polygon->getPositions() );
}