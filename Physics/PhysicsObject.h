#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <memory>

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject {
public:
	PhysicsObject() {};

	PhysicsObject(const PhysicsParticleSPtrVector& particles ) :
		particles(particles)
	{}


	PhysicsObject( const PhysicsParticleSPtrVector& particles, const CoordinatorSPtrVector& coordinators ) :
		particles( particles ),
		coordinators( coordinators )
	{}

	~PhysicsObject() {
		clear();
	}

	void coordinate() const {
		for( const auto& coordinator : coordinators ) {
			coordinator->coordinate( particles );
		}
	}

	PhysicsParticleSPtrVector getParticles() const { return particles; }

	void clear() {
		particles.clear();
		coordinators.clear();
	}

	void setName( const std::string& name ) { this->name = name; }

	std::string getName() const { return name; }

private:
	PhysicsParticleSPtrVector particles;
	CoordinatorSPtrVector coordinators;
	std::string name;
};

using PhysicsObjectSPtr = std::shared_ptr < PhysicsObject > ;
using PhysicsObjectSPtrVector = std::vector < PhysicsObjectSPtr > ;


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
//typedef std::vector< PhysicsObject* > PhysicsObjectVector;


	}
}

#endif