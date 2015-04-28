#include "ParticleObjectBuilder.h"

#include "ParticleBase.h"
#include "ParticleBaseBuilder.h"


using namespace Crystal::Math;
using namespace Crystal::Particle;

void ParticleObjectBuilder::clear()
{
	/*for (ParticleObject* o : objects) {
		delete o;
	}
	objects.clear();*/
}

ParticleObjectSPtr ParticleObjectBuilder::build()
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextId++);
	//objects.push_back(object);
	return object;
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Box& box)
{
	ParticleBaseBuilder pBuilder(divideLength);
	pBuilder.create(box);
	return build( pBuilder.getParticles() );
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Sphere& s)
{
	ParticleBaseBuilder pBuilder(divideLength);
	pBuilder.create(s);
	return build( pBuilder.getParticles() );
}

ParticleObjectSPtr ParticleObjectBuilder::build(const Cylinder& c)
{
	//ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextObjectId++);
	ParticleBaseBuilder pBuilder(divideLength);
	pBuilder.create(c);
	return build( pBuilder.getParticles());
}

ParticleObjectSPtr ParticleObjectBuilder::build(const std::list<ParticleBaseSPtr>& particles)
{
	ParticleObjectSPtr object = std::make_shared<ParticleObject>(nextId++);
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
