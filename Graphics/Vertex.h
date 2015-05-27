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

template<typename T>
class Vertex {
public:
	Vertex(const Math::Vector3d<T>& position, const unsigned int id) :
		position(position),
		id(id)
	{}

	Vertex(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal, const unsigned int id) :
		position( position ),
		normal( normal ),
		id(id)
	{}

	Vertex(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal, const Math::Vector3d<T>& texCoord, const unsigned int id) :
		position(position),
		normal(normal),
		texCoord( texCoord ),
		id(id)
	{}

	void setPosition(const Math::Vector3d<T>& position) { this->position = position; }

	Math::Vector3d<T> getPosition() const { return position; }

	void setNormal(const Math::Vector3d<T>& normal) { this->normal = normal; }

	Math::Vector3d<T> getNormal() const { return normal; }

	void setTexCoord(const Math::Vector3d<T>& texCoord) { this->texCoord = texCoord; }

	Math::Vector3d<T> getTexCoord() const { return texCoord; }

	void removeEdge(HalfEdge* e) {
		edges.remove(e);
	}

	void addEdge(HalfEdge* e) { this->edges.push_back( e ); }

	std::list< HalfEdge* > getEdges() const { return edges; }

	void move(const Math::Vector3d<T>& vec){
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

	void rotate(const Math::Matrix3d<float>& matrix) {
		position.rotate(matrix);
	}

	void scale(const Math::Vector3d<T>& scale) {
		position.scale(scale.getX(), scale.getY(), scale.getZ());
	}

private:
	Math::Vector3d<T> position;
	Math::Vector3d<T> normal;
	Math::Vector3d<T> texCoord;
	std::list< HalfEdge* > edges;
	unsigned int id;
};

typedef std::shared_ptr< Vertex<float> > VertexSPtr;
typedef std::vector< VertexSPtr > VertexSPtrVector;

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