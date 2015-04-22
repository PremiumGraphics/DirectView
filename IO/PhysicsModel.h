#ifndef __CRYSTAL_IO_PHYSICS_MODEL_H__
#define __CRYSTAL_IO_PHYSICS_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Particle/ParticleObjectBuilder.h"

namespace Crystal {
	namespace IO {

class PhysicsModel {
public:
	PhysicsModel()
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
	}

	Graphics::Camera<float>* getCamera() { return &camera; }


private:
	Graphics::Camera<float> camera;
};

	}
}

#endif