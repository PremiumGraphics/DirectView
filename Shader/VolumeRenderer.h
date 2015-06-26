#ifndef __CRYSTAL_SHADER_VOLUME_RENDERER_H__
#define __CRYSTAL_SHADER_VOLUME_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Buffer.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class VolumeRenderer final : private UnCopyable
{
public:

	VolumeRenderer() = default;

	~VolumeRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::VolumeBuffer<float>& buffer);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint density;
	};

	Location getLocations();

	Graphics::ShaderObject shader;
};

	}
}

#endif