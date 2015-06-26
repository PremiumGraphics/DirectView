#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Buffer.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class WireframeRenderer final : private UnCopyable
{
public:

	WireframeRenderer() = default;

	~WireframeRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::LineBuffer<float>& buffer, const bool isSelected);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
		GLuint isSelected;
	};

	Location getLocations();

	void up();

	void down();

	Graphics::ShaderObject shader;
};

	}
}

#endif