#ifndef __CRYSTAL_APP_PARTICLE_RENDERER_H__
#define __CRYSTAL_APP_PARTICLE_RENDERER_H__

#include "../Graphics/ShaderObject.h"

#include "../Graphics/Camera.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/DisplayList.h"

#include "../Math/ParticleBase.h"

#include <list>

namespace Crystal {
	namespace Shader {

		class ParticleRenderer {
		public:

			ParticleRenderer();

			~ParticleRenderer();

			void build();

			void render(const int width, const int height, const Graphics::Camera<float>* camera, const std::vector<float>& positions, const std::vector<unsigned int>& ids);

		private:
			Graphics::ShaderObject shader;
};

	}
}

#endif