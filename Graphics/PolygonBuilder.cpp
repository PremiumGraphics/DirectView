#include "PolygonBuilder.h"

#include "Face.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;

Polygon* PolygonBuilder::buildQuad()
{
	FaceVector faces;

	Polygon* polygon = new Polygon(nextId++);
	faceBuilder.setPolygon(polygon);

	faceBuilder.buildQuad();

	faces.push_back( faceBuilder.getFaces().back() );
	//this->vertices = faceBuilder.getVertices();

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

	const VertexVector& vs = faceBuilder.getVertexBuilder().buildVerticesFromPositionsAndNormals(positions, normals);

	Polygon* polygon = new Polygon(nextId++);
	faceBuilder.setPolygon(polygon);

	HalfEdgeBuilder& eBuilder = faceBuilder.getHalfEdgeBuilder();
	const std::vector<HalfEdgeList> edges = {
		eBuilder.buildClosedFromVertices(nullptr, { vs[0], vs[1], vs[2], vs[3] }),
		eBuilder.buildClosedFromVertices(nullptr, { vs[0], vs[1], vs[2], vs[3] }),
		eBuilder.buildClosedFromVertices(nullptr, { vs[4], vs[5], vs[6], vs[7] }),
		eBuilder.buildClosedFromVertices(nullptr, { vs[2], vs[3], vs[7], vs[6] }),
		eBuilder.buildClosedFromVertices(nullptr, { vs[3], vs[0], vs[4], vs[7] }),
		eBuilder.buildClosedFromVertices(nullptr, { vs[5], vs[1], vs[2], vs[6] }),
	};
	for (const HalfEdgeList& e : edges) {
		faceBuilder.build(e);
	}

	FaceVector faces = faceBuilder.getFaces();

	polygon->setVertices(vs);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;
}

Polygon* PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	Face* f = faceBuilder.buildCircleByNumber(radius, divideNumber);

	Polygon* polygon = new Polygon(nextId++);
	f->setPolygon(polygon);
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

	Polygon* polygon = new Polygon(nextId++);
	faceBuilder.setPolygon(polygon);

	VertexVector vv0;
	HalfEdgeBuilder& eBuilder = getHalfEdgeBuilder();
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv0.push_back( vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)) );
	}
	const HalfEdgeList& edges0 = eBuilder.buildClosedFromVertices(nullptr, vv0);
	faceBuilder.build( edges0 );
	//faces.push_back( new Face( vertices, vertexIds0, 0 ) );

	VertexVector vv1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv1.push_back( vertexBuilder.build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)) );
	}
	const HalfEdgeList& edges1 = eBuilder.buildClosedFromVertices(nullptr, vv1);
	faceBuilder.build( edges1 );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {
		const VertexVector vv{ vv0[i], vv0[i+1], vv1[i+1], vv1[i] };
		const HalfEdgeList& edges2 = eBuilder.buildClosedFromVertices(nullptr, vv);
		faceBuilder.build( edges2 );
	}

	{
		const VertexVector vv{ vv0.back(), vv0.front(), vv1.front(), vv1.back() };
		const HalfEdgeList& edges3 = eBuilder.buildClosedFromVertices(nullptr, vv);
		faceBuilder.build( edges3 );
	}

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

	Polygon* polygon = new Polygon(nextId++);

	faceBuilder.setPolygon(polygon);

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vertices.push_back(new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f), i));
	}

	faceBuilder.build( getHalfEdgeBuilder().buildClosedFromVertices( nullptr, vertices ) );

	vertices.push_back( new Vertex( Vector3d(0.0, 0.0, 1.0f), divideNumber ));

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		faceBuilder.build( getHalfEdgeBuilder().buildClosedFromVertices( nullptr, { vertices[v0], vertices[v1], vertices[v2] } ) );
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		faceBuilder.build( getHalfEdgeBuilder().buildClosedFromVertices( nullptr, { vertices[v0], vertices[v1], vertices[v2] } ) );
	}
	polygon->setVertices(vertices);
	polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}