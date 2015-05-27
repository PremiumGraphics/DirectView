#ifndef __CRYSTAL_GRAPHICS_NORMAL_RENDERER_H__
#define __CRYSTAL_GRAPHICS_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/DisplayList.h"

#include <memory>

namespace Crystal {
	namespace Graphics {

class NormalRenderer {
public:

	NormalRenderer();

	~NormalRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList<float>& list );

private:
	Graphics::ShaderObject shader;

};

	}
}

#endif