#ifndef __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__
#define __CRYSTAL_GRAPHICS_DISPLAY_LIST_H__

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"

#include "ColorRGBA.h"
#include "Face.h"
#include "Polygon.h"

namespace Crystal {
	namespace Graphics{

class DisplayList
{
public:
	DisplayList()
	{}

	DisplayList(Face* f, const ColorRGBA<float>& color) {
		add(f, color);
	}

	DisplayList(Polygon* polygon) {
		add(polygon);
	}

	DisplayList(const Math::Triangle<float>& t);

	DisplayList(const Math::Vector3dVector<float>& poss) {
		vertices = Math::Vector3d<float>::toArray(poss);
	}

	DisplayList(const Math::Vector3dVector<float>& poss, const Math::Vector3dVector<float>& norms) {
		vertices = Math::Vector3d<float>::toArray(poss);
		normals = Math::Vector3d<float>::toArray(norms);
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
		faceIds.clear();
		polygonIds.clear();
		materialIds.clear();
	}

	//void add(Vertex* v);

	void setColors(const std::vector<float>& colors) { this->colors = colors; }

	void add(Face* f, const ColorRGBA<float>& color) {
		const std::vector<float>& vs = Math::Vector3d<float>::toArray(getPositions(*f));
		vertices.insert(vertices.end(), vs.begin(), vs.end());

		const std::vector<float>& ns = Math::Vector3d<float>::toArray(getNormals(*f));
		normals.insert(normals.end(), ns.begin(), ns.end());

		const std::vector<float>& ts = Math::Vector3d<float>::toArray(f->getTexCoords());
		texCoords.insert(texCoords.end(), ts.begin(), ts.end());

		std::vector<unsigned int> vids;
		for (const VertexSPtr& v : f->getVertices()) {
			vids.push_back(v->getId());
		}

		vertexIds.insert(vertexIds.end(), vids.begin(), vids.end());
		ids.push_back(vids);

		const Math::Vector3dVector<float> positions = getPositions(*f);
		for (size_t i = 0; i < positions.size(); ++i) {
			faceIds.push_back(f->getId());
		}

		for (size_t i = 0; i < positions.size(); ++i) {
			const std::vector<float>& cs = color.toArray3();
			colors.insert(colors.end(), cs.begin(), cs.end());
		}

	}

	void add(Polygon* p) {
		for (std::shared_ptr<Face> f : p->getFaces()) {
			add(f.get(), p->getMaterial()->getAmbient());
		}
		for (size_t i = 0; i < p->getVertices().size(); ++i) {
			polygonIds.push_back(p->getId());
			materialIds.push_back(p->getMaterial()->getId());
		}
	}

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

	Math::Vector3dVector<float> getPositions(const Face& f) const {
		Math::Vector3dVector<float> positions;
		const HalfEdgeSPtrList& edges = f.getEdges();
		for (const HalfEdgeSPtr& e : edges) {
			positions.push_back(e->getStartPosition());
			if (e == edges.back() && f.isOpen()) {
				positions.push_back(e->getEndPosition());
			}
		}
		return positions;
	}

	Math::Vector3dVector<float> getNormals(const Face& f) const {
		Math::Vector3dVector<float> normals;
		const HalfEdgeSPtrList& edges = f.getEdges();
		for (const HalfEdgeSPtr& e : edges) {
			normals.push_back(e->getStart()->getNormal());
			if (e == edges.back() && f.isOpen()) {
				normals.push_back(e->getEnd()->getNormal());
			}
		}
		return normals;
	}

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