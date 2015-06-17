#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Kernel.h"
#include "../Math/Volume.h"

namespace Crystal {
	namespace Shader {

class PointRenderer {
public:

	PointRenderer();

	~PointRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera);

	void clear() {
	//	ids.clear();
	//	types.clear();
		points.clear();
	}


	void build(const Math::Volume3d<float>& ss, const unsigned int id) {
		const auto center = ss.getCenter();
		const auto cs = ss.getCenter().toArray();
		points.insert(points.end(), cs.begin(), cs.end());
		types.push_back(0);
	//	ids.push_back(id);
	}

	void build(const Math::Metaball<float>& ball, const unsigned int id) {
		const auto center = ball.getCenter();
		const auto cs = center.toArray();
		points.insert(points.end(), cs.begin(), cs.end());
	//	types.push_back(1);
	//	ids.push_back(ball.getId());
	}

private:
	std::vector< float > points;
	std::vector< int > types;
	std::vector< int > ids;


private:
	Graphics::ShaderObject shader;
};

	}
}

#endif