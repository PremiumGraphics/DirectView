#ifndef __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_SHADER_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Polygon.h"

namespace Crystal {
	namespace Shader {

class WireFrameRenderer {
public:

	WireFrameRenderer()
	{};

	~WireFrameRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera );

	void build();

	std::vector< float > positions;
	std::vector< float > colors;

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

class SurfaceRenderer {
public:
	SurfaceRenderer()
	{};

	virtual ~SurfaceRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera );

	void build();

	std::vector< float > positions;
	std::vector< float > colors;


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