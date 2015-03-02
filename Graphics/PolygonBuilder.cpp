#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	const unsigned int pIndex = positions.size();
	positions.push_back(Vector3d(0.0, 1.0, 0.0));
	positions.push_back(Vector3d(0.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 1.0, 0.0));

	const unsigned int nIndex = normals.size();
	normals.push_back(Vector3d(0.0, 0.0, 1.0));

	Face f;
	f.setVertexIds({ pIndex, pIndex+1, pIndex+2, pIndex+3 });
	f.setNormalIds({ nIndex, nIndex, nIndex, nIndex });
	faces.push_back(f);
}

void PolygonBuilder::buildBox()
{
	const unsigned int pIndex = positions.size();
	const unsigned int nIndex = normals.size();

	buildQuad();
	for (Vector3d& position : positions) {
		position += Vector3d(0.0, 0.0, 1.0);
	}
	buildQuad();

	Face f0;
	f0.setVertexIds({ pIndex, pIndex + 4, pIndex + 1, pIndex + 5 });
	faces.push_back(f0);
	Face f1;
	f1.setVertexIds({ pIndex + 1, pIndex + 5, pIndex + 2, pIndex + 6 });
	faces.push_back(f1);
	Face f2;
	f2.setVertexIds({ pIndex + 2, pIndex + 6, pIndex + 3, pIndex + 7 });
	faces.push_back(f2);
	Face f3;
	f3.setVertexIds({ pIndex + 3, pIndex + 7, pIndex + 4, pIndex + 8 });
	faces.push_back(f3);
}

void PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	std::vector<unsigned int> vertexIds;
	std::vector<unsigned int> normalIds;

	Face f;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0 / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		positions.push_back(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		vertexIds.push_back(i);
		normalIds.push_back(0);
	}
	normals.push_back(Vector3d(0.0, 0.0, 1.0));
	f.setVertexIds(vertexIds);
	f.setNormalIds(normalIds);
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
