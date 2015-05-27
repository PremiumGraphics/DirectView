#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Util/UnCopyable.h"

#include "../Math/Vector3d.h"
#include "../Math/Box.h"
#include "Vertex.h"
#include "Face.h"
#include "Material.h"

namespace Crystal {
	namespace Graphics {
		class Material;

class Polygon : private UnCopyable {
public:

	Polygon(unsigned int id, Material* m) :
		id(id),
		material(m),
		isSelected( true )
	{}

	~Polygon()
	{
	}

	bool isSelected;

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setFaces(const FaceSPtrVector& faces) { this->faces = faces; }

	FaceSPtrVector getFaces() const { return faces; }

	void setMaterial(Material* m) { this->material = m; }

	Material* getMaterial() { return material; }

	void setVertices(const VertexSPtrVector& vs) { this->vertices = vs; }

	void addVertices(const VertexSPtrVector& vs) { this->vertices.insert( vertices.end(),vs.begin(), vs.end() ); }

	VertexSPtrVector getVertices() const { return vertices; }

	void move(const Math::Vector3d<float>& vector) {
		//center += vector;
		for (const VertexSPtr v : vertices) {
			v->move(vector);
		}

	}

	bool operator==(const Polygon& rhs) const {
		return
			//faces == rhs.faces &&
			VerticesAreSame(vertices, rhs.vertices);
	}

	void setCenter(const Math::Vector3d<float>& center) { this->center = center; }

	Math::Vector3d<float> getCenter() const { return center; }

	unsigned int getId() const { return id; }

	Material* getMaterial() const { return material; }

private:
	FaceSPtrVector faces;
	VertexSPtrVector vertices;
	Math::Vector3d<float> center;
	Material* material;
	std::string name;
	unsigned int id;
};

typedef std::shared_ptr< Polygon > PolygonSPtr;
typedef std::vector< PolygonSPtr > PolygonSPtrVector;
typedef std::list< PolygonSPtr > PolygonSPtrList;

/*
static Graphics::VertexSPtrVector getFaces(const PolygonSPtrVector& polygons) {
	VertexSPtrVector vertices;
	for (PolygonSPtr p : polygons) {
		const VertexSPtrVector& vv = p->getVertices();
		for ()
			vertices.push_back(p->getVertices())
	}
}


/*
static Graphics::VertexSPtrVector getVertices(const PolygonSPtrVector& polygons ) {
	VertexSPtrVector vertices;
	for (PolygonSPtr p : polygons) {
		const VertexSPtrVector& vv = p->getVertices();
		for ()
		vertices.push_back(p->getVertices() )
	}
}
*/

	}
}

#endif