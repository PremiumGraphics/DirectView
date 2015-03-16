#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "Polygon.h"

#include "Face.h"
#include "Vertex.h"
#include "Material.h"

#include <memory>

namespace Crystal{
	namespace Graphics{

class PolygonBuilder{
public:

	PolygonBuilder() :
		faceBuilder( FaceBuilderSPtr(new FaceBuilder() ) ),
		materialBuilder(MaterialBuilderSPtr( new MaterialBuilder() )),
		nextId(0)
	{}

	PolygonBuilder(const FaceBuilderSPtr& faceBuilder) :
		nextId(0),
		faceBuilder( faceBuilder )
	{}

	PolygonBuilder(const FaceBuilderSPtr& faceBuilder, const MaterialBuilderSPtr& materialBuilder) :
		nextId(0),
		faceBuilder(faceBuilder),
		materialBuilder( materialBuilder )
	{}


	PolygonSPtr build() { return PolygonSPtr(new Polygon(nextId++) ); }

	PolygonSPtr buildQuad();

	PolygonSPtr buildBox();

	PolygonSPtr buildCircleByNumber(const float radius, const unsigned int divideNumber);

	PolygonSPtr buildCircleByAngle(const float radius, const float divideAngle);

	PolygonSPtr buildTriangle() { return buildCircleByNumber(1.0f, 3); }

	PolygonSPtr buildCylinder(const unsigned int divideNuber);

	PolygonSPtr buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	PolygonSPtr buildCone(const unsigned int divideNumber);

	FaceBuilderSPtr getFaceBuilder() const { return faceBuilder; }

	VertexBuilderSPtr getVertexBuilder() const { return faceBuilder->getVertexBuilder(); }

	HalfEdgeBuilderSPtr getHalfEdgeBuilder() const { return faceBuilder->getHalfEdgeBuilder(); }

	MaterialBuilderSPtr getMaterialBuilder() const { return materialBuilder; }

	void clear(){
		nextId = 0;
	}

private:
	unsigned int nextId;

	FaceBuilderSPtr faceBuilder;
	MaterialBuilderSPtr materialBuilder;
};

typedef std::shared_ptr< PolygonBuilder > PolygonBuilderSPtr;

	}
}

#endif