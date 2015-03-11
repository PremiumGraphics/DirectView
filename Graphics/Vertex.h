#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

#include "../Math/Vector3d.h"
#include <vector>
#include <list>
#include <memory>

namespace Crystal {
	namespace Graphics {
		class HalfEdge;
		typedef std::shared_ptr<HalfEdge> HalfEdgeSPtr;
		typedef std::list< HalfEdgeSPtr > HalfEdgeSPtrList;

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

	void addEdge(const HalfEdgeSPtr& e) { this->edges.push_back( e ); }

	HalfEdgeSPtrList getEdges() const { return edges; }

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
	HalfEdgeSPtrList edges;
	unsigned int id;
};

typedef std::shared_ptr< Vertex > VertexSPtr;
typedef std::vector< VertexSPtr > VertexSPtrVector;

class VertexBuilder {
public:
	VertexBuilder() :
		nextId( 0 )
	{}

	~VertexBuilder() {
	}


	VertexSPtr build(const Math::Vector3d& position) {
		return VertexSPtr( new Vertex(position, nextId++));
	}

	VertexSPtr build(const Math::Vector3d& position, const Math::Vector3d& normal) {
		return VertexSPtr(new Vertex(position, normal, nextId++));
	}

	VertexSPtr build(const Math::Vector3d& position, const Math::Vector3d& normal, const Math::Vector3d& texCoord){
		return VertexSPtr(new Vertex(position, normal, texCoord, nextId++));
	}

	VertexSPtrVector buildVerticesFromPositions(const Math::Vector3dVector& positions) {
		VertexSPtrVector vertices;
		for (const Math::Vector3d& position : positions) {
			VertexSPtr v(new Vertex(position, nextId++));
			vertices.push_back(v);
		}
		return vertices;
	}

	VertexSPtrVector buildVerticesFromPositionsAndNormals(const Math::Vector3dVector& positions, const Math::Vector3dVector& normals) {
		assert(positions.size() == normals.size());
		VertexSPtrVector vertices;
		for (size_t i = 0; i < positions.size(); ++i) {
			VertexSPtr v( new Vertex(positions[i], normals[i], nextId++) );
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

private:
	unsigned int nextId;
};


static bool VerticesAreSame(const VertexSPtrVector& lhs, const VertexSPtrVector& rhs)
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