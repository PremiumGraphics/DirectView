#ifndef __CRYSTAL_GRAPHICS_NORMAL_RENDERER_H__
#define __CRYSTAL_GRAPHICS_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Surface.h"

#include <memory>

namespace Crystal {
	namespace Graphics {

class NormalRenderer {
public:

	NormalRenderer();

	~NormalRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	float scale;

	void clear() {
		positions.clear();
		normals.clear();
	}

	void build(const Graphics::Surface<float >& s) {
			for (const auto& v : s.getVertices()) {
				const auto& ps = v->toPositionArray();
				positions.insert(positions.end(), ps.begin(), ps.end());
				const auto& ns = v->toNormalArray();
				normals.insert(normals.end(), ns.begin(), ns.end());

		}
	}

private:
	std::vector< float > positions;
	std::vector< float > normals;


private:
	Graphics::ShaderObject shader;

};

	}
}

#endif