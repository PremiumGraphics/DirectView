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


Face* FaceBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		Vertex* v = vBuilder.build(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0));
		vertices.push_back(v);
	}
	const HalfEdgeList& edges = eBuilder.createClosedFromVertices(vertices);
	faces.push_back(new Face(edges, nextId++));
	return faces.back();
}

Face* FaceBuilder::buildQuad()
{
	vertices = {
		vBuilder.build(Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		vBuilder.build(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		vBuilder.build(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		vBuilder.build(Vector3d(1.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0))
	};

	const HalfEdgeList& edges = eBuilder.createClosedFromVertices(vertices);
	faces = { new Face(edges, nextId++) };
	return faces.back();
}