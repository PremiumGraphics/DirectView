#include "DisplayList.h"

#include "Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

DisplayList::DisplayList(Face* f)
{
	const Vector3dVector& positions = f->getPositions();
	this->vertices = toArray(positions);
	const Vector3dVector& normals = f->getNormals();
	this->normals = toArray(normals);
	const Vector3dVector& texCoords = f->getTexCoords();
	this->texCoords = toArray(texCoords);
}


DisplayList::DisplayList(Polygon* polygon)
{
	this->vertices = toArray( polygon->getPositions() );
	this->normals = toArray(polygon->getNormals());
}