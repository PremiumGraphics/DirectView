#ifndef __CRYSTAL_SHADER_ID_RENDERER_H__
#define __CRYSTAL_SHADER_ID_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/Camera.h"

namespace Crystal {
	namespace Shader {

class IDRenderer {
public:

	IDRenderer();

	~IDRenderer();

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	void build();

	std::vector<float> positions;
	std::vector<int> types;
	std::vector<int> ids;

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint type;
		GLuint id;
	};

	Location getLocations();


	Graphics::ShaderObject shader;
};

	}
}

#endif