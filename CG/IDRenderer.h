#ifndef __CRYSTAL_APP_ID_RENDERER_H__
#define __CRYSTAL_APP_ID_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"
#include "../Graphics/Polygon.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class IDRenderer {
public:

	IDRenderer();

	~IDRenderer();

	struct Param {
		std::vector<float> positions;
		std::vector<float> positionIds;
		std::vector<float> projectionMatrix;
		std::vector<float> modelviewMatrix;
	};

	void render(const int width, const int height, const Param& param, const Graphics::FaceVector& faces);

	void build();

private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
	};

	Location getLocations();


	Graphics::ShaderObject shader;
};

	}
}

#endif