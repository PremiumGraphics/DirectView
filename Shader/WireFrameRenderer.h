#ifndef __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Camera.h"

#include "RendererBase.h"

namespace Crystal {
	namespace Shader {

class WireFrameRenderer : public RendererBase {
public:

	WireFrameRenderer()
	{};

	virtual ~WireFrameRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList<float>& list);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint color;
	};

	Location getLocations();

	Graphics::ShaderObject shader;
};

class SurfaceRenderer : public RendererBase {
public:
	SurfaceRenderer()
	{};

	virtual ~SurfaceRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList<float>& list);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint color;
	};

	Location getLocations();

	Graphics::ShaderObject shader;
};

	}
}

#endif