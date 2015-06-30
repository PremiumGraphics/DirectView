#ifndef __CRYSTAL_SHADER_NORMAL_RENDERER_H__
#define __CRYSTAL_SHADER_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/Surface.h"

#include <memory>

namespace Crystal {
	namespace Shader {

class NormalRenderer {
public:

	NormalRenderer();

	~NormalRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	float scale;

	void add(const Graphics::Surface<float>& surface) {
		for (const auto& e : surface.getEdges()) {
			add(e->getStartPosition(), e->getStartVertex()->getNormal() );
		}
		//positions.add( surface.)
	}
	void clear() {
		positions.clear();
		normals.clear();
	}


private:
	std::vector< float > positions;
	std::vector< float > normals;

	void add(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal) {
		const auto& poss = position.toArray();
		positions.insert(positions.end(), poss.begin(), poss.end());
		const auto& norms = normal.toArray();
		normals.insert(normals.end(), norms.begin(), norms.end());
	}


private:
	ShaderObject shader;

};

	}
}

#endif