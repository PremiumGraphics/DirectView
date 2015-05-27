#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

#include "../Math/Vector3d.h"
#include "ColorRGBA.h"
#include <vector>
#include <list>
#include <memory>
#include <tuple>

namespace Crystal {
	namespace Graphics {

template<typename T>
//using Vertex = std::tuple < Math::Vector3d<T>, Math::Vector3d<T>, Math::Vector3d<T> >;

class Vertex final {
public:
	explicit Vertex(const Math::Vector3d<T>& position) :
		position(position)
	{}

	Vertex(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal) :
		position( position ),
		normal( normal )
	{}

	Vertex(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal, const Math::Vector3d<T>& texCoord ) :
		position(position),
		normal(normal),
		texCoord( texCoord )
	{}

	Vertex(const Math::Vector3d<T>& position, const Math::Vector3d<T>& normal, const Math::Vector3d<T>& texCoord, const ColorRGBA<T>& color) :
		position(position),
		normal(normal),
		texCoord(texCoord),
		color(color)
	{}


	Math::Vector3d<T> getPosition() const { return position; }

	Math::Vector3d<T> getNormal() const { return normal; }

	Math::Vector3d<T> getTexCoord() const { return texCoord; }

	ColorRGBA<T> getColor() const { return color; }

private:
	Math::Vector3d<T> position;
	Math::Vector3d<T> normal;
	Math::Vector3d<T> texCoord;
	ColorRGBA<T> color;
};

template<typename T>
using VertexSPtr = std::shared_ptr< Vertex<T> >;

template<typename T>
using VertexSPtrVector = std::vector< VertexSPtr<T> >;

	}
}

#endif