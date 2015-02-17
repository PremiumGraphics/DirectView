#ifndef __CRYSTAL_DIRECT_VIEW_WIRE_FRAME_RENDERER_H__
#define __CRYSTAL_DIRECT_VIEW_WIRE_FRAME_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"

#include "../Graphics/ColorRGBA.h"

#include <memory>

namespace Crystal {
	namespace App {

class WireFrameRenderer {
public:

	WireFrameRenderer();

	~WireFrameRenderer();

	void build();

	struct Param {
		std::vector<float> positions;
		std::vector<float> values;
		float min;
		float max;
		std::vector<float> projectionMatrix;
		std::vector<float> modelviewMatrix;
	};

	void render(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices, const std::vector<Graphics::ColorRGBA<float> >& texColors, const bool withSurface );

	void renderCells(const int width, const int height, const Param& param, const std::vector< std::vector<unsigned int> >& indices, const std::vector<Graphics::ColorRGBA<float> >& texColors, const bool withSurface );

private:
	Graphics::ShaderObject shader;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint min;
		GLuint max;
		GLuint isConst;
		GLuint position;
		GLuint value;
		GLuint uValue;
	};

	Location getLocations();

	void setup(const int width, const int height);
};

	}
}

#endif