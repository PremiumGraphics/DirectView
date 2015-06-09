#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Math/ScalarSpace.h"
#include "../Math/MarchingCube.h"

#include "BitSpaceFactory.h"
#include "ScalarSpaceFactory.h"
#include "PolygonFactory.h"
#include "LightFactory.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {


class Model {
public:
	Model() :
		lightBuilder( std::make_shared< LightFactory >()),
		camera( std::make_shared< Graphics::Camera<float> >() ),
		bsFactory(std::make_shared< BitSpaceFactory >() ),
		ssFactory(std::make_shared< ScalarSpaceFactory >() )
	{
	}

	void clear()
	{
		bsFactory->clear();
		ssFactory->clear();
		polygonFactory.clear();
	}


	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

	BitSpaceFactorySPtr getBitSpaceFactory() const { return bsFactory; }

	ScalarSpaceFactorySPtr getScalarSpaceFactory() { return ssFactory; }

	PolygonFactory* getPolygonFactory() { return &polygonFactory; }

private:
	Graphics::CameraSPtr<float> camera;
	LightFactorySPtr lightBuilder;
	BitSpaceFactorySPtr bsFactory;
	ScalarSpaceFactorySPtr ssFactory;
	PolygonFactory polygonFactory;
private:
};


using ModelSPtr = std::shared_ptr < Model > ;
	}
}

#endif