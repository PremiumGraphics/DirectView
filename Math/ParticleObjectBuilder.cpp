#include "ParticleObjectBuilder.h"

#include "ParticleBase.h"

using namespace Crystal::Math;


void ParticleObjectBuilder::clear()
{
	for (ParticleBase * p : particles) {
		delete p;
	}
	particles.clear();
	/*for (ParticleObject* o : objects) {
		delete o;
	}
	objects.clear();*/
}

ParticleObjectSPtr ParticleObjectBuilder::build()
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	//objects.push_back(object);
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Box& box)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				ParticleBase* p = new ParticleBase(divideLength, Vector3d(x, y, z), nextId++);
				particles.push_back(p);
				object->add(p);
			}
		}
	}
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Sphere& s)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	Math::Box box = s.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (s.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++ );
					particles.push_back(p);
					object->add(p);
				}
			}
		}
	}
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Cylinder& c)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	Box box = c.getBoundingBox();
	for (float x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (float y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (float z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d v(x, y, z);
				if (c.isInner(v)) {
					ParticleBase* p = new ParticleBase(divideLength, v, nextId++);
					particles.push_back(p);
					object->add(p);
				}
			}
		}
	}
	return object;

}

/*
ParticleObject* ParticleObjectBuilder::getObject(const unsigned int id)
{
	for (ParticleObject* object : objects) {
		if (object->getId() == id) {
			return object;
		}
	}
	return nullptr;
}
*/
