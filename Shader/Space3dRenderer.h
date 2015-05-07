#ifndef __CRYSTAL_SHADER_SPACE_3D_RENDERER_H__
#define __CRYSTAL_SHADER_SPACE_3D_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Space3d.h"

namespace Crystal {
	namespace Shader {

class Space3dRenderer {
public:

	Space3dRenderer();

	~Space3dRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions, const Math::Space3d& space);

private:
	Graphics::ShaderObject shader;

};

	}
}

#endif