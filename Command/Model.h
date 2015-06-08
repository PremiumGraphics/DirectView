#ifndef __CRYSTAL_COMMAND_MODEL_H__
#define __CRYSTAL_COMMAND_MODEL_H__

#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Math/BitSpace.h"
#include "../Math/ScalarSpace.h"
#include "../Math/MarchingCube.h"

#include "BitSpaceFactory.h"
#include "ScalarSpaceFactory.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {


class Model {
public:
	Model() :
		lightBuilder( std::make_shared< Graphics::LightBuilder>()),
		camera( std::make_shared< Graphics::Camera<float> >() )
	{
		mc.buildTable();
	}

	void clear()
	{
		bsFactory.clear();
		ssFactory.clear();
		polygons.clear();
	}


	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

	void toPolygon() {
		polygons.clear();

		for (const auto& ss : ssFactory.getScalarSpaces() ) {
			const auto triangles = mc.march(*ss, 0.5);

			Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
			for (const auto t : triangles) {
				//p.add(t, Graphics::ColorRGBA<float>::Blue() );
				polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
			}
			polygons.push_back(polygon);
		}

		for (const auto& bs : bsFactory.getBitSpaces() ) {
			const auto& triangles = mc.march(*bs);

			Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
			for (const auto t : triangles) {
				//p.add(t, Graphics::ColorRGBA<float>::Blue() );
				polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
			}
			polygons.push_back(polygon);
		}
	}

	BitSpaceFactory* getBitSpaceFactory() { return &bsFactory; }

	ScalarSpaceFactory* getScalarSpaceFactory() { return &ssFactory; }

	Graphics::PolygonSPtrList getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrList polygons;
	Math::MarchingCube<float> mc;

	Graphics::CameraSPtr<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;
	BitSpaceFactory bsFactory;
	ScalarSpaceFactory ssFactory;
private:
};


using ModelSPtr = std::shared_ptr < Model > ;
	}
}

#endif