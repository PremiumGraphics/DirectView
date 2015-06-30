#ifndef __CRYSTAL_SHADER_VOLUME_RENDERER_H__
#define __CRYSTAL_SHADER_VOLUME_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Buffer.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {

class VolumeRenderer final : private UnCopyable
{
public:

	VolumeRenderer() = default;

	~VolumeRenderer() = default;

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

	void build();

	void add(const Math::Volume3d<float>& volume) {
		const auto& ps = volume.toCenterPositions();
		const auto& vs = volume.getValues();
		assert(ps.size() == vs.size());
		for (size_t i = 0; i < ps.size(); ++i) {
			const auto& pss = ps[i].toArray();
			positions.insert(positions.end(), pss.begin(), pss.end());
			values.emplace_back(vs[i]);
		}
		//positions.add( surface.)
	}


	void clear() {
		positions.clear();
		values.clear();
	}


private:
	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint density;
	};

	Location getLocations();

	ShaderObject shader;


private:
	std::vector<float> positions;
	std::vector<float> values;

};

	}
}

#endif