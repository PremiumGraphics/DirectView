#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Vector3dVector Face::getTexCoords() const
{
	Vector3dVector texCoords;
	for (const HalfEdgeSPtr& e : edges) {
		texCoords.push_back(e->getStart()->getNormal());
		if (e == edges.back() && isOpen()) {
			texCoords.push_back(e->getEnd()->getNormal());
		}
	}
	return texCoords;

}


std::shared_ptr< Face > FaceBuilder::buildCircleByNumber(const float radius, const unsigned int divideNumber)
{
	assert(divideNumber >= 3);

	for (unsigned int i = 0; i < divideNumber; ++i) {
		const float angle = 360.0f / divideNumber * i;
		const float rad = angle *Tolerances::getPI() / 180.0f;
		const VertexSPtr& v = getVertexBuilder()->build(radius * Vector3d(std::sin(rad), std::cos(rad), 0.0f), Vector3d(0.0, 0.0, 1.0));
		vertices.push_back(v);
	}
	const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices( vertices);
	FaceSPtr f(new Face(edges, nextId++));
	faces.push_back(f);
	return f;
}

std::shared_ptr< Face > FaceBuilder::buildQuad()
{
	vertices = {
		getVertexBuilder()->build(Vector3d(0.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder()->build(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder()->build(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 1.0)),
		getVertexBuilder()->build(Vector3d(1.0, 1.0, 0.0), Vector3d(0.0, 0.0, 1.0))
	};

	const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices( vertices);
	FaceSPtr f(new Face(edges, nextId++));
	faces.push_back(f);
	f->setPolygon(polygon);
	return f;
}

FaceSPtr FaceBuilder::createOffset(const FaceSPtr& original)
{
	const VertexSPtrVector& vs = original->getVertices();

	Vector3dVector positions;
	for (const VertexSPtr& v : vs) {
		positions.push_back( v->getPosition() + Vector3d( 0.0, 0.0, 1.0 ) );
	}
	VertexSPtrVector ps = getVertexBuilder()->buildVerticesFromPositions(positions);
	vertices.insert(vertices.end(), ps.begin(), ps.end());
	const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices(ps);

	FaceSPtr f(new Face(edges, nextId++));
	faces.push_back(f);
	f->setPolygon(polygon);
	return f;
}

FaceSPtrVector FaceBuilder::buildSides(const FaceSPtr& lhs, const FaceSPtr& rhs)
{
	assert(lhs->getEdges().size() == rhs->getEdges().size());
	
	const HalfEdgeSPtrList& ee1 = lhs->getEdges();
	const HalfEdgeSPtrList& ee2 = rhs->getEdges();
	std::vector< HalfEdgeSPtr > e1( ee1.begin(), ee1.end() );
	std::vector< HalfEdgeSPtr > e2( ee2.begin(), ee2.end() );

	FaceSPtrVector fs;
	for (size_t i = 0; i < e1.size(); ++i) {
		VertexSPtrVector vs;
		vs.push_back( e1[i]->getStart());
		vs.push_back( e1[i]->getEnd() );
		vs.push_back( e2[i]->getEnd());
		vs.push_back( e2[i]->getStart());
		const HalfEdgeSPtrList& edges = eBuilder->buildClosedFromVertices(vs);

		FaceSPtr f(new Face(edges, nextId++));
		fs.push_back(f);
		f->setPolygon(polygon);
	}
	faces.insert(faces.end(), fs.begin(), fs.end());
	return fs;	
}
