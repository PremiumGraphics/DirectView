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

typedef std::vector<Face> FaceVector;

class Polygon {
public:

	void setFaces(const std::vector< Face >& faces) { this->faces = faces; }

	std::vector< Face > getFaces() const { return faces; }

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setPositions(const std::vector< Math::Vector3d>& pos) { this->positions = pos;  }

	std::vector< Math::Vector3d > getPositions() const { return positions; }

	void setNormals(const std::vector < Math::Vector3d>& normals) { this->normals = normals; }

	std::vector< Math::Vector3d > getNormals() const { return normals; }

	void setTexCoords(const std::vector<Math::Vector3d>& tex) { this->texCoords = tex; }
	
	std::vector<Math::Vector3d> getTexCoords() const { return texCoords; }

	void rotateX(const double angle);

	void rotateY(const double angle);

	void rotateZ(const double angle);

	void move(const Math::Vector3d& vector) {
		//center += vector;
		for (Math::Vector3d& p : positions) {
			p += vector;
		}

	}

	void scale(const Math::Vector3d& scale);

	bool operator==(const Polygon& rhs) const {
		return
			name == rhs.name &&
			faces == rhs.faces &&
			positions == rhs.positions &&
			normals == rhs.normals &&
			texCoords == rhs.texCoords;
	}

	static Polygon* createTriangle();

	static Polygon* createCricleByNumber(const float radius, const unsigned int divideNumber );

	static Polygon* createCircleByAngle( const float radius, const float divideAngle);

	static Polygon* createCylinder( const float radius, const float height );

	void setCenter(const Math::Vector3d& center) { this->center = center; }

	Math::Vector3d getCenter() const { return center; }


private:
	std::string name;
	std::vector< Face > faces;
	std::vector < Math::Vector3d > positions;
	std::vector < Math::Vector3d > normals;
	std::vector < Math::Vector3d > texCoords;
	Math::Vector3d center;

};

	}
}

#endif