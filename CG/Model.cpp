#include "stdafx.h"

#include "../Graphics/Vertex.h"
#include "Model.h"

using namespace Crystal::Graphics;
using namespace Crystal::CG;

void Model::toPolygon()
{
	polygons.clear();
	gridCenters.clear();

	for (const auto ss : scalarSpaces) {
		const auto triangles = mc.march(*ss, 0.5);

		Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
		for (const auto t : triangles) {
			//p.add(t, Graphics::ColorRGBA<float>::Blue() );
			polygon->add(t.getv0(), t.getv1(), ColorRGBA<float>::Blue());
			polygon->add(t.getv1(), t.getv2(), ColorRGBA<float>::Blue());
			polygon->add(t.getv2(), t.getv0(), ColorRGBA<float>::Blue());
		}
		polygons.push_back(polygon);

		gridCenters.push_back(ss->getCenter());
	}

	for (const auto& bs : bitSpaces) {
		const auto& triangles = mc.march(*bs);

		Graphics::PolygonSPtr polygon = std::make_shared<Graphics::Polygon>();
		for (const auto t : triangles) {
			//p.add(t, Graphics::ColorRGBA<float>::Blue() );
			polygon->add(t.getv0(), t.getv1(), ColorRGBA<float>::Blue());
			polygon->add(t.getv1(), t.getv2(), ColorRGBA<float>::Blue());
			polygon->add(t.getv2(), t.getv0(), ColorRGBA<float>::Blue());
		}
		polygons.push_back(polygon);

		gridCenters.push_back(bs->getCenter());
	}

}