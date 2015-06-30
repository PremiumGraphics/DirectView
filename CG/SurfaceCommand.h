#ifndef __CRYSTAL_UI_SURFACE_COMMAND_H__
#define __CRYSTAL_UI_SURFACE_COOMAND_H__

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
		preSurfaces.clear();
	}


	Graphics::SurfaceSPtr<float> create(const Math::Volume3d<float>& ss, const float threshold);

	Graphics::SurfaceSPtrList<float> getSurfaces() const { return preSurfaces; }

private:
	Graphics::SurfaceSPtrList<float> preSurfaces;

	Math::MarchingCube<float> mc;

};
	}
}

#endif