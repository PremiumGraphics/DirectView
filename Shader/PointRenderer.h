#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "../Util/UnCopyable.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "ShaderObject.h"

namespace Crystal {
	namespace Shader {

class PointRenderer final : private UnCopyable
{
public:

	PointRenderer() = default;

	~PointRenderer() = default;

	void add(const Graphics::Surface<float>& surface);

	void clear();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const bool isSelected);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint isSelected;
	};

	Location getLocations();

	void add(const Math::Vector3d<float>& position);

	std::vector<float> positions;

	ShaderObject shader;
};

	}
}

#endif