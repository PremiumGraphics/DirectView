#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

#include "../Math/Vector3d.h"
#include <vector>
#include <list>

namespace Crystal {
	namespace Graphics {
		class HalfEdge;

class Vertex {
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

	Vertex(const Math::Vector3d& position, const Math::Vector3d& normal, const Math::Vector3d& texCoord, const unsigned int id) :
		position(position),
		normal(normal),
		texCoord( texCoord ),
		id(id)
	{}

	void setPosition(const Math::Vector3d& position) { this->position = position; }

	Math::Vector3d getPosition() const { return position; }

	void setNormal(const Math::Vector3d& normal) { this->normal = normal; }

	Math::Vector3d getNormal() const { return normal; }

	void setTexCoord(const Math::Vector3d& texCoord) { this->texCoord = texCoord; }

	Math::Vector3d getTexCoord() const { return texCoord; }

	void addEdge(HalfEdge* e) { this->edges.push_back( e ); }

	std::list<HalfEdge*> getEdges() const { return edges; }

	void move(const Math::Vector3d& vec){
		position += vec;
	}

	unsigned int getId() const { return id; }

	bool equals(const Vertex& rhs) const {
		return
			position == rhs.position &&
			normal == rhs.normal &&
			texCoord == rhs.texCoord &&
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

private:
	Math::Vector3d position;
	Math::Vector3d normal;
	Math::Vector3d texCoord;
	std::list< HalfEdge* > edges;
	unsigned int id;
};

typedef std::vector<Vertex*> VertexVector;

class VertexBuilder {
public:
	VertexBuilder() :
		nextId( 0 )
	{}

	~VertexBuilder() {
		clear();
	}

	void clear() {
		for (Vertex* v : vertices) {
			delete v;
		}
		vertices.clear();
	}

	Vertex* build(const Math::Vector3d& position) {
		vertices.push_back(new Vertex(position, nextId++));
		return vertices.back();
	}

	Vertex* build(const Math::Vector3d& position, const Math::Vector3d& normal) {
		vertices.push_back(new Vertex(position, normal, nextId++));
		return vertices.back();
	}

	Vertex* build(const Math::Vector3d& position, const Math::Vector3d& normal, const Math::Vector3d& texCoord){
		vertices.push_back(new Vertex(position, normal, texCoord, nextId++));
		return vertices.back();
	}

	VertexVector buildVerticesFromPositions(const Math::Vector3dVector& positions) {
		std::vector< Vertex* > vertices;
		for (const Math::Vector3d& position : positions) {
			Vertex* v = new Vertex(position, nextId++);
			vertices.push_back(v);
		}
		return vertices;
	}

	VertexVector buildVerticesFromPositionsAndNormals(const Math::Vector3dVector& positions, const Math::Vector3dVector& normals) {
		assert(positions.size() == normals.size());
		std::vector< Vertex* > vertices;
		for (size_t i = 0; i < positions.size(); ++i) {
			Vertex* v = new Vertex(positions[i], normals[i], nextId++);
			vertices.push_back(v);
		}
		return vertices;
	}

	static std::vector< Vertex* > buildVerticesFromPositionsNormalsTexCoords(const Math::Vector3dVector& positions, const Math::Vector3dVector& normals, const Math::Vector3dVector& texCoords) {
		assert(positions.size() == normals.size());
		assert(normals.size() == texCoords.size());
		std::vector< Vertex* > vertices;
		for (size_t i = 0; i < positions.size(); ++i) {
			Vertex* v = new Vertex(positions[i], normals[i], texCoords[i], i);
			vertices.push_back(v);
		}
		return vertices;
	}

	VertexVector getVertices() const { return vertices; }

private:
	VertexVector vertices;
	unsigned int nextId;
};


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