#ifndef __CRYSTAL_PHYSICS_FLUID_OBJECT_H__
#define __CRYSTAL_PHYSICS_FLUID_OBJECT_H__

#include "PhysicsObject.h"

namespace Crystal {
	namespace Physics {

class FluidObject : public PhysicsObject {
public:
	FluidObject()
	{}

	FluidObject(const PhysicsParticleSPtrVector& particles) :
		PhysicsObject(particles) 
	{}


	virtual ~FluidObject() = default;

};
	}
}

#endif