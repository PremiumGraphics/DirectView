#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include <vector>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics{
		class Face;
		class Polygon;

class DisplayList
{
public:
	DisplayList()
	{}

	DisplayList(Face* f);

	DisplayList(Polygon* polygon);

	DisplayList(const Math::Vector3dVector& poss) {
		vertices = Math::toArray(poss);
	}

	DisplayList(const Math::Vector3dVector& poss, const Math::Vector3dVector& norms) {
		vertices = Math::toArray(poss);
		normals = Math::toArray(norms);
	}

	DisplayList(const Math::Vector3dVector& poss, const Math::Vector3dVector& norms, const Math::Vector3dVector& texs) {
		vertices = Math::toArray(poss);
		normals = Math::toArray(norms);
		texCoords = Math::toArray(texs);
	}

	std::vector< float > getPositions() const { return vertices; }

	std::vector< float > getNormals() const { return normals; }

	std::vector< float > getTexCoords() const { return texCoords; }

	bool isValid() const {
		return
			(vertices.size() % 3 == 0) &&
			(normals.size() % 3 == 0) &&
			(texCoords.size() % 3 == 0);
	}

private:
	std::vector< float > vertices;
	std::vector< float > normals;
	std::vector< float > texCoords;
};
	}
}

#endif