#ifndef __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_BUILDER_H__

#include "Polygon.h"

#include "Face.h"
#include "Vertex.h"
#include "Material.h"

#include "../Math/Cone.h"
#include "../Math/Cylinder.h"
#include "../Math/Triangle.h"

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


	PolygonSPtr build() { 
		PolygonSPtr p(new Polygon(nextId++, materialBuilder->build()) );
		polygons.push_back(p);
		return p;
	}

	PolygonSPtr buildQuad();

	PolygonSPtr buildBox();

	PolygonSPtr buildCircleByNumber(const float radius, const unsigned int divideNumber);

	PolygonSPtr buildCircleByAngle(const float radius, const float divideAngle);

	PolygonSPtr build(const Math::Triangle& t);

	PolygonSPtr build(const unsigned int divideNuber, const Math::Cylinder& c);

	PolygonSPtr buildSphere(const unsigned int uDivideNumber, const unsigned int vDivideNumber);

	PolygonSPtr build(const unsigned int divideNumber, const Math::Cone& cone);

	FaceSPtrVector getFaces() const { return faceBuilder->getFaces(); }

	FaceBuilderSPtr getFaceBuilder() const { return faceBuilder; }

	VertexSPtrVector getVertices() const { return faceBuilder->getVertexBuilder()->getVertices(); }

	VertexBuilderSPtr getVertexBuilder() const { return faceBuilder->getVertexBuilder(); }

	HalfEdgeBuilderSPtr getHalfEdgeBuilder() const { return faceBuilder->getHalfEdgeBuilder(); }

	MaterialBuilderSPtr getMaterialBuilder() const { return materialBuilder; }

	void remove(const PolygonSPtr& p) { polygons.remove(p); }

	void clear(){
		polygons.clear();
		nextId = 0;
	}

	PolygonSPtrList getPolygons() const { return polygons; }

private:
	unsigned int nextId;

	PolygonSPtrList polygons;
	FaceBuilderSPtr faceBuilder;
	MaterialBuilderSPtr materialBuilder;
};

typedef std::shared_ptr< PolygonBuilder > PolygonBuilderSPtr;

	}
}

#endif