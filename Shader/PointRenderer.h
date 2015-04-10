#ifndef __CRYSTAL_GRAPHICS_POINT_RENDERER_H__
#define __CRYSTAL_GRAPHICS_POINT_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/DisplayList.h"

namespace Crystal {
	namespace Shader {

class PointRenderer {
public:

	PointRenderer();

	~PointRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera, const Graphics::DisplayList& list);

private:
	Graphics::ShaderObject shader;
};

	}
}

#endif