#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics{

class Face;
class Polygon;
class Vertex;
typedef std::shared_ptr< Vertex > VertexSPtr;
class PolygonGroup;

class DisplayList
{
public:
	DisplayList()
	{}

	DisplayList(Face* f, const ColorRGBA<float>& color);

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

	void clear();

	//void add(Vertex* v);

	void setColors(const std::vector<float>& colors) { this->colors = colors; }

	void add(Face* f, const ColorRGBA<float>& color);

	void add(Polygon* p);

	std::vector< float > getPositions() const { return vertices; }

	std::vector< float > getNormals() const { return normals; }

	std::vector< float > getTexCoords() const { return texCoords; }

	std::vector< float > getColors() const { return colors; }

	std::vector< unsigned int > getVertexIds() const { return vertexIds; }

	std::vector< unsigned int > getFaceIds() const { return faceIds; }

	std::vector< unsigned int > getPolygonIds() const { return polygonIds; }

	void setIds(const std::vector< std::vector< unsigned int > >& ids) { this->ids = ids; }

	std::vector< std::vector< unsigned int > >getIds() const { return ids; }

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
	std::vector< float > colors;
	std::vector< unsigned int > vertexIds;
	std::vector< unsigned int > faceIds;
	std::vector< unsigned int > polygonIds;
	std::vector< unsigned int > materialIds;
	std::vector< std::vector< unsigned int > > ids;

	std::vector<unsigned int> getVertexIds(const Face& f) const;

	Math::Vector3dVector getPositions(const Face& f) const;

	Math::Vector3dVector getNormals(const Face& f) const;

};

	}
}

#endif