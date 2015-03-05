#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "Vertex.h"
#include "Face.h"

namespace Crystal {
	namespace Graphics {


class Polygon {
public:
	Polygon()
	{}

	~Polygon()
	{
		for (Vertex* v : vertices) {
			delete v;
		}
		for (Face* f : faces) {
			delete f;
		}
	}


	void setFaces(const std::vector< Face* >& faces) { this->faces = faces; }

	std::vector< Face* > getFaces() const { return faces; }

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setVertices(const VertexVector& pos) { this->vertices = pos; }

	void setPositions(const Math::Vector3dVector& poss) {
		int i = 0;
		for (const Math::Vector3d& pos : poss) {
			
			this->vertices.push_back( new Vertex(pos, i++));
		}
	}

	VertexVector getVertices() const { return vertices; }

	Math::Vector3dVector getPositions() {
		Math::Vector3dVector vv;
		for (Vertex* v: vertices) {
			vv.push_back(v->getPosition());
		}
		return vv;
	}

	void rotateX(const double angle);

	void rotateY(const double angle);

	void rotateZ(const double angle);

	void move(const Math::Vector3d& vector) {
		//center += vector;
		for (Vertex* v : vertices) {
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


private:
	std::string name;
	std::vector< Face* > faces;
	VertexVector vertices;
	Math::Vector3d center;

};

	}
}

#endif