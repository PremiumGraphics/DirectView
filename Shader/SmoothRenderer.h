#ifndef __CRYSTAL_GRAPHICS_POLYGON_RENDERER_H__
#define __CRYSTAL_GRAPHICS_POLYGON_RENDERER_H__

#include <map>
#include <vector>

#include "../Math/Matrix4d.h"
#include "../Graphics/Light.h"
#include "../Graphics/ShaderObject.h"
#include "../Graphics/Camera.h"
#include "../Graphics/DisplayList.h"
#include "../Graphics/Material.h"

namespace Crystal {
	namespace Graphics {

class SmoothRenderer {
public:

	SmoothRenderer();

	~SmoothRenderer();

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

	void render(const int width, const int height, const Camera<float>& camera, const DisplayList& list, const LightSPtrList& lights, const std::list<Material*>& materials );

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
		GLuint lightSize;
	};

	Location getLocations();
};

	}
}

#endif