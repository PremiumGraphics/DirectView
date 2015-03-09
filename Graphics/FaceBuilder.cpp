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
		vBuilder.build( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0) );
	}
	const HalfEdgeList& edges = HalfEdgeBuilder::createClosedFromVertices(vBuilder.getVertices());
	faces.push_back( new Face(edges, nextId++) );
}

Face* FaceBuilder::buildQuad()
{
	vBuilder.build(Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0));
	vBuilder.build(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0));
	vBuilder.build(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0));
	vBuilder.build(Vector3d(1.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0));

	const HalfEdgeList& edges = HalfEdgeBuilder::createClosedFromVertices(vBuilder.getVertices());
	faces = { new Face(edges, nextId++) };
	return faces.back();
}