#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

class Face {
public:
	std::vector< unsigned int > vertexIds;
	std::vector< unsigned int > normalIds;
	std::vector< unsigned int > texIds;

	bool operator==(const Face& rhs) const {
		return
			vertexIds == rhs.vertexIds &&
			normalIds == rhs.normalIds &&
			texIds == rhs.texIds;
	}
};

class Polygon {
public:
	std::vector< Face > faces;
	std::vector < Math::Vector3d > positions;
	std::vector < Math::Vector3d > normals;
	std::vector < Math::Vector3d > texCoords;
	std::string name;

	bool operator==(const Polygon& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			positions == rhs.positions &&
			normals == rhs.normals &&
			texCoords == rhs.texCoords;
	}
};

	}
}

#endif