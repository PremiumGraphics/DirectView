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
		polygon( polygon ),
		instantiated( false )
	{}

	Type getType() const { return Type::Polygon; }

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		polygon->move(vector);
	};

	void instanciate() { instantiated = true; }

	bool isInstance() const { return instantiated; }

	Graphics::SurfaceSPtr<T> getPolygon() const { return polygon; }

private:
	Graphics::SurfaceSPtr<T> polygon;
	bool instantiated;
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
		this->surfaces.clear();
	}

	void add(const SurfaceObjectSPtrList<T>& objects) {
		this->surfaces.insert( this->surfaces.end(), objects.begin(), objects.end() );
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
		for (const auto& p : surfaces) {
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
		surfaces.remove(p);
	}

	void move(const Math::Vector3d<T>& vector) {
		for (const auto& s : surfaces) {
			if (s->isSelected()) {
				s->move(vector);
			}
		}
	}

	void deleteSelected() {
		for (auto iter = surfaces.begin(); iter != surfaces.end();) {
			const auto ball = (*iter);
			if (ball->isSelected()) {
				iter = surfaces.erase(iter);
				continue;
			}
			++iter;
		}
	}

	void instanciate() {
		for (const auto& s : surfaces) {
			s->instanciate();
		}
	}

	SurfaceObjectSPtrList<T> getUnInstances() const {
		SurfaceObjectSPtrList<T> uninstances;
		for (const auto& s : surfaces) {
			if (!s->isInstance()) {
				uninstances.push_back(s);
			}
		}
		return uninstances;
	}


	SurfaceObjectSPtrList<T> getInstances() const {
		SurfaceObjectSPtrList<T> instances;
		for (const auto& s : surfaces) {
			if (s->isInstance()) {
				instances.push_back(s);
			}
		}
		return instances;
	}

	SurfaceObjectSPtrList<T> getSurfaces() const { return surfaces; }

private:
	SurfaceObjectSPtrList<T> surfaces;

	Math::MarchingCube<T> mc;

	SurfaceObjectSPtr<T> add(Graphics::SurfaceSPtr<float>& p) {
		this->surfaces.push_back( std::make_shared< SurfaceObject<float> >( p, getNextId() ) );
		return surfaces.back();
	}

};

template<typename T>
using SurfaceModelSPtr = std::shared_ptr< SurfaceModel<T> > ;

	}
}

#endif