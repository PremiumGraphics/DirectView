#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Shader {

class PointRenderer {
public:

	PointRenderer();

	~PointRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera);

	std::vector<float> positions;

private:
	Graphics::ShaderObject shader;
};

	}
}

#endif