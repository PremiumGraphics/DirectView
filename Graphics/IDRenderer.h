#ifndef __CRYSTAL_GRAPHICS_ID_RENDERER_H__
#define __CRYSTAL_GRAPHICS_ID_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Camera.h"

#include "RendererBase.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace Graphics {

class IDRenderer : public RendererBase {
public:

	IDRenderer();

	virtual ~IDRenderer();

	virtual void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList& list);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
		GLuint faceId;
		GLuint polygonId;
	};

	Location getLocations();


	Graphics::ShaderObject shader;
};

	}
}

#endif