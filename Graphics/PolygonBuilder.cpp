#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Polygon* PolygonBuilder::buildQuad()
{
	const VertexVector vertices = {
		new Vertex( Vector3d(0.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 0 ),
		new Vertex( Vector3d(0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 1 ),
		new Vertex( Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 2 ),
		new Vertex( Vector3d(1.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 3 )
	};

	const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
	const FaceVector& faces = { new Face(edges, 0) };

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
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

	const VertexVector& vertices = Vertex::createVerticesFromPositionsAndNormals(positions, normals);

	const FaceVector& faces = {
		new Face(vertices, { 0, 1, 2, 3 }, 0),
		new Face(vertices, { 4, 5, 6, 7 }, 1),
		new Face(vertices, { 0, 1, 5, 4 }, 2),
		new Face(vertices, { 2, 3, 7, 6 }, 3),
		new Face(vertices, { 3, 0, 4, 7 }, 4),
		new Face(vertices, { 5, 1, 2, 6 }, 5)
	};

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;
}

Polygon* PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;

	VertexVector vertices;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(
			new Vertex( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d( 0.0, 0.0, 1.0), i ) );
	}
	const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
	const FaceVector faces = { new Face(edges, 0) };

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;
}

Polygon* PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	return buildCircleByNumber(radius, 360.0f / divideAngle);
}

Polygon* PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	VertexVector vertices;
	FaceVector faces;
	std::vector<unsigned int> vertexIds0;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f), i ));
		vertexIds0.push_back(i);
	}
	faces.push_back( new Face( vertices, vertexIds0, 0 ) );

	std::vector<unsigned int> vertexIds1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 1.0f), divideNumber + i ));
		vertexIds1.push_back( divideNumber + i);
	}
	faces.push_back( new Face( vertices, vertexIds1, 1 ) );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {

		const unsigned int v0 = vertexIds0[i];
		const unsigned int v1 = vertexIds0[i+1];
		const unsigned int v2 = vertexIds1[i+1];
		const unsigned int v3 = vertexIds1[i];
		std::vector<unsigned int> vertexIds2 = { v0, v1, v2, v3 };
		faces.push_back( new Face( HalfEdge::createByIndex( vertices, vertexIds2), 2 ) );
	}

	{
		const unsigned int v0 = vertexIds0.back();
		const unsigned int v1 = vertexIds0.front();
		const unsigned int v2 = vertexIds1.front();
		const unsigned int v3 = vertexIds1.back();
		std::vector<unsigned int> vertexIds3 = { v0, v1, v2, v3 };
		faces.push_back( new Face( HalfEdge::createByIndex( vertices, vertexIds3), 3) );
	}

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
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

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;
	//f.setVertexIds(vertexIds);
	//f.setNormalIds(normalIds);
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

	Face* f = new Face( vertices, vertexIds, 0);
	faces.push_back(f);

	vertices.push_back( new Vertex( Vector3d(0.0, 0.0, 1.0f), divideNumber ));

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		Face* f = new Face( vertices, { v0, v1, v2 }, i+1);
		faces.push_back(f);
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		Face* f = new Face(vertices, { v0, v1, v2 }, divideNumber);
		faces.push_back(f);
	}

	Polygon* polygon = new Polygon();
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;
}