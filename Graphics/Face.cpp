#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Vector3dVector Face::getPositions() const
{
	Vector3dVector positions;
	for (HalfEdge* e : edges) {
		positions.push_back(e->getStartPosition());
		if (e == edges.back() && isOpen()) {
			positions.push_back(e->getEndPosition());
		}
	}
	return positions;
}

Vector3dVector Face::getNormals() const
{
	Vector3dVector normals;
	for (HalfEdge* e : edges) {
		normals.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			normals.push_back(e->getEnd()->getNormal());
		}
	}
	return normals;
}

Vector3dVector Face::getTexCoords() const
{
	Vector3dVector texCoords;
	for (HalfEdge* e : edges) {
		texCoords.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			texCoords.push_back(e->getEnd()->getNormal());
		}
	}
	return texCoords;

}