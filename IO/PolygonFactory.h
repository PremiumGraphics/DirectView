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
	Graphics::Polygon* create(const OBJFile& file);

	Graphics::Polygon* create(const STLFile& file);
};
	}
}

#endif