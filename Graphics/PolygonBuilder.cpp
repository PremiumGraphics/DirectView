#include "PolygonBuilder.h"

#include "FaceBuilder.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;

Polygon* PolygonBuilder::buildQuad()
{
	FaceVector faces;

	faceBuilder.buildQuad();

	faces.push_back( faceBuilder.getFaces().back() );
	//this->vertices = faceBuilder.getVertices();

	Polygon* polygon = new Polygon(nextId++);
	polygon->setVertices(faceBuilder.getVertices());
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;
}

Polygon* PolygonBuilder::buildBox()
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

	VertexVector vertices = vertexBuilder.buildVerticesFromPositionsAndNormals(positions, normals);

	faceBuilder.build(vertices, { 0, 1, 2, 3 });
	faceBuilder.build(vertices, { 4, 5, 6, 7 });
	faceBuilder.build(vertices, { 0, 1, 5, 4 });
	faceBuilder.build(vertices, { 2, 3, 7, 6 });
	faceBuilder.build(vertices, { 3, 0, 4, 7 });
	faceBuilder.build(vertices, { 5, 1, 2, 6 });

	FaceVector faces = faceBuilder.getFaces();

	Polygon* polygon = new Polygon(nextId++);
	polygon->setVertices(vertices);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;
}

Polygon* PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	Face* f = faceBuilder.buildCircleByNumber(radius, divideNumber);

	Polygon* polygon = new Polygon(nextId++);
	polygon->setVertices(f->getVertices());
	polygon->setFaces({ f });
	return polygon;
}

Polygon* PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	const int howMany = static_cast<int>(360.0f / divideAngle);
	return buildCircleByNumber(radius, howMany);
}

Polygon* PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	VertexVector vv0;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv0.push_back( vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)) );
	}
	faceBuilder.build( vv0 );
	//faces.push_back( new Face( vertices, vertexIds0, 0 ) );

	VertexVector vv1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv1.push_back( vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)) );
	}
	faceBuilder.build( vv1 );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {
		const VertexVector vv{ vv0[i], vv0[i+1], vv1[i+1], vv1[i] };
		faceBuilder.build( vv );
	}

	{
		const VertexVector vv{ vv0.back(), vv0.front(), vv1.front(), vv1.back() };
		faceBuilder.build( vv );
	}

	Polygon* polygon = new Polygon(nextId++);
	polygon->addVertices(vv0);
	polygon->addVertices(vv1);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}

Polygon* PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
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
	Polygon* polygon = new Polygon(nextId++);
	polygon->setVertices(vertices);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}

Polygon* PolygonBuilder::buildCone(const unsigned int divideNumber)
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
	Polygon* polygon = new Polygon(nextId++);
	polygon->setVertices(vertices);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}