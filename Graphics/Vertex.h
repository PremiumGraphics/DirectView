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

	void move(const Math::Vector3d& vec){
		position += vec;
	}

	unsigned int getId() const { return id; }

	bool operator==(const Vertex& rhs) const {
		return position == rhs.position &&
			id == rhs.id;
	}

	void rotate(const Math::Matrix3d<double>& matrix) {
		position.rotate(matrix);
	}

	void scale(const Math::Vector3d& scale) {
		position.scale(scale.getX(), scale.getY(), scale.getZ());
	}

private:
	Math::Vector3d position;
	unsigned int id;
};

typedef std::vector<Vertex> VertexVector;

	}
}

#endif