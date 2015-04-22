#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <memory>

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject {
public:
	PhysicsObject() {};
	
	PhysicsObject( const ParticleVector& particles, const CoordinatorVector& coordinators ) :
		particles( particles ),
		coordinators( coordinators )
	{}

	~PhysicsObject() {
		clear();
	}

	void coordinate() const {
		for( Coordinator* coordinator : coordinators ) {
			coordinator->coordinate( particles );
		}
	}

	ParticleVector getParticles() const { return particles; }

	void clear() {
		for( Particle* particle : particles ) {
			delete particle;
		}
		for( Coordinator* coordinator : coordinators ) {
			delete coordinator;
		}
		particles.clear();
		coordinators.clear();
	}

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

private:
	ParticleVector particles;
	CoordinatorVector coordinators;
	std::string name;
};

using PhysicsObjectSPtr = std::shared_ptr < PhysicsObject > ;



/*
void PhysicsObjectCollection::clear()
{
	for( PhysicsObject* object : objects ) {
		delete object;
	}
	objects.clear();
}

ParticleVector PhysicsObjectCollection::getParticles() const
{
	ParticleVector ordered;
	for( const PhysicsObject* object : objects ) {
		const ParticleVector& particles = object->getParticles();
		ordered.insert( ordered.end(), particles.begin(), particles.end() );
	}
	return ordered;
}

void PhysicsObjectCollection::coordinate() const
{
	for( PhysicsObject* object : objects ) {
		object->coordinate();
	}
}
*/
typedef std::vector< PhysicsObject* > PhysicsObjectVector;


	}
}

#endif