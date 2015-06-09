#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"

#include "BitSpaceFactory.h"
#include "ScalarSpaceFactory.h"
#include "PolygonFactory.h"
#include "LightFactory.h"

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
		polygonFactory(std::make_shared< PolygonFactory >())
	{
	}

	void clear()
	{
		bsFactory->clear();
		ssFactory->clear();
		polygonFactory->clear();
	}


	Graphics::CameraSPtr<float> getCamera() const { return camera; }

	LightFactorySPtr getLightFactory() const { return lightFactory; }

	BitSpaceFactorySPtr getBitSpaceFactory() const { return bsFactory; }

	ScalarSpaceFactorySPtr getScalarSpaceFactory() const { return ssFactory; }

	PolygonFactorySPtr getPolygonFactory() const { return polygonFactory; }

private:
	Graphics::CameraSPtr<float> camera;
	LightFactorySPtr lightFactory;
	BitSpaceFactorySPtr bsFactory;
	ScalarSpaceFactorySPtr ssFactory;
	PolygonFactorySPtr polygonFactory;
private:
};


using ModelSPtr = std::shared_ptr < MainFactory > ;
	}
}

#endif