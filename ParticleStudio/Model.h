#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Physics/ParticleBuilder.h"

namespace Crystal {
	namespace CG {

class Model {
public:
	Model() :
		pBuilder( 0.1f)
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		pBuilder.clear();
	}

	Graphics::Camera<float>* getCamera() { return &camera; }

	Physics::ParticleBuilder& getParticleBuilder() { return pBuilder; }

private:
	Graphics::Camera<float> camera;
	Physics::ParticleBuilder pBuilder;
};

	}
}

#endif