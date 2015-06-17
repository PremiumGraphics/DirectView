#ifndef __CRYSTAL_SHADER_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_RENDERER_H__

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Kernel.h"
#include "../Math/Volume.h"

namespace Crystal {
	namespace Shader {

class PointRenderer final
{
public:

	PointRenderer();

	~PointRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>* camera);

	void clear() {
		points.clear();
	}

	void add(const Math::Metaball<float>& ball, const unsigned int id) {
		const auto center = ball.getCenter();
		const auto cs = center.toArray();
		points.insert(points.end(), cs.begin(), cs.end());
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