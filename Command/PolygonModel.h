#ifndef __CRYSTAL_COMMAND_POLYGON_MODEL_H__
#define __CRYSTAL_COMMAND_POLYGON_MODEL_H__

#include "../Graphics/Polygon.h"

#include "../Math/Volume.h"
#include "../Math/BitSpace.h"

#include "../Math/MarchingCube.h"

#include "../Util/UnCopyable.h"

#include <memory>

#include "Object.h"
#include "Factory.h"

namespace Crystal {
	namespace Command {

template<typename T>
class PolygonObject : public Object
 {
public:
	PolygonObject(const Graphics::PolygonSPtr<T>& polygon, const unsigned int id) :
		Object(id),
		polygon( polygon )
	{}

	Type getType() const { return Type::Polygon; }

	virtual void move(const Math::Vector3d<float>& vector) override
	{
		polygon->move(vector);
	};


	Graphics::PolygonSPtr<T> getPolygon() const { return polygon; }

private:
	Graphics::PolygonSPtr<T> polygon;
};

template<typename T>
using PolygonObjectSPtr = std::shared_ptr < PolygonObject<T> > ;

template<typename T>
using PolygonObjectSPtrList = std::list < PolygonObjectSPtr<T> > ;

template<typename T>
class PolygonModel final : public ModelBase
{
public:
	PolygonModel()
	{
		mc.buildTable();
	}

	~PolygonModel() = default;

	PolygonModel& clear() {
		ModelBase::clear();
		this->polygons.clear();
		return (*this);
	}

	PolygonObjectSPtr<T> create(const Math::Volume3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue() );
		}
		return add(polygon);
	}

	PolygonObjectSPtr<T> create(const Math::BitSpace3d<float>& bs) {
		const auto& triangles = mc.march(bs);

		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return add(polygon);
	}

	PolygonObjectSPtr<T> createBoundingBox(const Math::Volume3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		Math::Box<T> bb(ss.getStart(), ss.getEnd());
		polygon->add(bb, Graphics::ColorRGBA<float>::Black());
		return add(polygon);
	}

	PolygonObjectSPtr<T> createGridCells(const Math::Volume3d<T>& ss) {
		Graphics::PolygonSPtr<T> polygon = std::make_shared<Graphics::Polygon<T> >();
		const auto& cells = ss.toCells();
		for (const auto& c : cells) {
			const auto& space = c.getSpace();
			Math::Box<T> bb(space.getStart(), space.getEnd());
			polygon->add(bb, Graphics::ColorRGBA<float>::Black());
			//polygon->add( )
		}
		return add(polygon);
	}


	PolygonObjectSPtr<T> find(const unsigned int id) {
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

	PolygonObjectSPtrList<T> getPolygons() const { return polygons; }

private:
	PolygonObjectSPtrList<T> polygons;

	Math::MarchingCube<T> mc;

	PolygonObjectSPtr<T> add(Graphics::PolygonSPtr<float>& p) {
		this->polygons.push_back( std::make_shared< PolygonObject<float> >( p, getNextId() ) );
		return polygons.back();
	}

};

template<typename T>
using PolygonModelSPtr = std::shared_ptr< PolygonModel<T> > ;

	}
}

#endif