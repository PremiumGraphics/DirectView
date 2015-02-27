#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	positions ={
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 1, 2, 3 });
	faces.push_back(f);
}

void PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	std::vector<unsigned int> vertexIds;
	Face f;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0 / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		normals.push_back(Vector3d(0.0, 0.0, 1.0));
		vertexIds.push_back(i);
	}
	f.setVertexIds(vertexIds);
	f.setNormalIds(vertexIds);
	faces.push_back(f);
}

void PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	buildCircleByNumber(radius, 360.0 / divideAngle);
}

void PolygonBuilder::buildCylinder(const float radius, const float height)
{
	buildCircleByNumber(1.0f,6);
	for (Math::Vector3d& v : positions) {
		v += Vector3d(1.0, 0.0, 0.0);
	}
	buildCircleByNumber(1.0f, 6);
}
