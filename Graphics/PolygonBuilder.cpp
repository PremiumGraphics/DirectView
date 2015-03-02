#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	positions.push_back(Vector3d(0.0, 1.0, 0.0));
	positions.push_back(Vector3d(0.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 1.0, 0.0));

	normals.push_back(Vector3d(0.0, 0.0, 1.0));

	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	faces.push_back(f);
}

void PolygonBuilder::buildBox()
{
	positions.push_back(Vector3d(0.0, 1.0, 1.0));
	positions.push_back(Vector3d(0.0, 0.0, 1.0));
	positions.push_back(Vector3d(1.0, 0.0, 1.0));
	positions.push_back(Vector3d(1.0, 1.0, 1.0));

	positions.push_back(Vector3d(0.0, 1.0, 0.0));
	positions.push_back(Vector3d(0.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 0.0, 0.0));
	positions.push_back(Vector3d(1.0, 1.0, 0.0));

	normals.push_back(Vector3d(0.0, 0.0, 1.0));
	normals.push_back(Vector3d(0.0, 0.0, -1.0));
	normals.push_back(Vector3d(1.0, 0.0, 0.0));
	normals.push_back(Vector3d(-1.0, 0.0, 0.0));
	normals.push_back(Vector3d(0.0, -1.0, 0.0));
	normals.push_back(Vector3d(0.0, 1.0, 0.0));

	faces.push_back(Face({ 0, 1, 2, 3 }, { 0, 0, 0, 0 }));
	faces.push_back(Face({ 4, 5, 6, 7 }, { 1, 1, 1, 1 }));
	faces.push_back(Face({ 0, 4, 1, 5 }, { 2, 2, 2, 2 }));
	faces.push_back(Face({ 1, 5, 2, 6 }, { 3, 3, 3, 3 }));
	faces.push_back(Face({ 2, 6, 3, 7 }, { 4, 4, 4, 4 }));
	faces.push_back(Face({ 3, 7, 4, 8 }, { 5, 5, 5, 5 }));
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
	Face f0;
	{
		std::vector< unsigned int > vs;
		vs.push_back(faces[0].getVertexIds()[0]);
		vs.push_back(faces[0].getVertexIds()[1]);
		vs.push_back(faces[1].getVertexIds()[0]);
	}
	{
		std::vector< unsigned int > vs;
		vs.push_back(faces[1].getVertexIds()[0]);
		vs.push_back(faces[1].getVertexIds()[1]);
		vs.push_back(faces[0].getVertexIds()[0]);

	}
	//f0.setVertexIds({ faces.front });
}

void PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		std::vector<unsigned int> normalIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0 / vDivideNumber * k;
			const float vRadius = vAngle *Tolerances::getPI() / 180.0f;

			const float uAngle = 360.0 / uDivideNumber * i;
			const float rad = uAngle *Tolerances::getPI() / 180.0f;
			positions.push_back(Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius );
			normals.push_back(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
			vertexIds.push_back(i);
			normalIds.push_back(i);
		}
	}
	//f.setVertexIds(vertexIds);
	//f.setNormalIds(normalIds);
}