#ifndef __CRYSTAL_IO_MODEL_H__
#define __CRYSTAL_IO_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Particle/ParticleObjectBuilder.h"

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

	Particle::ParticleObjectSPtr create() {
		Particle::ParticleObjectSPtr object = pBuilder.build();
		objects.push_back(object);
		return object;
	}

	Particle::ParticleObjectSPtr create(const Math::Box& box) {
		Particle::ParticleObjectSPtr object = pBuilder.build(box);
		objects.push_back(object);
		return object;
	}

	Particle::ParticleObjectSPtr create(const Math::Sphere& sphere) {
		Particle::ParticleObjectSPtr object = pBuilder.build(sphere);
		objects.push_back(object);
		return object;
	}

	Particle::ParticleObjectSPtr create(const Math::Cylinder& cylinder) {
		Particle::ParticleObjectSPtr object = pBuilder.build(cylinder);
		objects.push_back(object);
		return object;
	}

	void clearObjects() { objects.clear(); }

	Particle::ParticleObjectSPtr getObjectById(const unsigned int id);

	//void remove(Math::ParticleObject* object) { pBuilder.}

	std::list< Particle::ParticleObjectSPtr > getParticleObjects() const { return objects; }

	void clearSlectedObjects() { selectedObjects.clear(); }

	void removeSelectedObject(Particle::ParticleObjectSPtr object) { selectedObjects.remove(object); }

	void addSelectedObject(Particle::ParticleObjectSPtr object) { selectedObjects.push_back(object); }

	bool findSelectedObject(Particle::ParticleObjectSPtr object) {
		return std::find(selectedObjects.begin(), selectedObjects.end(), object) != selectedObjects.end();
	}

	std::list<Particle::ParticleObjectSPtr> getSelectedObjects() const { return selectedObjects; }


private:
	Graphics::Camera<float> camera;
	Particle::ParticleObjectBuilder pBuilder;
	std::list<Particle::ParticleObjectSPtr> objects;
	std::list<Particle::ParticleObjectSPtr> selectedObjects;
};

	}
}

#endif