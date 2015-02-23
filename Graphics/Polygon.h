#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

class Face {
public:
	void setNormalIds(const std::vector<unsigned int>& normalIds) { this->normalIds = normalIds; }

	std::vector<unsigned int> getNormalIds() const { return normalIds; }

	void setVertexIds(const std::vector<unsigned int >& vertexIds) { this->vertexIds = vertexIds;  }

	std::vector< unsigned int > getVertexIds() const { return vertexIds; }

	void setTexIds(const std::vector<unsigned int>& texIds) { this->texIds = texIds; }

	std::vector< unsigned int > getTexIds() const { return texIds; }

	bool operator==(const Face& rhs) const {
		return
			vertexIds == rhs.vertexIds &&
			normalIds == rhs.normalIds &&
			texIds == rhs.texIds;
	}

private:
	std::vector< unsigned int > vertexIds;
	std::vector< unsigned int > texIds;
	std::vector< unsigned int > normalIds;
};

class Polygon {
public:
	std::vector< Face > faces;

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setPositions(const std::vector< Math::Vector3d>& pos) { this->positions = pos;  }

	std::vector< Math::Vector3d > getPositions() const { return positions; }

	void setNormals(const std::vector < Math::Vector3d>& normals) { this->normals = normals; }

	std::vector< Math::Vector3d > getNormals() const { return normals; }

	void setTexCoords(const std::vector<Math::Vector3d>& tex) { this->texCoords = tex; }
	
	std::vector<Math::Vector3d> getTexCoords() const { return texCoords; }

	void scale(const Math::Vector3d& scale) {
		for (Math::Vector3d& p : positions) {
			p.scale(scale.getX(), scale.getY(), scale.getZ());
		}
	}

	bool operator==(const Polygon& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			positions == rhs.positions &&
			normals == rhs.normals &&
			texCoords == rhs.texCoords;
	}

	static Polygon* createTriangle();

	static Polygon* createQuad();

	static Polygon* createCircle( const float radius, const float divideAngle);

	static Polygon* createCylinder();

private:
	std::string name;
	std::vector < Math::Vector3d > positions;
	std::vector < Math::Vector3d > normals;
	std::vector < Math::Vector3d > texCoords;

};

	}
}

#endif