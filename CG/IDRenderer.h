#ifndef __CRYSTAL_APP_ID_RENDERER_H__
#define __CRYSTAL_APP_ID_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class IDRenderer {
public:

	IDRenderer();

	~IDRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList& list);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
		GLuint faceId;
	};

	Location getLocations();


	Graphics::ShaderObject shader;
};

	}
}

#endif