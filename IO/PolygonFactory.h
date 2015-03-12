#ifndef __CRYSTAL_IO_POLYGON_FACTORY_H__
#define __CRYSTAL_IO_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"
#include "../Graphics/PolygonBuilder.h"
#include "OBJFile.h"
#include "STLFile.h"
#include <list>


namespace Crystal {
	namespace IO {


class PolygonFactory {
public:
	PolygonFactory( Graphics::PolygonBuilder& pBuilder ) :
		pBuilder( pBuilder ),
		vBuilder(pBuilder.getVertexBuilder() ),
		fBuilder(pBuilder.getFaceBuilder() ),
		eBuilder(pBuilder.getHalfEdgeBuilder() )
	{}

	Graphics::PolygonSPtrList create(const OBJFile& file);

	Graphics::PolygonSPtrList create(const STLFile& file);

private:
	Graphics::PolygonBuilder& pBuilder;
	Graphics::VertexBuilderSPtr vBuilder;
	Graphics::HalfEdgeBuilderSPtr eBuilder;
	Graphics::FaceBuilderSPtr fBuilder;
};
	}
}

#endif