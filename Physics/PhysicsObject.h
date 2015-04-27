#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <memory>

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject {
public:
	enum class Type {
		Fluid,
		Rigid,
	};

	PhysicsObject() {};

	PhysicsObject(const PhysicsParticleSPtrVector& particles ) :
		particles(particles)
	{}


	PhysicsObject( const PhysicsParticleSPtrVector& particles, const CoordinatorSPtrVector& coordinators ) :
		particles( particles ),
		coordinators( coordinators )
	{}

	virtual ~PhysicsObject() {
		clear();
	}

	void coordinate() const;

	PhysicsParticleSPtrVector getParticles() const { return particles; }

	float getMass() const;

	float getVolume() const;

	void clear() {
		particles.clear();
		coordinators.clear();
	}

private:
	PhysicsParticleSPtrVector particles;
	CoordinatorSPtrVector coordinators;
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