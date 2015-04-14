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


	Face(const HalfEdgeSPtrList& edges, const unsigned int id) :
		edges( edges ),
		id( id ),
		polygon(nullptr)
	{}

	~Face(){}

	unsigned int getId() const { return id; }

	bool isClosed() const { return edges.back()->getEndPosition() == edges.front()->getStartPosition(); }

	bool isOpen() const { return !isClosed(); }

	void setEdges(const HalfEdgeSPtrList& edges) { this->edges = edges; }

	HalfEdgeSPtrList getEdges() const { return edges; }

	VertexSPtrVector getVertices() const {
		VertexSPtrVector vertices;
		for (const HalfEdgeSPtr& e : edges) {
			vertices.push_back(e->getStart());
		}
		return vertices;
	}

	Math::Vector3dVector getTexCoords() const;

	Math::Vector3d getCenter() const;

	PolygonSPtr getPolygon() const { return polygon; }

	void setPolygon(const PolygonSPtr& polygon) { this->polygon = polygon; }

private:
	//VertexSPtrVector vertices;
	HalfEdgeSPtrList edges;
	const unsigned int id;
	PolygonSPtr polygon;
};

typedef std::shared_ptr<Face> FaceSPtr;
typedef std::vector< std::shared_ptr<Face> > FaceSPtrVector;

class FaceBuilder {
public:
	FaceBuilder() :
		nextId(0)
	{}

	void setPolygon(const PolygonSPtr& polygon){ this->polygon = polygon; }

	FaceSPtr buildCircleByNumber(const float radius, const unsigned int divideNumber);

	FaceSPtr buildQuad();

	FaceSPtr build(const HalfEdgeSPtrList& edges ) {
		FaceSPtr f( new Face(edges, nextId++) );
		f->setPolygon(polygon);
		return f;
	}

	VertexSPtrVector getVertices() const { return vertices; }

	VertexBuilderSPtr getVertexBuilder() const { return eBuilder.getVertexBuilder(); }

	HalfEdgeBuilder& getHalfEdgeBuilder() { return eBuilder; }

	FaceSPtrVector getFaces() const { return faces; }

	FaceSPtr createOffset(const FaceSPtr& original);

	FaceSPtrVector buildSides(const FaceSPtr& lhs, const FaceSPtr& rhs);

private:
	VertexSPtrVector vertices;
	FaceSPtrVector faces;
	HalfEdgeBuilder eBuilder;
	PolygonSPtr polygon;
	unsigned int nextId;
};

typedef std::shared_ptr<FaceBuilder> FaceBuilderSPtr;

	}
}

#endif