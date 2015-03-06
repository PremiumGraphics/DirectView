#include "FaceBuilder.h"

#include "Polygon.h"

#include <cassert>
#include <vector>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void FaceBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(
			new Vertex(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0), i));
	}
	const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
	faces.push_back( new Face(edges, nextId++) );
}

void FaceBuilder::buildQuad()
{
	vertices = {
		new Vertex(Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0), 0),
		new Vertex(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0), 1),
		new Vertex(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0), 2),
		new Vertex(Vector3d(1.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0), 3)
	};

	const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
	faces = { new Face(edges, nextId++) };
}