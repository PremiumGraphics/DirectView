#ifndef __CRYSTAL_PHYSICS_RIGID_ENFORCER_H__
#define __CRYSTAL_PHYSICS_RIGID_ENFORCER_H__

#include "Particle.h"
#include "Coordinator.h"

namespace Crystal{
	namespace Physics{

class RigidCoordinator : public Coordinator
{
public:
	RigidCoordinator(){};

	~RigidCoordinator(void){};

	void coordinate(const ParticleSPtrVector& particles, const float proceedTime);

private:
	Math::Vector3d angleVelosity;

	void convertToFluidForce(const ParticleSPtrVector& particles);

	void getAngleVelosity( const Math::Vector3d& I, const Math::Vector3d& N, const float proceedTime );
};

	}
}

#endif
