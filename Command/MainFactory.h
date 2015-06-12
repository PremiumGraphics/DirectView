#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"

#include "BitSpaceFactory.h"
#include "ScalarSpaceFactory.h"
#include "PolygonFactory.h"
#include "LightFactory.h"
#include "MetaballFactory.h"
#include "DrawableFactory.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {


class MainFactory {
public:
	MainFactory() :
		lightFactory(std::make_shared< LightFactory >()),
		camera(std::make_shared< Graphics::Camera<float> >()),
		bsFactory(std::make_shared< BitSpaceFactory >()),
		ssFactory(std::make_shared< ScalarSpaceFactory >()),
		polygonFactory(std::make_shared< PolygonFactory<float> >()),
		metaballFactory(std::make_shared< MetaballFactory<float> >()),
		drawableFactory(std::make_shared< DrawableFactory<float> >())
	{
	}

	void clear()
	{
		bsFactory->clear();
		ssFactory->clear();
		polygonFactory->clear();
		metaballFactory->clear();
		drawableFactory->clear();
	}

	void add(const MetaballId<float>& metaball)
	{
		auto ss = ssFactory->getScalarSpaces().front();
		ss.getScalarSpace()->add(*metaball.getMetaball());
		polygonFactory->create(*ss.getScalarSpace());
	}

	void add(const GridConfig& config)
	{
		const auto ss = getScalarSpaceFactory()->create(config);
		getPolygonFactory()->create(*(ss.getScalarSpace()));
		getDrawableFactory()->createBoundingBox(*ss.getScalarSpace());
		getDrawableFactory()->createGridCells(*ss.getScalarSpace());
	}


	Graphics::CameraSPtr<float> getCamera() const { return camera; }

	LightFactorySPtr getLightFactory() const { return lightFactory; }

	BitSpaceFactorySPtr getBitSpaceFactory() const { return bsFactory; }

	ScalarSpaceFactorySPtr getScalarSpaceFactory() const { return ssFactory; }

	PolygonFactorySPtr<float> getPolygonFactory() const { return polygonFactory; }

	//PolygonFactorySPtr<float> getDrawableFactory() const { return supportFactory; }

	MetaballFactorySPtr getMetaballFactory() const { return metaballFactory; }

	DrawableFactorySPtr<float> getDrawableFactory() const { return drawableFactory; }

private:
	Graphics::CameraSPtr<float> camera;
	LightFactorySPtr lightFactory;
	BitSpaceFactorySPtr bsFactory;
	ScalarSpaceFactorySPtr ssFactory;
	PolygonFactorySPtr<float> polygonFactory;
	MetaballFactorySPtr metaballFactory;
	DrawableFactorySPtr<float> drawableFactory;
};


using MainFactorySPtr = std::shared_ptr < MainFactory > ;
	}
}

#endif