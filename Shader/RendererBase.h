#ifndef __CRYSTAL_SHADER_RENDERER_BASE_H__
#define __CRYSTAL_SHADER_RENDERER_BASE_H__

#include "../Util/UnCopyable.h"

#include "../Graphics/Camera.h"
#include "../Math/Particle.h"
#include "../Math/Volume.h"

#include <memory>
#include <list>
#include <vector>

namespace Crystal {
	namespace Shader {

class RendererBase : private UnCopyable
{
public:
	RendererBase() = default;

	virtual ~RendererBase(){};

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera) = 0;

	virtual void add(const Math::Particle3d<float>& particle) = 0;

	virtual void add(const Math::Volume3d<float>& volume) = 0;

	virtual void add(const Graphics::Surface<float>& surface) = 0;
};

using RendererBaseSPtr = std::shared_ptr < RendererBase > ;
using RendererBaseSPtrVector = std::vector < RendererBaseSPtr > ;
using RendererBaseSPtrList = std::list < RendererBaseSPtr > ;

class NullRenderer : public RendererBase
{
public:
	NullRenderer() = default;

	~NullRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera) override {};

	void add(const Math::Particle3d<float>& particle) override{};

	void add(const Math::Volume3d<float>& volume) override{};

	void add(const Graphics::Surface<float>& surface) override{};

};
	}
}

#endif