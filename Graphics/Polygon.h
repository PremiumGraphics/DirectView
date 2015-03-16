#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"
#include "Material.h"

namespace Crystal {
	namespace Graphics {
		class Material;
		typedef std::shared_ptr< Material > MaterialSPtr;

class Polygon {
public:

	Polygon(unsigned int id) :
		id(id),
		material(new Material())
	{}

	~Polygon()
	{
	}


	void setFaces(const FaceSPtrVector& faces) { this->faces = faces; }

	FaceSPtrVector getFaces() const { return faces; }

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setVertices(const VertexSPtrVector& vs) { this->vertices = vs; }

	void addVertices(const VertexSPtrVector& vs) { this->vertices.insert( vertices.end(),vs.begin(), vs.end() ); }

	VertexSPtrVector getVertices() const { return vertices; }

	Math::Vector3dVector getPositions() {
		Math::Vector3dVector vv;
		for (const VertexSPtr& v: vertices) {
			vv.push_back(v->getPosition());
		}
		return vv;
	}

	Math::Vector3dVector getNormals() {
		Math::Vector3dVector vv;
		for (const VertexSPtr v : vertices) {
			vv.push_back(v->getNormal());
		}
		return vv;
	}

	void rotateX(const double angle);

	void rotateY(const double angle);

	void rotateZ(const double angle);

	void move(const Math::Vector3d& vector) {
		//center += vector;
		for (const VertexSPtr v : vertices) {
			v->move(vector);
		}

	}

	void scale(const Math::Vector3d& scale);

	bool operator==(const Polygon& rhs) const {
		return
			name == rhs.name &&
			//faces == rhs.faces &&
			VerticesAreSame(vertices, rhs.vertices);
	}

	void setCenter(const Math::Vector3d& center) { this->center = center; }

	Math::Vector3d getCenter() const { return center; }

	unsigned int getId() const { return id; }

	MaterialSPtr getMaterial() const { return material; }

	void setMaterial(const MaterialSPtr& m) { this->material = m; }

private:
	std::string name;
	FaceSPtrVector faces;
	VertexSPtrVector vertices;
	Math::Vector3d center;
	MaterialSPtr material;
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