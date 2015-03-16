#ifndef __CRYSTAL_GRAPHICS_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_GRAPHICS_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Camera.h"

#include "RendererBase.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace Graphics {

class WireFrameRenderer : public RendererBase {
public:

	WireFrameRenderer() :
		lineWidth( 1.0 )
	{};

	virtual ~WireFrameRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList& list);

	void build();

	float getLineWidth() const { return lineWidth; }

	void setLineWidth(const float width) { this->lineWidth = width; }

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint color;
	};

	Location getLocations();

	float lineWidth;

	Graphics::ShaderObject shader;
};

	}
}

#endif