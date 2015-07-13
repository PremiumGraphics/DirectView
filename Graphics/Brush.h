#ifndef __CRYSTAL_GRAPHICS_BRUSH_H__
#define __CRYSTAL_GRAPHICS_BRUSH_H__

#include "../Math/Vector.h"
#include "../Math/Volume.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Brush {
public:
	Brush() = default;

	explicit Brush(const Math::Vector3d<T>& center) :
		center(center),
		size(1,1,1)
	{}

	Brush(const Math::Vector3d<T>& center, const Math::Vector3d<T>& size) :
		center(center),
		size(size)
	{}

	~Brush() = default;

	Math::Vector3d<T> getCenter() const { return center; }

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

	Math::Vector3d<T> getMinPosition() const { return center - size*0.5; }

	Math::Vector3d<T> getMaxPosition() const { return center + size*0.5; }

	//Space3d<T> getSpace() const { return Space3d<T>( ) }

	virtual void add(Math::Volume3d<float>& grid) const = 0;


	Math::Space3d<T> getSpace() const {
		const auto& start = getMinPosition();
		return Math::Space3d<T>(start, size);
	}


private:
	Math::Vector3d<T> center;
	Math::Vector3d<T> size;
};

template<typename T>
class BlendBrush final : public Brush<T>
{
public:
	BlendBrush() :
		Brush( Math::Vector3d<T>(0, 0, 0) ),
		density(0.1f)
	{}

	explicit BlendBrush(const Math::Vector3d<T>& pos) :
		Brush(pos, Math::Vector3d<T>(1, 1, 1)),
		density(0.1f)
	{}

	BlendBrush(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& size) :
		Brush(pos,size),
		density(0.1f)
	{}

	~BlendBrush() = default;

	T getDensity() const { return density; }

	virtual void add(Math::Volume3d<float>& grid) const override {
		const T radius = getSize().getX() * T(0.5);
		for (size_t x = 0; x < grid.getResolutions()[0]; ++x) {
			for (size_t y = 0; y < grid.getResolutions()[1]; ++y) {
				for (size_t z = 0; z < grid.getResolutions()[2]; ++z) {
					const auto& pos = grid.toCenterPosition(x, y, z);
					if ( getCenter().getDistanceSquared(pos) < radius * radius) {
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
		const auto dist = pos.getDistance(getCenter());
		const auto v = 1.0f - dist / getSize().getX();//radius;
		return v * density;
	}

private:
	T density;
};

template<typename T>
class FillBrush final : public Brush < T >
{
public:
	FillBrush() :
		Brush(Math::Vector3d<T>(0, 0, 0)),
		fillValue(0)
	{}

	explicit FillBrush(const T fillValue) :
		Brush(Math::Vector3d<T>(0, 0, 0)),
		fillValue(fillValue)
	{}

	FillBrush(const Math::Vector3d<T>& pos, const T fillValue) :
		Brush(pos, Math::Vector3d<T>(1, 1, 1), fillValue)
	{}

	FillBrush(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& size, const T fillValue) :
		Brush(pos, size, fillValue)
	{}

	T getFillValue() const { return fillValue; }

	virtual void add(Math::Volume3d<float>& grid) const override {
		const T radius = getSize().getX() * 0.5;
		for (size_t x = 0; x < grid.getResolutions()[0]; ++x) {
			for (size_t y = 0; y < grid.getResolutions()[1]; ++y) {
				for (size_t z = 0; z < grid.getResolutions()[2]; ++z) {
					const auto& pos = grid.toCenterPosition(x, y, z);
					if (getCenter().getDistanceSquared(pos) < radius * radius) {
						grid.setValue(x, y, z, fillValue);
					}
					/*
					metaball.getSpace();
					const auto& pos = toCenterPosition(x, y, z);
					*/
				}
			}
		}
	}

private:
	T fillValue;
};

template<typename T>
using BrushSPtr = std::shared_ptr < Brush<T> > ;

template<typename T>
using BrushSPtrVector = std::vector < BrushSPtr<T> > ;

	}
}

#endif