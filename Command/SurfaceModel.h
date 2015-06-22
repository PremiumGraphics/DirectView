#ifndef __CRYSTAL_COMMAND_SURFACE_MODEL_H__
#define __CRYSTAL_COMMAND_SURFACE_MODEL_H__

#include "../Graphics/Surface.h"


#include <memory>

#include "Object.h"

namespace Crystal {
	namespace Model {

template<typename T>
class SurfaceObject : public Object
 {
public:
	SurfaceObject(const Graphics::SurfaceSPtr<T>& surface, const unsigned int id) :
		Object(id),
		surface( surface )
	{}

	Type getType() const { return Type::Polygon; }

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		surface->move(vector);
	};

	Graphics::SurfaceSPtr<T> getSurface() const { return surface; }

private:
	Graphics::SurfaceSPtr<T> surface;
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
	}

	~SurfaceModel() = default;

	void clear() {
		ModelBase::clear();
		this->surfaces.clear();
	}

	void add(const SurfaceObjectSPtrList<T>& objects) {
		this->surfaces.insert( this->surfaces.end(), objects.begin(), objects.end() );
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

	SurfaceObjectSPtrList<T> getSurfaces() const { return surfaces; }

	SurfaceObjectSPtr<T> add(const Graphics::SurfaceSPtr<float>& p) {
		this->surfaces.push_back(std::make_shared< SurfaceObject<float> >(p, getNextId()));
		return surfaces.back();
	}


private:
	SurfaceObjectSPtrList<T> surfaces;

};

template<typename T>
using SurfaceModelSPtr = std::shared_ptr< SurfaceModel<T> > ;

	}
}

#endif