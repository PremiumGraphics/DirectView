#ifndef __CRYSTAL_GRAPHICS_BRUSH_H__
#define __CRYSTAL_GRAPHICS_BRUSH_H__

#include "../Math/Vector.h"
#include "../Math/Volume.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Brush3d final
{
public:
	Brush3d() :
		center(Math::Vector3d<T>(0, 0, 0)),
		size(Math::Vector3d<T>(1, 1, 1)),
		density(0.1f)
	{}

	explicit Brush3d(const Math::Vector3d<T>& pos) :
		center(pos),
		size(Math::Vector3d<T>(1, 1, 1)),
		density(0.1f)
	{}

	Brush3d(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& size) :
		center(pos),
		size(size),
		density(0.1f)
	{}

	~Brush3d() = default;

	Math::Vector3d<T> getPosition() const{ return center; }

	Math::Vector3d<T> getSize() const { return size; }

	void move(const Math::Vector3d<T>& v) {
		this->center += v;
	}

	void scale(const Math::Vector3d<T>& s) {
		this->size.scale(x);
	}

	void addSize(const Math::Vector3d<T>& s) {
		this->size += s;
	}

	T getDensity() const { return density; }

	void add(Math::Volume3d<float>& grid) const {
		const T radius = size.getX();
		for (size_t x = 0; x < grid.getSizeX(); ++x) {
			for (size_t y = 0; y < grid.getSizeY(); ++y) {
				for (size_t z = 0; z < grid.getSizeZ(); ++z) {
					const auto& pos = grid.toCenterPosition(x, y, z);
					if (center.getDistanceSquared(pos) < radius * radius) {
						const auto v = getValue(pos);
						grid.add(x, y, z, v);
					}
					/*
					metaball.getSpace();
					const auto& pos = toCenterPosition(x, y, z);
					*/
				}
			}
		}
	}

	T getValue(const Math::Vector3d<T>& pos) const
	{
		const auto dist = pos.getDistance(center);
		const auto v = 1.0f - dist / size.getX();//radius;
		return v * density;
	}



private:
	Math::Vector3d<T> center;
	Math::Vector3d<T> size;
	T density;
};

template<typename T>
using Brush3dVector = std::vector < Brush3d<T> > ;

	}
}

#endif