#ifndef __CRYSTAL_SHADER_SPACE_2D_RENDERER_H__
#define __CRYSTAL_SHADER_SPACE_2D_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

//#include "../Math/Space2d.h"

namespace Crystal {
	namespace Shader {

class Space2dRenderer {
public:

	Space2dRenderer();

	~Space2dRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions);// , , const Math::Space2d& space);

private:
	Graphics::ShaderObject shader;

};

	}
}

#endif