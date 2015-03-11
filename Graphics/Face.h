#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

#include <vector>
#include <memory>

namespace Crystal {
	namespace Graphics {

class Polygon;
typedef std::shared_ptr< Polygon > PolygonSPtr;

class Face {
public:
	Face(const unsigned int id)
		: id(id),
		polygon( nullptr )
	{};


	Face(const HalfEdgeList& edges, const unsigned int id) :
		edges( edges ),
		id( id ),
		polygon(nullptr)
	{}

	~Face(){}

	unsigned int getId() const { return id; }

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setEdges(const HalfEdgeList& edges) { this->edges = edges; }

	HalfEdgeList getEdges() const { return edges; }

	VertexVector getVertices() const {
		VertexVector vertices;
		for (const HalfEdgeSPtr& e : edges) {
			vertices.push_back(e->getStart());
		}
		return vertices;
	}

	Math::Vector3dVector getNormals() const;

	Math::Vector3dVector getTexCoords() const;

	PolygonSPtr getPolygon() const { return polygon; }

	void setPolygon(const PolygonSPtr& polygon) { this->polygon = polygon; }

private:
	//VertexVector vertices;
	HalfEdgeList edges;
	const unsigned int id;
	PolygonSPtr polygon;
};

typedef std::shared_ptr<Face> FaceSPtr;
typedef std::vector< std::shared_ptr<Face> > FaceVector;

class Face;

class FaceBuilder {
public:
	FaceBuilder(HalfEdgeBuilder& eBuilder) :
		eBuilder(eBuilder),
		nextId(0),
		polygon( nullptr )
	{}

	void setPolygon(const PolygonSPtr& polygon){ this->polygon = polygon; }

	std::shared_ptr<Face> buildCircleByNumber(const float radius, const unsigned int divideNumber);

	std::shared_ptr<Face> buildQuad();

	std::shared_ptr<Face> build(const HalfEdgeList& edges ) {
		std::shared_ptr<Face> f( new Face(edges, nextId++) );
		f->setPolygon(polygon);
		return f;
	}

	VertexVector getVertices() const { return vertices; }

	VertexBuilder& getVertexBuilder() const { return eBuilder.getVertexBuilder(); }

	HalfEdgeBuilder& getHalfEdgeBuilder() const { return eBuilder; }

private:
	VertexVector vertices;
	HalfEdgeBuilder& eBuilder;
	PolygonSPtr polygon;
	unsigned int nextId;
};

	}
}

#endif