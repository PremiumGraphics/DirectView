#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;


Vector3dVector Face::getNormals() const
{
	Vector3dVector normals;
	for (const HalfEdgeSPtr& e : edges) {
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
	for (const HalfEdgeSPtr& e : edges) {
		texCoords.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			texCoords.push_back(e->getEnd()->getNormal());
		}
	}
	return texCoords;

}


std::shared_ptr< Face > FaceBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		const VertexSPtr& v = getVertexBuilder().build(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0));
		vertices.push_back(v);
	}
	const HalfEdgeList& edges = eBuilder.buildClosedFromVertices( vertices);
	return std::shared_ptr<Face>(new Face(edges, nextId++));
}

std::shared_ptr< Face > FaceBuilder::buildQuad()
{
	vertices = {
		getVertexBuilder().build(Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder().build(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder().build(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder().build(Vector3d(1.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0))
	};

	const HalfEdgeList& edges = eBuilder.buildClosedFromVertices( vertices);
	FaceSPtr f(std::shared_ptr<Face>(new Face(edges, nextId++)));
	f->setPolygon(polygon);
	return f;
}