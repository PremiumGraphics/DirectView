#ifndef __CRYSTAL_IO_PHYSICS_MODEL_H__
#define __CRYSTAL_IO_PHYSICS_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Physics/PhysicsObjectBuilder.h"

namespace Crystal {
	namespace Math {
		class Box;
		class Cylinder;
	}
	namespace IO {

class PhysicsModel {
public:
	PhysicsModel()
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		objects.clear();
	}

	Graphics::Camera<float>* getCamera() { return &camera; }

	Physics::PhysicsObjectSPtr create(const Math::Box& box);

	//PhysicsObjectSPtr create(const Math::Cylinder& c);

	std::list< Physics::PhysicsObjectSPtr > getObjects() const { return objects; }

private:
	Graphics::Camera<float> camera;
	Physics::PhysicsObjectBuilder builder;
	std::list< Physics::PhysicsObjectSPtr > objects;
};

	}
}

#endif