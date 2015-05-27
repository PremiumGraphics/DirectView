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

	DisplayList(const Polygon& polygon) {
		add(polygon);
	}

	DisplayList(const Vertex<T>& v) {
		add(v);
	}

	void clear() {
		vertices.clear();
		normals.clear();
		texCoords.clear();
		colors.clear();
	}

	void add(const Polygon& polygon) {
		const auto& vs = polygon.getVertices();
		for (const auto& v : vs) {
			add( *v );
		}
	}

	void add(const Vertex<T>& v) {
		const auto vs = v.getPosition().toArray();
		vertices.insert(vertices.end(), vs.begin(), vs.end());
		const auto ns = v.getNormal().toArray();
		normals.insert(normals.end(), ns.begin(), ns.end());
		const std::vector<float> cs = ColorRGBA<float>::Black().toArray3();
		colors.insert(colors.end(), cs.begin(), cs.end());
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