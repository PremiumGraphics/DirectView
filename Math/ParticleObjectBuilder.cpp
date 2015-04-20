#include "ParticleObjectBuilder.h"

#include "ParticleBase.h"


using namespace Crystal::Math;


void ParticleObjectBuilder::clear()
{
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
	ParticleBuilder pBuilder(divideLength);
	const std::vector<ParticleBaseSPtr>& ps = pBuilder.create(box);
	for (const ParticleBaseSPtr& p : ps) {
		object->add(p);
	}
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Sphere& s)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	ParticleBuilder pBuilder(divideLength);
	const std::vector<ParticleBaseSPtr>& ps = pBuilder.create(s);
	for (const ParticleBaseSPtr& p : ps) {
		object->add(p);
	}
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Cylinder& c)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	ParticleBuilder pBuilder(divideLength);
	const std::vector<ParticleBaseSPtr>& ps = pBuilder.create(c);
	for (const ParticleBaseSPtr& p : ps) {
		object->add(p);
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
