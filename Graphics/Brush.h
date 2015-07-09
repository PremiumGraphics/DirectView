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
		size(Math::Vector3d<T>(1, 1, 1)),
		density(0.1f)
	{}

	explicit Brush3d(const Math::Vector3d<T>& pos) :
		pos(pos),
		size(Math::Vector3d<T>(1, 1, 1)),
		density(0.1f)
	{}

	Brush3d(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& size) :
		pos(pos),
		size(size),
		density(0.1f)
	{}

	Math::Vector3d<T> getPosition() const{ return pos; }

	Math::Vector3d<T> getSize() const { return size; }

	void move(const Math::Vector3d<T>& v) {
		this->pos += v;
	}

	void scale(const Math::Vector3d<T>& s) {
		this->size.scale(x);
	}

	void addSize(const Math::Vector3d<T>& s) {
		this->size += s;
	}

	T getDensity() const { return density; }

private:
	Math::Vector3d<T> pos;
	Math::Vector3d<T> size;
	T density;
};
	}
}

#endif