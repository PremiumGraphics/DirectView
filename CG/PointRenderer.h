#ifndef __CRYSTAL_APP_POINT_RENDERER_H__
#define __CRYSTAL_APP_POINT_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace CG {

class PointRenderer {
public:

	PointRenderer();

	~PointRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions, const float pointSize);

private:
	Graphics::ShaderObject shader;

};

	}
}

#endif