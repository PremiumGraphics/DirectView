#ifndef __CRYSTAL_GRAPHICS_FAST_POINT_RENDERER_H__
#define __CRYSTAL_GRAPHICS_FAST_POINT_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class FastPointRenderer {
public:

	FastPointRenderer();

	~FastPointRenderer();

	void build();

	void render( const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions, const std::vector<float>& values, const float min, const float max, const std::vector<ColorRGBA<float> >& texColors, const float pointSize );

private:
	Graphics::ShaderObject shader;
	
};

	}
}

#endif