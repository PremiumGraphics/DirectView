#ifndef __CRYSTAL_GRAPHICS_SCENE_H__
#define __CRYSTAL_GRAPHICS_SCENE_H__

#include "Polygon.h"
#include "Camera.h"

namespace Crystal {
	namespace Graphics {

class Scene
{
public:
	Scene() :
		parent(nullptr),
		child(nullptr)
	{}

	void addPolygon(const PolygonSPtr& polygon) { polygons.push_back(polygon); }

	PolygonSPtrList getPolygons() const { return polygons; }

	//void addCamera(const Camera<float>& camera) {}

	void setParent(Scene* parent) { this->parent = parent;  }

	void setChild(Scene* child) { this->child = child; }

	Scene* getParent() const { return parent; }

	Scene* getChild() const { return child; }

private:
	PolygonSPtrList polygons;
	Scene* parent;
	Scene* child;
};

	}
}

#endif