#ifndef __CRYSTAL_GRAPHICS_SMOOTH_RENDERER_H__
#define __CRYSTAL_GRAPHICS_SMOOTH_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"
#include "../Math/Matrix.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Material.h"
#include "../Graphics/Buffer.h"

namespace Crystal {
	namespace Graphics {

class SmoothRenderer final {
public:

	SmoothRenderer() = default;

	~SmoothRenderer() = default;

	void build();

	/*
	struct Param {
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> projectionMatrix;
		std::vector<float> modelviewMatrix;
		std::vector<float> eyePos;
		std::list<Graphics::Light*> lights;
		std::vector<float> matAmbient;
		std::vector<float> matSpecular;
		std::vector<float> matDiffuse;
		float shininess;
	};
	*/

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::TriangleBuffer<float>& buffer);

private:
	Graphics::ShaderObject shader;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint normal;
		GLuint eyePos;
		GLuint matAmbient;
		GLuint matSpecular;
		GLuint matDiffuse;
		GLuint shininess;
	};

	Location getLocations();
};


	}
}

#endif