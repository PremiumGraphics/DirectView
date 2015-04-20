#ifndef __CRYSTAL_IO_MODEL_H__
#define __CRYSTAL_IO_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Math/ParticleObjectBuilder.h"

namespace Crystal {
	namespace IO {

class Model {
public:
	Model() :
		pBuilder(0.1f)
	{
		camera.setNear(1.0f);
	}

	void clear()
	{
		pBuilder.clear();
	}

	Graphics::Camera<float>* getCamera() { return &camera; }

	Math::ParticleObjectBuilder& getParticleBuilder() { return pBuilder; }

	Math::ParticleObjectSPtr create() {
		Math::ParticleObjectSPtr object = pBuilder.build();
		objects.push_back(object);
		return object;
	}

	Math::ParticleObjectSPtr create(const Math::Box& box) {
		Math::ParticleObjectSPtr object = pBuilder.build(box);
		objects.push_back(object);
		return object;
	}

	Math::ParticleObjectSPtr create(const Math::Sphere& sphere) {
		Math::ParticleObjectSPtr object = pBuilder.build(sphere);
		objects.push_back(object);
		return object;
	}

	Math::ParticleObjectSPtr create(const Math::Cylinder& cylinder) {
		Math::ParticleObjectSPtr object = pBuilder.build(cylinder);
		objects.push_back(object);
		return object;
	}

	void clearObjects() { objects.clear(); }

	//void remove(Math::ParticleObject* object) { pBuilder.}

	std::list< Math::ParticleObjectSPtr > getParticleObjects() const { return objects; }

	void clearSlectedObjects() { selectedObjects.clear(); }

	void addSelectedObject(Math::ParticleObjectSPtr object) { selectedObjects.push_back(object); }

	bool findSelectedObject(Math::ParticleObjectSPtr object) {
		return std::find(selectedObjects.begin(), selectedObjects.end(), object) != selectedObjects.end();
	}

	std::list<Math::ParticleObjectSPtr> getSelectedObjects() const { return selectedObjects; }

private:
	Graphics::Camera<float> camera;
	Math::ParticleObjectBuilder pBuilder;
	std::list<Math::ParticleObjectSPtr> objects;
	std::list<Math::ParticleObjectSPtr> selectedObjects;
};

	}
}

#endif