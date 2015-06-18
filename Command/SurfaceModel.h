#ifndef __CRYSTAL_COMMAND_SURFACE_MODEL_H__
#define __CRYSTAL_COMMAND_SURFACE_MODEL_H__

#include "../Graphics/Surface.h"

#include "../Math/Volume.h"
#include "../Math/BitSpace.h"

#include "../Math/MarchingCube.h"

#include <memory>

#include "Object.h"

namespace Crystal {
	namespace Model {

template<typename T>
class SurfaceObject : public Object
 {
public:
	SurfaceObject(const Graphics::SurfaceSPtr<T>& polygon, const unsigned int id) :
		Object(id),
		polygon( polygon )
	{}

	Type getType() const { return Type::Polygon; }

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		polygon->move(vector);
	};


	Graphics::SurfaceSPtr<T> getPolygon() const { return polygon; }

private:
	Graphics::SurfaceSPtr<T> polygon;
};

template<typename T>
using SurfaceObjectSPtr = std::shared_ptr < SurfaceObject<T> > ;

template<typename T>
using SurfaceObjectSPtrList = std::list < SurfaceObjectSPtr<T> > ;

template<typename T>
class SurfaceModel final : public ModelBase
{
public:
	SurfaceModel()
	{
		mc.buildTable();
	}

	~SurfaceModel() = default;

	void clear() {
		ModelBase::clear();
		this->polygons.clear();
	}

	SurfaceObjectSPtr<T> create(const Math::Volume3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue() );
		}
		return add(polygon);
	}

	SurfaceObjectSPtr<T> create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<T> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return add(polygon);
	}

	SurfaceObjectSPtr<T> createBoundingBox(const Math::Volume3d<T>& ss) {
		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<T> >();
		Math::Box<T> bb(ss.getStart(), ss.getEnd());
		polygon->add(bb, Graphics::ColorRGBA<float>::Black());
		return add(polygon);
	}

	SurfaceObjectSPtr<T> createGridCells(const Math::Volume3d<T>& ss) {
		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<T> >();
		const auto& cells = ss.toCells();
		for (const auto& c : cells) {
			const auto& space = c.getSpace();
			Math::Box<T> bb(space.getStart(), space.getEnd());
			polygon->add(bb, Graphics::ColorRGBA<float>::Black());
			//polygon->add( )
		}
		return add(polygon);
	}


	SurfaceObjectSPtr<T> find(const unsigned int id) {
		for (const auto& p : polygons) {
			if (p->getId() == id) {
				return p;
			}
		}
		return nullptr;
	}

	void remove(const unsigned int id) override {
		const auto& p = find(id);
		if (p == nullptr) {
			return;
		}
		polygons.remove(p);
	}

	void move(const Math::Vector3d<T>& vector) {
		for (const auto& s : polygons) {
			if (s->isSelected()) {
				s->move(vector);
			}
		}
	}


	SurfaceObjectSPtrList<T> getPolygons() const { return polygons; }

private:
	SurfaceObjectSPtrList<T> polygons;

	Math::MarchingCube<T> mc;

	SurfaceObjectSPtr<T> add(Graphics::SurfaceSPtr<float>& p) {
		this->polygons.push_back( std::make_shared< SurfaceObject<float> >( p, getNextId() ) );
		return polygons.back();
	}

};

template<typename T>
using SurfaceModelSPtr = std::shared_ptr< SurfaceModel<T> > ;

	}
}

#endif