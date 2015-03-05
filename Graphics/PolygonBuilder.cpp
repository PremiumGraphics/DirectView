#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

void PolygonBuilder::buildQuad()
{
	vertices = {
		new Vertex( Vector3d(0.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 0 ),
		new Vertex( Vector3d(0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 1 ),
		new Vertex( Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 2 ),
		new Vertex( Vector3d(1.0, 1.0, 0.0), Vector3d( 0.0, 0.0, 1.0 ), 3 )
	};

	const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
	faces = { new Face(edges) };
}

void PolygonBuilder::buildBox()
{
	normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, -1.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0)
	};

	Vector3dVector positions = {
		Vector3d(0.0, 1.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(1.0, 0.0, 1.0),
		Vector3d(1.0, 1.0, 1.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};

	vertices = Vertex::createVerticesFromPositionsAndNormals(positions, normals);

	faces = {
		new Face(vertices, { 0, 1, 2, 3 }),
		new Face(vertices, { 4, 5, 6, 7 }),
		new Face(vertices, { 0, 1, 5, 4 }),
		new Face(HalfEdge::createByIndex(vertices, { 2, 3, 7, 6 })),
		new Face(HalfEdge::createByIndex(vertices, { 3, 0, 4, 7 })),
		new Face(HalfEdge::createByIndex(vertices, { 5, 1, 2, 6 }))
	};
}

void PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	std::vector<unsigned int> vertexIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(
			new Vertex( radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d( 0.0, 0.0, 1.0), i ) );
		vertexIds.push_back(i);
	}
	faces = { new Face(HalfEdge::createByIndex(vertices, vertexIds)) };
}

void PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	buildCircleByNumber(radius, 360.0f / divideAngle);
}

void PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	normals = {
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, -1.0),
	};

	std::vector<unsigned int> vertexIds0;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f), i ));
		vertexIds0.push_back(i);
	}
	faces.push_back( new Face( vertices, vertexIds0 ) );

	std::vector<unsigned int> vertexIds1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 1.0f), divideNumber + i ));
		vertexIds1.push_back( divideNumber + i);
	}
	faces.push_back( new Face( vertices, vertexIds1 ) );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {

		const unsigned int v0 = vertexIds0[i];
		const unsigned int v1 = vertexIds0[i+1];
		const unsigned int v2 = vertexIds1[i+1];
		const unsigned int v3 = vertexIds1[i];
		std::vector<unsigned int> vertexIds2 = { v0, v1, v2, v3 };
		normals.push_back(Vector3d(0.0, 0.0, 0.0));
		faces.push_back( new Face( HalfEdge::createByIndex( vertices, vertexIds2) ) );
	}

	{
		const unsigned int v0 = vertexIds0.back();
		const unsigned int v1 = vertexIds0.front();
		const unsigned int v2 = vertexIds1.front();
		const unsigned int v3 = vertexIds1.back();
		std::vector<unsigned int> vertexIds3 = { v0, v1, v2, v3 };
		normals.push_back(Vector3d(0.0, 0.0, 0.0));
		faces.push_back( new Face( HalfEdge::createByIndex( vertices, vertexIds3)) );
	}

}

void PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0f / vDivideNumber * k;
			const float vRadius = vAngle * Tolerances::getPI() / 180.0f;

			const float uAngle = 360.0f / uDivideNumber * i;
			const float rad = uAngle *Tolerances::getPI() / 180.0f;
			vertices.push_back( new Vertex( Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius, i ) );
			normals.push_back(Vector3d(std::sin(rad), std::cos(rad), 0.0f));
			vertexIds.push_back(i);
		}
	}
	//f.setVertexIds(vertexIds);
	//f.setNormalIds(normalIds);
}

void PolygonBuilder::buildCone(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);
	std::vector<unsigned int> vertexIds;
	std::vector<unsigned int> normalIds;

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f), i));
		vertexIds.push_back(i);
		normalIds.push_back(0);
	}

	normals.push_back(Vector3d(0.0, 0.0, 1.0));
	Face* f = new Face( vertices, vertexIds);
	faces.push_back(f);

	vertices.push_back( new Vertex( Vector3d(0.0, 0.0, 1.0f), divideNumber ));

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		Face* f = new Face( vertices, { v0, v1, v2 });
		faces.push_back(f);
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		Face* f = new Face(vertices, { v0, v1, v2 });
		faces.push_back(f);
	}
}