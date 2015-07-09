#ifndef __CRYSTAL_GRAPHICS_BRUSH_H__
#define __CRYSTAL_GRAPHICS_BRUSH_H__

#include "../Math/Vector.h"


namespace Crystal {
	namespace Graphics {

template<typename T>
class Brush3d
{
public:
	Brush3d() :
		pos(Math::Vector3d<T>(0, 0, 0)),
		size(Math::Vector3d<T>(1, 1, 1))
	{}

	explicit Brush3d(const Math::Vector3d<T>& pos) :
		pos(pos),
		size(Math::Vector3d<T>(1, 1, 1))
	{}

	Brush3d(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& size) :
		pos(pos),
		size(size)
	{}

	Math::Vector3d<T> getPosition() const{ return pos; }

	void move(const Math::Vector3d<T>& v) {
		this->pos += v;
	}

private:
	Math::Vector3d<T> pos;
	Math::Vector3d<T> size;
};
	}
}

#endif