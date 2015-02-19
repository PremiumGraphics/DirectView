#ifndef __CRYSTAL_IO_POLYGON_FACTORY_H__
#define __CRYSTAL_IO_POLYGON_FACTORY_H__

#include "../Graphics/PolygonGroup.h"
#include "OBJFile.h"
#include "STLFile.h"
#include <list>


namespace Crystal {
	namespace IO {


class PolygonFactory {
public:
	Graphics::PolygonGroupList create(const OBJFile& file);

	Graphics::PolygonGroupList create(const STLFile& file);
};
	}
}

#endif