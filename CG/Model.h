#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

#include "../Math/BitSpace.h"
#include "../Math/ScalarSpace.h"
#include "../Math/MarchingCube.h"

#include "SpaceFactory.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace CGS {


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
		factory.clear();
		polygons.clear();
	}


	Graphics::LightBuilderSPtr getLightBuilder() const { return lightBuilder; }

	Graphics::CameraSPtr<float> getCamera() { return camera; }

	Graphics::LightSPtrList getLights() { return lightBuilder->getLights(); }

	void toPolygon() {
		polygons.clear();
		gridCenters.clear();

		for (const auto& ss : factory.getScalarSpaces() ) {
			const auto triangles = mc.march(*ss, 0.5);

			Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
			for (const auto t : triangles) {
				//p.add(t, Graphics::ColorRGBA<float>::Blue() );
				polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
			}
			polygons.push_back(polygon);

			gridCenters.push_back(ss->getCenter());
		}

		for (const auto& bs : factory.getBitSpaces() ) {
			const auto& triangles = mc.march(*bs);

			Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
			for (const auto t : triangles) {
				//p.add(t, Graphics::ColorRGBA<float>::Blue() );
				polygon->add(t.getv0(), t.getv1(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv1(), t.getv2(), Graphics::ColorRGBA<float>::Blue());
				polygon->add(t.getv2(), t.getv0(), Graphics::ColorRGBA<float>::Blue());
			}
			polygons.push_back(polygon);

			gridCenters.push_back(bs->getCenter());
		}
	}

	SpaceFactory* getSpaceFactory() { return &factory; }

	Graphics::PolygonSPtrVector getPolygons() const { return polygons; }

private:
	Graphics::PolygonSPtrVector polygons;
	std::vector< Math::Vector3d<float > > gridCenters;
	Math::MarchingCube<float> mc;

	Graphics::CameraSPtr<float> camera;
	Graphics::LightBuilderSPtr lightBuilder;
	SpaceFactory factory;

private:
};


using ModelSPtr = std::shared_ptr < Model > ;
	}
}

#endif