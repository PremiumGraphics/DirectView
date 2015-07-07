#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"
#include "../Math/Matrix.h"
#include "../Graphics/Light.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Material.h"
#include "../Graphics/Surface.h"

#include "RendererBase.h"

namespace Crystal {
	namespace Shader {

class SmoothRenderer final : public RendererBase {
public:

	SmoothRenderer() = default;

	~SmoothRenderer() = default;

	void build() override;

	void add(const Math::Particle3d<float>& particle) override {};

	void add(const Math::Volume3d<float>& volume) override {};

	void add(const Graphics::Surface<float>& surface) override
	{
		for (const auto& v : surface.getVertices()) {
			const auto& pos = v->getPosition();
			const auto& norms = v->getNormal();
			add(pos, norms);
		}
		//positions.add( surface.)
	}

	void clear() {
		positions.clear();
		normals.clear();
	}


	void render(const int width, const int height, const Graphics::Camera<float>& camera ) override;

private:
	ShaderObject shader;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint normal;
		GLuint eyePos;
		GLuint matAmbient;
		GLuint matSpecular;
		GLuint matDiffuse;
		GLuint shininess;
	};

	std::vector<float> positions;
	std::vector<float> normals;

	void add(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal) {
		const auto& poss = position.toArray3();
		positions.insert(positions.end(), std::begin(poss), std::end(poss));
		const auto& norms = normal.toArray3();
		normals.insert(normals.end(), std::begin(poss), std::end(poss));
	}


	Location getLocations();
};


	}
}

#endif