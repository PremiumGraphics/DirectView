#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "../Graphics/Buffer.h"
#include "../Graphics/Camera.h"
#include "ShaderObject.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class PointRenderer final : private UnCopyable
{
public:

	PointRenderer() = default;

	~PointRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::PointBuffer<float>& buffer, const bool isSelected);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
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