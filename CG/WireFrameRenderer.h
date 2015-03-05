#ifndef __CRYSTAL_APP_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_APP_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class WireFrameRenderer {
public:

	WireFrameRenderer();

	~WireFrameRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList& list);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
	};

	Location getLocations();


	Graphics::ShaderObject shader;
};

	}
}

#endif