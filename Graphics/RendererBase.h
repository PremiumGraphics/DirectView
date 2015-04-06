#ifndef __CRYSTAL_GRAPHICS_RENDERER_BASE_H__
#define __CRYSTAL_GRAPHICS_RENDERER_BASE_H__

#include "Camera.h"
#include "DisplayList.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace Graphics {

class RendererBase {
public:

	RendererBase(){};

	virtual ~RendererBase(){};

	virtual void render(const int width, const int height, const Camera<float>& camera, const DisplayList& list) = 0;

};
	}
}

#endif