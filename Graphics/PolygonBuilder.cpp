#include "PolygonBuilder.h"

#include "Face.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;

PolygonSPtr PolygonBuilder::buildQuad()
{
	FaceSPtrVector faces;

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder->build()) );
	faceBuilder->setPolygon(polygon);

	FaceSPtr f( faceBuilder->buildQuad() );

	faces.push_back( f );
	//this->vertices = faceBuilder.getVertices();

	polygon->setVertices(faceBuilder->getVertices());
	polygon->setFaces({ f });
	return polygon;
}

PolygonSPtr PolygonBuilder::buildBox()
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

	const VertexSPtrVector& vs = faceBuilder->getVertexBuilder()->buildVerticesFromPositionsAndNormals(positions, normals);

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder->build()) );
	faceBuilder->setPolygon(polygon);

	const HalfEdgeBuilderSPtr& eBuilder = faceBuilder->getHalfEdgeBuilder();
	const std::vector<HalfEdgeSPtrList> edges = {
		eBuilder->buildClosedFromVertices({ vs[0], vs[1], vs[2], vs[3] }),
		eBuilder->buildClosedFromVertices({ vs[0], vs[1], vs[2], vs[3] }),
		eBuilder->buildClosedFromVertices({ vs[4], vs[5], vs[6], vs[7] }),
		eBuilder->buildClosedFromVertices({ vs[2], vs[3], vs[7], vs[6] }),
		eBuilder->buildClosedFromVertices({ vs[3], vs[0], vs[4], vs[7] }),
		eBuilder->buildClosedFromVertices({ vs[5], vs[1], vs[2], vs[6] }),
	};

	FaceSPtrVector faces;
	for (const HalfEdgeSPtrList& e : edges) {
		faces.push_back( faceBuilder->build(e) );
	}
	polygon->setVertices(vs);
	polygon->setFaces(faces);
	return polygon;
}

PolygonSPtr PolygonBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	std::shared_ptr< Face > f = faceBuilder->buildCircleByNumber(radius, divideNumber);

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder->build()) );
	f->setPolygon(polygon);
	polygon->setVertices(f->getVertices());
	polygon->setFaces({ f });
	return polygon;
}

PolygonSPtr PolygonBuilder::buildCircleByAngle(const float radius, const float divideAngle)
{
	const int howMany = static_cast<int>(360.0f / divideAngle);
	return buildCircleByNumber(radius, howMany);
}

PolygonSPtr PolygonBuilder::buildCylinder(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	PolygonSPtr polygon(new Polygon(nextId++, materialBuilder->build()));
	FaceSPtrVector faces;
	faceBuilder->setPolygon(polygon);

	VertexSPtrVector vv0;
	const HalfEdgeBuilderSPtr& eBuilder = getHalfEdgeBuilder();
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv0.push_back( getVertexBuilder()->build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)) );
	}
	const HalfEdgeSPtrList& edges0 = eBuilder->buildClosedFromVertices( vv0);
	faces.push_back( faceBuilder->build( edges0 ) );
	//faces.push_back( new Face( vertices, vertexIds0, 0 ) );

	VertexSPtrVector vv1;
	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		vv1.push_back(getVertexBuilder()->build(Vector3d(std::sin(rad), std::cos(rad), 0.0f)));
	}
	const HalfEdgeSPtrList& edges1 = eBuilder->buildClosedFromVertices(vv1);
	faces.push_back( faceBuilder->build( edges1 ) );

	for (unsigned int i = 0; i < divideNumber-1; ++i) {
		const VertexSPtrVector vv{ vv0[i], vv0[i+1], vv1[i+1], vv1[i] };
		const HalfEdgeSPtrList& edges2 = eBuilder->buildClosedFromVertices(vv);
		faces.push_back( faceBuilder->build( edges2 ) );
	}

	{
		const VertexSPtrVector vv{ vv0.back(), vv0.front(), vv1.front(), vv1.back() };
		const HalfEdgeSPtrList& edges3 = eBuilder->buildClosedFromVertices(vv);
		faces.push_back( faceBuilder->build( edges3 ) );
	}

	polygon->addVertices(vv0);
	polygon->addVertices(vv1);
	polygon->setFaces(faces);
	return polygon;

}

PolygonSPtr PolygonBuilder::buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	VertexSPtrVector vertices;
	//FaceVector faces;
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0f / vDivideNumber * k;
			const float vRadius = vAngle * Tolerances::getPI() / 180.0f;

			const float uAngle = 360.0f / uDivideNumber * i;
			const float rad = uAngle *Tolerances::getPI() / 180.0f;
			VertexSPtr v( new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius, i) );
			vertices.push_back(v);
			vertexIds.push_back(i);
		}
	}
	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder->build()) );
	polygon->setVertices(vertices);
	//polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}

PolygonSPtr PolygonBuilder::buildCone(const unsigned int divideNumber)
{
	assert(divideNumber >= 3);
	VertexSPtrVector vertices;
	FaceSPtrVector faces;

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder->build()) );

	faceBuilder->setPolygon(polygon);

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		const VertexSPtr v(new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f), i));
		vertices.push_back(v);
	}

	faces.push_back( faceBuilder->build( getHalfEdgeBuilder()->buildClosedFromVertices( vertices ) ) );

	const VertexSPtr v(new Vertex(Vector3d(0.0, 0.0, 1.0f), divideNumber));
	vertices.push_back(v);

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		const unsigned int v2 = divideNumber;
		faces.push_back( faceBuilder->build( getHalfEdgeBuilder()->buildClosedFromVertices( { vertices[v0], vertices[v1], vertices[v2] } ) ) );
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		const unsigned int v2 = divideNumber;
		faces.push_back( faceBuilder->build( getHalfEdgeBuilder()->buildClosedFromVertices( { vertices[v0], vertices[v1], vertices[v2] } ) ) );
	}
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;

}