#ifndef __CRYSTAL_GRAPHICS_POLYGON_H__
#define __CRYSTAL_GRAPHICS_POLYGON_H__

#include <vector>
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

class Vertex{
public:


	Vertex(const Math::Vector3d& position, const unsigned int id) :
		position(position),
		id(id)
	{}

	void setPosition(const Math::Vector3d& position) { this->position = position; }

	Math::Vector3d getPosition() const { return position;  }

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

class Face {
public:
	Face(){};

	Face(const std::vector<unsigned int >& vertexIds) :
		vertexIds( vertexIds)
	{}

	Face(const std::vector<unsigned int >& vertexIds, const std::vector<unsigned int>& normalIds) :
		vertexIds(vertexIds),
		normalIds(normalIds)
	{}

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

	void setPositions(const VertexVector& pos) { this->positions = pos;  }

	void setPositions(const Math::Vector3dVector& poss) {
		int i = 0;
		for (const Math::Vector3d& pos : poss) {
			this->positions.push_back(Vertex(pos, i++));
		}
	}

	VertexVector getVertices() const { return positions; }

	Math::Vector3dVector getPositions() {
		Math::Vector3dVector vv;
		for (const Vertex& v : positions) {
			vv.push_back(v.getPosition());
		}
		return vv;
	}

	void setNormals(const std::vector < Math::Vector3d>& normals) { this->normals = normals; }

	std::vector< Math::Vector3d > getNormals() const { return normals; }

	void setTexCoords(const std::vector<Math::Vector3d>& tex) { this->texCoords = tex; }
	
	std::vector<Math::Vector3d> getTexCoords() const { return texCoords; }

	void rotateX(const double angle);

	void rotateY(const double angle);

	void rotateZ(const double angle);

	void move(const Math::Vector3d& vector) {
		//center += vector;
		for (Vertex& v : positions) {
			v.move(vector);
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

	void setCenter(const Math::Vector3d& center) { this->center = center; }

	Math::Vector3d getCenter() const { return center; }


private:
	std::string name;
	std::vector< Face > faces;
	VertexVector positions;
	std::vector < Math::Vector3d > normals;
	std::vector < Math::Vector3d > texCoords;
	Math::Vector3d center;

};

	}
}

#endif