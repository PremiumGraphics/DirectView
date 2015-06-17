#ifndef __CRYSTAL_SHADER_VOLUME_RENDERER_H__
#define __CRYSTAL_SHADER_VOLUME_RENDERER_H__

#include "ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Volume.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class VolumeRenderer final : private UnCopyable
{
public:

	VolumeRenderer();

	~VolumeRenderer();

	void build();

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	void clear() {
		points.clear();
	}

	void build(const Math::Volume3d<float>& ss) {
		const auto cells = ss.toCells();
		for (const auto& c : ss.toCells()) {
			const auto cs = c.getSpace().getCenter().toArray();
			points.insert(points.end(), cs.begin(), cs.end());
		}
	}

private:
	std::vector< float > points;
	Graphics::ShaderObject shader;
};

	}
}

#endif