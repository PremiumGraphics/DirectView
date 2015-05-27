#ifndef __CRYSTAL_SHADER_RENDERER_BASE_H__
#define __CRYSTAL_SHADER_RENDERER_BASE_H__

#include "../Graphics/Camera.h"
#include "../Graphics/DisplayList.h"

namespace Crystal {
	namespace Shader {

class RendererBase {
public:

	RendererBase(){};

	virtual ~RendererBase(){};

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList<float>& list) = 0;

};
	}
}

#endif