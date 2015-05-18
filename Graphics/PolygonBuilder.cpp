#include "PolygonBuilder.h"

#include "Face.h"

#include "../Math/Cone.h"
#include "../Math/Cylinder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

PolygonSPtr PolygonBuilder::build(const Quad<float>& quad)
{
	FaceSPtrVector faces;

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder.build()) );
	polygons.push_back(polygon);
	faceBuilder->setPolygon(polygon);

	FaceSPtr f( faceBuilder->buildQuad() );

	faces.push_back( f );
	//this->vertices = faceBuilder.getVertices();

	polygon->setVertices(faceBuilder->getVertices());
	polygon->setFaces({ f });
	return polygon;
}

PolygonSPtr PolygonBuilder::build(const Box& box)
{
	PolygonSPtr polygon(new Polygon(nextId++, materialBuilder.build()));
	faceBuilder->setPolygon( polygon );
	FaceSPtr f1(faceBuilder->buildQuad());
	FaceSPtr f2(faceBuilder->createOffset(f1));
	FaceSPtrVector fs = faceBuilder->buildSides(f1, f2);

	FaceSPtrVector faces{ f1, f2 };
	faces.insert(faces.end(), fs.begin(), fs.end());

	VertexSPtrVector v1 = f1->getVertices();
	VertexSPtrVector v2 = f2->getVertices();
	v1.insert(v1.end(), v2.begin(), v2.end());

	polygon->setVertices(v1);
	polygon->setFaces(faces);
	polygons.push_back(polygon);
	return polygon;
}

PolygonSPtr PolygonBuilder::build(const Circle& circle, const unsigned int divideNumber)
{
	std::shared_ptr< Face > f = faceBuilder->buildCircleByNumber(circle.getRadius(), divideNumber);

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder.build()) );
	polygons.push_back(polygon);
	f->setPolygon(polygon);
	polygon->setVertices(f->getVertices());
	polygon->setFaces({ f });
	return polygon;
}

PolygonSPtr PolygonBuilder::build(const Triangle& triangle)
{
	Circle c;
	return build(c, 3);
}

PolygonSPtr PolygonBuilder::build(const unsigned int divideNumber, const Cylinder& c )
{
	assert(divideNumber >= 3);

	PolygonSPtr polygon(new Polygon(nextId++, materialBuilder.build()));
	faceBuilder->setPolygon(polygon);
	FaceSPtr f1(faceBuilder->buildCircleByNumber(1.0f,divideNumber));
	FaceSPtr f2(faceBuilder->createOffset(f1));
	FaceSPtrVector fs = faceBuilder->buildSides(f1, f2);

	FaceSPtrVector faces{ f1, f2 };
	faces.insert(faces.end(), fs.begin(), fs.end());

	VertexSPtrVector v1 = f1->getVertices();
	VertexSPtrVector v2 = f2->getVertices();
	v1.insert(v1.end(), v2.begin(), v2.end());

	polygon->setVertices(v1);
	polygon->setFaces(faces);
	polygons.push_back(polygon);
	return polygon;

}

PolygonSPtr PolygonBuilder::build(const Sphere& sphere,const unsigned int uDivideNumber, const unsigned int vDivideNumber)
{
	VertexSPtrVector vertices;
	//FaceVector faces;
	for (unsigned int i = 0; i < uDivideNumber; ++i) {
		std::vector<unsigned int> vertexIds;
		for (unsigned int k = 0; k < vDivideNumber; ++k) {
			const float vAngle = 180.0f / vDivideNumber * k;
			const float vRadius = vAngle * Tolerancef::getPI() / 180.0f;

			const float uAngle = 360.0f / uDivideNumber * i;
			const float rad = uAngle *Tolerancef::getPI() / 180.0f;
			VertexSPtr v( new Vertex(Vector3d(std::sin(rad), std::cos(rad), 0.0f) * vRadius, i) );
			vertices.push_back(v);
			vertexIds.push_back(i);
		}
	}
	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder.build()) );
	polygons.push_back(polygon);

	polygon->setVertices(vertices);
	//polygon->setFaces(faceBuilder.getFaces());
	return polygon;

}

PolygonSPtr PolygonBuilder::build(const unsigned int divideNumber, const Cone& cone)
{
	/*
	const Circle c;
	PolygonSPtr p = build(c, divideNumber);

	const Math::Vector3d& center = p->getCenter();
	VertexSPtr v( new Vertex(center) );
	p->addVertices({ v });
	*/

	assert(divideNumber >= 3);
	VertexSPtrVector vertices;
	FaceSPtrVector faces;

	PolygonSPtr polygon( new Polygon(nextId++, materialBuilder.build()) );
	polygons.push_back(polygon);

	faceBuilder->setPolygon(polygon);

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerancef::getPI() / 180.0f;
		const VertexSPtr v(new Vertex(Vector3d(std::sin(rad), 0.0f, std::cos(rad) ), i));
		vertices.push_back(v);
	}

	//faces.push_back( faceBuilder->build( getHalfEdgeBuilder().buildClosedFromVertices( vertices ) ) );

	const VertexSPtr topVertex(new Vertex(Vector3d(0.0, cone.getHeight(), 0.0f), divideNumber));
	vertices.push_back(topVertex);

	for (unsigned int i = 0; i < divideNumber - 1; ++i) {
		const unsigned int v0 = i;
		const unsigned int v1 = i + 1;
		faces.push_back( faceBuilder->build( getHalfEdgeBuilder().buildClosedFromVertices( { vertices[v0], vertices[v1], topVertex, vertices[v0] } ) ) );
	}

	{
		const unsigned int v0 = divideNumber - 1;
		const unsigned int v1 = 0;
		faces.push_back( faceBuilder->build( getHalfEdgeBuilder().buildClosedFromVertices( { vertices[v0], vertices[v1], topVertex, vertices[v0] } ) ) );
	}
	polygon->setVertices(vertices);
	polygon->setFaces(faces);
	return polygon;
}