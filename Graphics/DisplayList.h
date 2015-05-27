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

		ids.clear();
		vertexIds.clear();
	}

	//void add(Vertex* v);

	void setColors(const std::vector<float>& colors) { this->colors = colors; }

	std::vector< float > getPositions() const { return vertices; }

	std::vector< float > getNormals() const { return normals; }

	std::vector< float > getTexCoords() const { return texCoords; }

	std::vector< float > getColors() const { return colors; }

	std::vector< unsigned int > getVertexIds() const { return vertexIds; }

	void setIds(const std::vector< std::vector< unsigned int > >& ids) { this->ids = ids; }

	std::vector< std::vector< unsigned int > >getIds() const { return ids; }

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
	std::vector< unsigned int > vertexIds;
	std::vector< std::vector< unsigned int > > ids;

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