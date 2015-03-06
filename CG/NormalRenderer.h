#ifndef __CRYSTAL_APP_NORMAL_RENDERER_H__
#define __CRYSTAL_APP_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "../Graphics/ShaderObject.h"

#include "../Graphics/ShaderObject.h"
#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/DisplayList.h"

#include <memory>

namespace Crystal {
	namespace CG {

class NormalRenderer {
public:

	NormalRenderer();

	~NormalRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera, const Graphics::DisplayList& list );

private:
	Graphics::ShaderObject shader;

};

	}
}

#endif