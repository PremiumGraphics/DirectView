#ifndef __CRYSTAL_MODEL_SURFACE_CONSTRUCT_COMMAND__
#define __CRYSTAL_MODEL_SURFACE_CONSTRUCT_COMMAND__

#include "../Math/Volume.h"
#include "../Math/BitSpace.h"
#include "../Math/MarchingCube.h"

#include "../Graphics/Surface.h"

namespace Crystal {
	namespace Model {

template<typename T>
class SurfaceConstructCommand final : private UnCopyable
{
public:
	SurfaceConstructCommand()
	{
		mc.buildTable();
	}

	~SurfaceConstructCommand() = default;

	Graphics::SurfaceSPtr<T> create(const Math::Volume3d<float>& ss)
	{
		const auto triangles = mc.march(ss, 0.5);

		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		surfaces.push_back(polygon);
		return surfaces.back();
	}

	Graphics::SurfaceSPtrList<T> getSurfaces() { return surfaces; }

	void clear() { surfaces.clear(); }

	/*
	Graphics::SurfaceSPtr<T> create(const Math::BitSpace3d<float>& bs) {
	const auto& triangles = mc.march(bs);

	Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<T> >();
	for (const auto t : triangles) {
	polygon->add(t, Graphics::ColorRGBA<float>::Blue());
	}
	surfaces.push_back(polygon);
	return surfaces.back();
	}
	*/

private:
	Math::MarchingCube<T> mc;
	Graphics::SurfaceSPtrList<T> surfaces;
};
	}
}

#endif