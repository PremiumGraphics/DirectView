#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "Polygon.h"

#include "FaceBuilder.h"
#include "Vertex.h"

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:

	PolygonBuilder(VertexBuilder& vertexBuilder) :
		nextId(0),
		faceBuilder( vertexBuilder ),
		vertexBuilder( vertexBuilder )
	{}

	void buildQuad();

	void buildBox();

	void buildCircleByNumber(const float radius, const unsigned int divideNumber);

	void buildCircleByAngle(const float radius, const float divideAngle);

	void buildTriangle() { return buildCircleByNumber(1.0f, 3); }

	void buildCylinder(const unsigned int divideNuber);

	void buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	void buildCone(const unsigned int divideNumber);

	void clear(){
		nextId = 0;
	}


	Polygon* createPolygon() {
		Polygon* polygon = new Polygon(nextId++);
		polygon->setVertices(faceBuilder.getVertices());
		polygon->setFaces(faceBuilder.getFaces());
		return polygon;
	}

private:
	unsigned int nextId;

	FaceBuilder faceBuilder;
	VertexBuilder& vertexBuilder;
};
	}
}

#endif