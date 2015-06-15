#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"

#include "ScalarSpaceFactory.h"
#include "PolygonFactory.h"
#include "LightFactory.h"
#include "MetaballFactory.h"
#include "DrawableFactory.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {

template<typename T>
class MainFactory {
public:
	MainFactory() :
		lightFactory(std::make_shared< LightFactory<T> >()),
		camera(std::make_shared< Graphics::Camera<T> >()),
		ssFactory(std::make_shared< ScalarSpaceFactory<T> >()),
		polygonFactory(std::make_shared< PolygonFactory<T> >()),
		metaballFactory(std::make_shared< MetaballFactory<T> >()),
		drawableFactory(std::make_shared< DrawableFactory<T> >())
	{
	}

	void clear()
	{
		ssFactory->clear();
		polygonFactory->clear();
		metaballFactory->clear();
		drawableFactory->clear();
	}

	void add(const MetaballId<T>& metaball)
	{
		auto ss = ssFactory->getSpaces().front();
		ss.getScalarSpace()->add(*metaball.getMetaball());
	}

	void add(const GridConfig<T>& config)
	{
		const auto ss = getScalarSpaceFactory()->create(config);
		getPolygonFactory()->create(*(ss.getScalarSpace()));
		getDrawableFactory()->createBoundingBox(*ss.getScalarSpace());
		getDrawableFactory()->createGridCells(*ss.getScalarSpace());
	}

	void polygonize()
	{
		for (const auto& s : getScalarSpaceFactory()->getSpaces()) {
			getPolygonFactory()->create(*s.getScalarSpace());
		}
	}

	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	LightFactorySPtr<T> getLightFactory() const { return lightFactory; }

	ScalarSpaceFactorySPtr<T> getScalarSpaceFactory() const { return ssFactory; }

	PolygonFactorySPtr<T> getPolygonFactory() const { return polygonFactory; }

	//PolygonFactorySPtr<float> getDrawableFactory() const { return supportFactory; }

	MetaballFactorySPtr<T> getMetaballFactory() const { return metaballFactory; }

	DrawableFactorySPtr<T> getDrawableFactory() const { return drawableFactory; }

private:
	Graphics::CameraSPtr<T> camera;
	LightFactorySPtr<T> lightFactory;
	ScalarSpaceFactorySPtr<T> ssFactory;
	PolygonFactorySPtr<T> polygonFactory;
	MetaballFactorySPtr<T> metaballFactory;
	DrawableFactorySPtr<T> drawableFactory;
};

template<typename T>
using MainFactorySPtr = std::shared_ptr < MainFactory<T> > ;
	}
}

#endif