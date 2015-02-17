#ifndef __CRYSTAL_APP_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_APP_WIRE_FRAME_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"

namespace Crystal {
	namespace Math {
		class Vector3d;
	}
	namespace CG {

class WireFrameRenderer {
public:

	WireFrameRenderer();

	~WireFrameRenderer();

	struct Param {
		std::vector<float> positions;
		std::vector<float> projectionMatrix;
		std::vector<float> modelviewMatrix;
	};


	void render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices );

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