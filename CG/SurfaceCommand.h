#ifndef __CRYSTAL_COMMAND_SURFACE_COMMAND_H__
#define __CRYSTAL_COMMAND_SURFACE_COOMAND_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Surface.h"

namespace Crystal {
	namespace UI {

class SurfaceCommand {
public:
	SurfaceCommand() {
		mc.buildTable();
	}

	void clear() {
		surfaces.clear();
	}


	Graphics::SurfaceSPtr<float> create(const Math::Volume3d<float>& ss, const float threshold);

	Graphics::SurfaceSPtrList<float> getSurfaces() const { return surfaces; }

private:
	Graphics::SurfaceSPtrList<float> surfaces;

	Math::MarchingCube<float> mc;

};
	}
}

#endif