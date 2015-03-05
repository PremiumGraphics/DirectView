#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include <vector>

namespace Crystal {
	namespace Graphics{
		class Polygon;

class DisplayList
{
public:
	DisplayList()
	{}

	DisplayList(Polygon* polygon);

	std::vector< float > getPositions() const { return positions; }

	std::vector< float > getNormals() const { return normals; }

	std::vector< float > getTexCoords() const { return texCoords; }

private:
	std::vector< float > positions;
	std::vector< float > normals;
	std::vector< float > texCoords;
};
	}
}

#endif