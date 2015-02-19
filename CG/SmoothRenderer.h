#ifndef __CRYSTAL_APP_POLYGON_RENDERER_H__
#define __CRYSTAL_APP_POLYGON_RENDERER_H__

#include <map>
#include <vector>

#include "../Math/Matrix4d.h"
#include "../Graphics/Light.h"
#include "../Graphics/ShaderObject.h"


namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class SmoothRenderer {
public:

	SmoothRenderer();

	~SmoothRenderer();

	void build();

	struct Param {
		std::vector<float> positions;
		std::vector<float> normals;
		std::vector<float> projectionMatrix;
		std::vector<float> modelviewMatrix;
		std::vector<float> eyePos;
		std::vector<Graphics::Light*> lights;
	};

	void render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices );

private:
	Graphics::ShaderObject shader;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint normal;
		GLuint diffuse;
		GLuint specular;
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