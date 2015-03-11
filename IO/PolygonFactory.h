#ifndef __CRYSTAL_IO_POLYGON_FACTORY_H__
#define __CRYSTAL_IO_POLYGON_FACTORY_H__

#include "../Graphics/Polygon.h"
#include "OBJFile.h"
#include "STLFile.h"
#include <list>


namespace Crystal {
	namespace IO {


class PolygonFactory {
public:
	Graphics::PolygonSPtrList create(const OBJFile& file);

	Graphics::PolygonSPtrList create(const STLFile& file);
};
	}
}

#endif