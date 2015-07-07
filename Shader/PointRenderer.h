#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "../Util/UnCopyable.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "ShaderObject.h"
#include "RendererBase.h"

namespace Crystal {
	namespace Shader {

class PointRenderer final : public RendererBase
{
public:

	PointRenderer() = default;

	~PointRenderer() = default;

	void add(const Math::Particle3d<float>& particle) override;

	void add(const Graphics::Surface<float>& surface) override;

	void add(const Math::Vector3d<float>& position);

	void add(const Math::Volume3d<float>& volume) override{};

	void clear();

	void render(const int width, const int height, const Graphics::Camera<float>& camera) override;

	void build() override;

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
	};

	Location getLocations();


	std::vector<float> positions;

	ShaderObject shader;
};

	}
}

#endif