#ifndef __CRYSTAL_SHADER_RENDERER_BASE_H__
#define __CRYSTAL_SHADER_RENDERER_BASE_H__

#include "../Util/UnCopyable.h"

#include "../Graphics/Camera.h"
#include "../Math/Particle.h"

namespace Crystal {
	namespace Shader {

class RendererBase : private UnCopyable
{
public:
	RendererBase() = default;

	virtual ~RendererBase(){};

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera) = 0;

	virtual void add(const Math::Particle3d<float>& particle) = 0;
};

class NullRenderer : public RendererBase
{
public:
	NullRenderer() = default;

	~NullRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera) override {};

	virtual void add(const Math::Particle3d<float>& particle) override{};
};
	}
}

#endif