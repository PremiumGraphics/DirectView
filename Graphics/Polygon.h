#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"

namespace Crystal {
	namespace Graphics {
		class Material;
		typedef std::shared_ptr< Material > MaterialSPtr;

class Polygon {
public:

	Polygon(unsigned int id) :
		id(id)
	{}

	~Polygon()
	{
	}


	void setFaces(const FaceVector& faces) { this->faces = faces; }

	FaceVector getFaces() const { return faces; }

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setVertices(const VertexVector& vs) { this->vertices = vs; }

	void addVertices(const VertexVector& vs) { this->vertices = vs; }

	VertexVector getVertices() const { return vertices; }

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
	FaceVector faces;
	VertexVector vertices;
	Math::Vector3d center;
	MaterialSPtr material;
	unsigned int id;
};

typedef std::shared_ptr< Polygon > PolygonSPtr;
typedef std::vector< PolygonSPtr > PolygonSPtrVector;
typedef std::list< PolygonSPtr > PolygonSPtrList;

	}
}

#endif