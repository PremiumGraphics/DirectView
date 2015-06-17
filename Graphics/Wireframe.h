#ifndef __CRYSTAL_GRAPHICS_WIREFRAME_H__
#define __CRYSTAL_GRAPHICS_WIREFRAME_H__

#include "../Math/Line.h"
#include "../Math/Triangle.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Wireframe final
{
public:
	Wireframe() = default;

	~Wireframe() = default;

	void add(const Math::Triangle<T>& t) {
		lines.emplace_back( Math::Line3d<T>( t.getv0(), t.getv1() ) );
		lines.emplace_back( Math::Line3d<T>( t.getv1(), t.getv2() ) );
		lines.emplace_back( Math::Line3d<T>( t.getv2(), t.getv0() ) );
	}

	Math::Line3dVector<T> getLines() const { return lines; }

private:
	Math::Line3dVector<T> lines;
};
	}
}

#endif