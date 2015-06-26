#ifndef __CRYSTAL_SHADER_NORMAL_RENDERER_H__
#define __CRYSTAL_SHADER_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Buffer.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Surface.h"

#include <memory>

namespace Crystal {
	namespace Shader {

class NormalRenderer {
public:

	NormalRenderer();

	~NormalRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::PointBuffer<float>& buffer);

	float scale;

private:
	std::vector< float > positions;
	std::vector< float > normals;


private:
	ShaderObject shader;

};

	}
}

#endif