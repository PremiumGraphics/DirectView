#ifndef __CRYSTAL_GRAPHICS_FACE_BUILDER_H__
#define __CRYSTAL_GRAPHICS_FACE_BUILDER_H__

#include "Vertex.h"
#include "Face.h"

namespace Crystal {
	namespace Graphics {

class Face;

class FaceBuilder {
public:
	FaceBuilder(VertexBuilder& vBuilder) :
		vBuilder( vBuilder ),
		nextId(0)
	{}

	void buildCircleByNumber(const float radius, const unsigned int divideNumber);

	Face* buildQuad();

	void build(const VertexVector& vertices, const std::vector<unsigned int >& vertexIds) {
		Face* f = new Face( HalfEdgeBuilder::createByIndex(vertices, vertexIds), nextId++ );
		faces.push_back(f);
	}

	VertexVector getVertices() const { return vBuilder.getVertices();  }

	FaceVector getFaces() const { return faces; }

private:
	VertexBuilder& vBuilder;
	FaceVector faces;
	unsigned int nextId;
};

	}
}

#endif