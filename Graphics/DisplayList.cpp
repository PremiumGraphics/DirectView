#include "DisplayList.h"

#include "Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Polygon* polygon)
{
	this->vertices = toArray( polygon->getPositions() );
	this->normals = toArray(polygon->getNormals());
	this->texCoords = toArray(polygon->getTexCoords());
}