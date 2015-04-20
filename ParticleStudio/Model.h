#ifndef __CRYSTAL_APP_MODEL_H__
#define __CRYSTAL_APP_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Math/ParticleObjectBuilder.h"

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

	Math::ParticleObjectBuilder& getParticleBuilder() { return pBuilder; }

	void clearSlectedObjects() { selectedObjects.clear(); }

	void addSelectedObject(Math::ParticleObject* object) { selectedObjects.push_back(object); }

	std::list<Math::ParticleObject*> getSelectedObjects() const { return selectedObjects; }

private:
	Graphics::Camera<float> camera;
	Math::ParticleObjectBuilder pBuilder;
	std::list<Math::ParticleObject*> selectedObjects;
};

	}
}

#endif