#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

#include "../Math/Vector3d.h"
#include <vector>
#include <list>
#include <memory>

namespace Crystal {
	namespace Graphics {

template<typename T>
class Vertex final {
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

	Math::Vector3d<T> getPosition() const { return position; }

	Math::Vector3d<T> getNormal() const { return normal; }

	Math::Vector3d<T> getTexCoord() const { return texCoord; }

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

private:
	Math::Vector3d<T> position;
	Math::Vector3d<T> normal;
	Math::Vector3d<T> texCoord;
	unsigned int id;
};

template<typename T>
using VertexSPtr = std::shared_ptr< Vertex<T> >;

template<typename T>
using VertexSPtrVector = std::vector< VertexSPtr<T> >;

	}
}

#endif