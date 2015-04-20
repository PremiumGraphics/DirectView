#include "ParticleObjectBuilder.h"

#include "ParticleBase.h"
#include "ParticleBaseBuilder.h"


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
	ParticleBuilder pBuilder(divideLength);
	return build( pBuilder.create(box) );
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Sphere& s)
{
	ParticleBuilder pBuilder(divideLength);
	return build( pBuilder.create(s) );
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Cylinder& c)
{
	//ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	ParticleBuilder pBuilder(divideLength);
	return build( pBuilder.create(c));
}

ParticleObjectSPtr ParticleObjectBuilder::build(const std::list<ParticleBaseSPtr>& particles)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	for (const ParticleBaseSPtr& p : particles) {
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
