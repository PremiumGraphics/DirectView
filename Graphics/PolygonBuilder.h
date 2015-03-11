#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "Polygon.h"

#include "Face.h"
#include "Vertex.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:

	PolygonBuilder(FaceBuilder& faceBuilder) :
		nextId(0),
		faceBuilder( faceBuilder )
	{}

	PolygonSPtr buildQuad();

	PolygonSPtr buildBox();

	PolygonSPtr buildCircleByNumber(const float radius, const unsigned int divideNumber);

	PolygonSPtr buildCircleByAngle(const float radius, const float divideAngle);

	PolygonSPtr buildTriangle() { return buildCircleByNumber(1.0f, 3); }

	PolygonSPtr buildCylinder(const unsigned int divideNuber);

	PolygonSPtr buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	PolygonSPtr buildCone(const unsigned int divideNumber);

	FaceBuilder& getFaceBuilder() const { return faceBuilder; }

	VertexBuilder& getVertexBuilder() const { return faceBuilder.getVertexBuilder(); }

	HalfEdgeBuilder& getHalfEdgeBuilder() const { return faceBuilder.getHalfEdgeBuilder(); }

	void clear(){
		nextId = 0;
	}

private:
	unsigned int nextId;

	FaceBuilder& faceBuilder;
};
	}
}

#endif