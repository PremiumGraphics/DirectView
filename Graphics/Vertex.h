#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHCIS_VERTEX_H__

#include "../Math/Vector3d.h"
#include <vector>

namespace Crystal {
	namespace Graphics {

class Vertex{
public:
	Vertex(const Math::Vector3d& position, const unsigned int id) :
		position(position),
		id(id)
	{}

	void setPosition(const Math::Vector3d& position) { this->position = position; }

	Math::Vector3d getPosition() const { return position; }

	void setNormal(const Math::Vector3d& normal) { this->normal = normal; }

	Math::Vector3d getNormal() const { return normal; }

	void move(const Math::Vector3d& vec){
		position += vec;
	}

	unsigned int getId() const { return id; }

	bool operator==(const Vertex& rhs) const {
		return
			position == rhs.position &&
			normal == rhs.normal &&
			id == rhs.id;
	}

	void rotate(const Math::Matrix3d<double>& matrix) {
		position.rotate(matrix);
	}

	void scale(const Math::Vector3d& scale) {
		position.scale(scale.getX(), scale.getY(), scale.getZ());
	}

	static std::vector< Vertex > createVerticesFromPositions( const Math::Vector3dVector& positions ) {
		std::vector< Vertex > vertices;
		unsigned int id = 0;
		for (const Math::Vector3d& position : positions) {
			Vertex v(position, id++);
			vertices.push_back(v);
		}
		return vertices;
	}

private:
	Math::Vector3d position;
	Math::Vector3d normal;
	unsigned int id;
};

typedef std::vector<Vertex> VertexVector;

	}
}

#endif