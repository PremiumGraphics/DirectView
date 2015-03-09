#include "FaceBuilder.h"

#include "Polygon.h"

#include <cassert>
#include <vector>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Face* FaceBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		Vertex* v = vBuilder.build( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0) );
		vertices.push_back(v);
	}
	const HalfEdgeList& edges = eBuilder.createClosedFromVertices(vertices);
	faces.push_back( new Face(edges, nextId++) );
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