#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

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

	Vertex(const Math::Vector3d& position, const Math::Vector3d& normal, const unsigned int id) :
		position( position ),
		normal( normal ),
		id(id)
	{}

	void setPosition(const Math::Vector3d& position) { this->position = position; }

	Math::Vector3d getPosition() const { return position; }

	void setNormal(const Math::Vector3d& normal) { this->normal = normal; }

	Math::Vector3d getNormal() const { return normal; }

	void setTexCoord(const Math::Vector3d& texCoord) { this->texCoord = texCoord; }

	Math::Vector3d getTexCoord() const { return texCoord; }

	void move(const Math::Vector3d& vec){
		position += vec;
	}

	unsigned int getId() const { return id; }

	bool equals(const Vertex& rhs) const {
		return
			position == rhs.position &&
			normal == rhs.normal &&
			id == rhs.id;
	}

	bool operator==(const Vertex& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Vertex& rhs) const {
		return !equals(rhs);
	}

	void rotate(const Math::Matrix3d<double>& matrix) {
		position.rotate(matrix);
	}

	void scale(const Math::Vector3d& scale) {
		position.scale(scale.getX(), scale.getY(), scale.getZ());
	}

	static std::vector< Vertex* > createVerticesFromPositions( const Math::Vector3dVector& positions ) {
		std::vector< Vertex* > vertices;
		unsigned int id = 0;
		for (const Math::Vector3d& position : positions) {
			Vertex* v = new Vertex(position, id++);
			vertices.push_back(v);
		}
		return vertices;
	}

	static std::vector< Vertex* > createVerticesFromPositionsAndNormals(const Math::Vector3dVector& positions, const Math::Vector3dVector& normals) {
		assert(positions.size() == normals.size());
		std::vector< Vertex* > vertices;
		unsigned int id = 0;
		for (size_t i = 0; i < positions.size(); ++i) {
			Vertex* v = new Vertex(positions[i], normals[i], id++);
			vertices.push_back(v);
		}
		return vertices;
	}


private:
	Math::Vector3d position;
	Math::Vector3d normal;
	Math::Vector3d texCoord;
	unsigned int id;
};

typedef std::vector<Vertex*> VertexVector;

static bool VerticesAreSame(const VertexVector& lhs, const VertexVector& rhs)
{
	if (lhs.size() != rhs.size()) {
		return false;
	}
	for (size_t i = 0; i < rhs.size(); ++i) {
		if (*lhs[i] != *rhs[i]) {
			return false;
		}
	}
	return true;
}

	}
}

#endif