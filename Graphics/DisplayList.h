#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"

#include "ColorRGBA.h"
#include "Polygon.h"

namespace Crystal {
	namespace Graphics{

template<typename T>
class DisplayList
{
public:
	DisplayList()
	{}

	DisplayList(Polygon* polygon) {
		add(polygon);
	}

	DisplayList(const Math::Vector3dVector<float>& poss) {
		vertices = Math::Vector3d<float>::toArray(poss);
	}

	DisplayList(const Math::Vector3dVector<T>& poss, const Math::Vector3dVector<float>& norms) {
		vertices = Math::Vector3d<T>::toArray(poss);
		normals = Math::Vector3d<T>::toArray(norms);
	}

	DisplayList(const Math::Vector3dVector<float>& poss, const Math::Vector3dVector<float>& norms, const Math::Vector3dVector<float>& texs) {
		vertices = Math::Vector3d<float>::toArray(poss);
		normals = Math::Vector3d<float>::toArray(norms);
		texCoords = Math::Vector3d<float>::toArray(texs);
	}

	void clear() {
		vertices.clear();
		normals.clear();
		texCoords.clear();
		colors.clear();
	}

	//void add(Vertex* v);

	void setColors(const std::vector<float>& colors) { this->colors = colors; }

	std::vector< T > getPositions() const { return vertices; }

	std::vector< T > getNormals() const { return normals; }

	std::vector< T > getTexCoords() const { return texCoords; }

	std::vector< T > getColors() const { return colors; }

	bool isValid() const {
		return
			(vertices.size() % 3 == 0) &&
			(normals.size() % 3 == 0) &&
			(texCoords.size() % 3 == 0);
	}

private:
	std::vector< T > vertices;
	std::vector< T > normals;
	std::vector< T > texCoords;
	std::vector< T > colors;

};



/*
void DisplayList::add(Vertex* v)
{
v->getPosition()
}
*/

	}
}

#endif