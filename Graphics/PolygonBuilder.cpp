#include "PolygonBuilder.h"

#include "FaceBuilder.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	faceBuilder.buildQuad();
}

void PolygonBuilder::buildBox()
{
	const Vector3dVector normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, -1.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0)
	};

	const Vector3dVector positions = {
		Vector3d(0.0, 1.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(1.0, 0.0, 1.0),
		Vector3d(1.0, 1.0, 1.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};

	const VertexVector& vertices = vertexBuilder.buildVerticesFromPositionsAndNormals(positions, normals);

	faceBuilder.build(vertices, { 0, 1, 2, 3 });
	faceBuilder.build(vertices, { 4, 5, 6, 7 });
	faceBuilder.build(vertices, { 0, 1, 5, 4 });
	faceBuilder.build(vertices, { 2, 3, 7, 6 });
	faceBuilder.build(vertices, { 3, 0, 4, 7 });
	faceBuilder.build(vertices, { 5, 1, 2, 6 });

	const FaceVector& faces = faceBuilder.getFaces();
}

void PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	faceBuilder.buildCircleByNumber(radius, divideNumber);
}

void PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	const int howMany = static_cast<int>(360.0f / divideAngle);
	return buildCircleByNumber(radius, howMany);
}

void PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds0;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		vertexIds0.push_back(i);
	}
	faceBuilder.build( vertexBuilder.getVertices(), vertexIds0);
	//faces.push_back( new Face( vertices, vertexIds0, 0 ) );

	std::vector<unsigned int> vertexIds1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
		vertexIds1.push_back(divideNumber + i);
	}
	faceBuilder.build( vertexBuilder.getVertices(), vertexIds1);

	for (unsigned int i = 0; i < divideNumber-1; ++i) {

		const unsigned int v0 = vertexIds0[i];
		const unsigned int v1 = vertexIds0[i+1];
		const unsigned int v2 = vertexIds1[i+1];
		const unsigned int v3 = vertexIds1[i];
		std::vector<unsigned int> vertexIds2 = { v0, v1, v2, v3 };
		faceBuilder.build( vertexBuilder.getVertices(), vertexIds2);
	}

	{
		const unsigned int v0 = vertexIds0.back();
		const unsigned int v1 = vertexIds0.front();
		const unsigned int v2 = vertexIds1.front();
		const unsigned int v3 = vertexIds1.back();
		std::vector<unsigned int> vertexIds3 = { v0, v1, v2, v3 };
		faceBuilder.build(vertexBuilder.getVertices(), vertexIds3);
	}

}

void PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	VertexVector vertices;
	FaceVector faces;
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0f / vDivideNumber * k;
			const float vRadius = vAngle * Tolerances::getPI() / 180.0f;

			const float uAngle = 360.0f / uDivideNumber * i;
			const float rad = uAngle *Tolerances::getPI() / 180.0f;
			vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius, i ) );
			vertexIds.push_back(i);
		}
	}

}

void PolygonBuilder::buildCone(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);
	VertexVector vertices;
	FaceVector faces;
	std::vector<unsigned int> vertexIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f), i));
		vertexIds.push_back(i);
	}

	faceBuilder.build( vertices, vertexIds );

	vertices.push_back( new Vertex( Vector3d(0.0, 0.0, 1.0f), divideNumber ));

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		faceBuilder.build( vertices, { v0, v1, v2 });
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		faceBuilder.build(vertices, { v0, v1, v2 });
	}

}