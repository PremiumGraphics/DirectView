#ifndef __CRYSTAL_APP_VECTOR_RENDERER_H__
#define __CRYSTAL_APP_VECTOR_RENDERER_H__

#include "../Graphics/ShaderObject.h"
#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

#include <memory>

namespace Crystal {
	namespace Graphics {

class VectorRenderer {
public:

	VectorRenderer();

	~VectorRenderer();

	void build();

	void render( const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions, const std::vector<float>& vectors, const float min, const float max, const std::vector<Graphics::ColorRGBA<float> >& texColors, const float lineWidth, const float vectorScale );

private:
	Graphics::ShaderObject shader;
	
};

	}
}

#endif