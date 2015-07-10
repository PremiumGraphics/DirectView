#ifndef __CRYSTAL_SHADER_VOLUME_RENDERER_H__
#define __CRYSTAL_SHADER_VOLUME_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Math/Volume.h"
#include "../Graphics/Surface.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"
#include "RendererBase.h"

namespace Crystal {
	namespace Shader {

class VolumeRenderer final : public RendererBase
{
public:

	VolumeRenderer() = default;

	~VolumeRenderer() = default;


	//void add(const Graphics::BlendBrush<float>& particle) override{};

	void add(const Graphics::Surface<float>& surface) override{};

	void add(const Math::Volume3d<float>& volume) override;

	void render(const int width, const int height, const Graphics::Camera<float>& camera) override;

	void build();



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