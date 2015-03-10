#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include <vector>

namespace Crystal {
	namespace Graphics {

class Face {
public:
	Face(const unsigned int id) : id(id)
	{};


	Face(const HalfEdgeList& edges, const unsigned int id) :
		edges( edges ),
		id( id )
	{}

	~Face(){
		for (HalfEdge* e : edges) {
			delete e;
		}
	}

	unsigned int getId() const { return id; }

	std::vector<unsigned int> getVertexIds() {
		std::vector<unsigned int> ids;
		for (HalfEdge* edge : edges) {
			ids.push_back( edge->getStart()->getId() );
		}
		return ids;
	}

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setEdges(const HalfEdgeList& edges) { this->edges = edges; }

	HalfEdgeList getEdges() const { return edges; }

	VertexVector getVertices() const {
		VertexVector vertices;
		for (HalfEdge* e : edges) {
			vertices.push_back(e->getStart());
		}
		return vertices;
	}

	Math::Vector3dVector getPositions() const;

	Math::Vector3dVector getNormals() const;

	Math::Vector3dVector getTexCoords() const;

private:
	//VertexVector vertices;
	HalfEdgeList edges;
	const unsigned int id;

};

typedef std::vector<Face*> FaceVector;

class Face;

class FaceBuilder {
public:
	FaceBuilder(VertexBuilder& vBuilder) :
		vBuilder(vBuilder),
		nextId(0)
	{}

	Face* buildCircleByNumber(const float radius, const unsigned int divideNumber);

	Face* buildQuad();

	void build(const VertexVector& vertices) {
		const HalfEdgeList& edges = eBuilder.createClosedFromVertices( vertices, nullptr);
		Face* f = new Face(edges, nextId++);
		faces.push_back(f);
	}

	/*
	void build(const VertexVector& vertices, const std::vector<unsigned int >& vertexIds) {
	Face* f = new Face( eBuilder.createByIndex( vertices, vertexIds), nextId++ );
	faces.push_back(f);
	}
	*/

	VertexVector getVertices() const { return vertices; }

	FaceVector getFaces() const { return faces; }

private:
	VertexBuilder& vBuilder;
	VertexVector vertices;
	FaceVector faces;
	HalfEdgeBuilder eBuilder;
	unsigned int nextId;
};

	}
}

#endif