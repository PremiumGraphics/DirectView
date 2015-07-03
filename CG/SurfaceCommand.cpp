#include "stdafx.h"
#include "SurfaceCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

SurfaceSPtr<float> SurfaceCommand::create(const Volume3d<float>& ss, const float threshold)
{
	const auto& triangles = mc.march(ss, threshold);//vConfig.threshold);

	Graphics::SurfaceSPtr<float> surface = std::make_shared<Graphics::Surface<float> >();
	for (const auto& t : triangles) {
		surface->add(t, Graphics::ColorRGBA<float>::Blue());
	}
	surfaces.push_back(surface);
	return surface;
}
