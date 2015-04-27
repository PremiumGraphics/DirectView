#ifndef __CRYSTAL_PHYSICS_RIGID_ENFORCER_H__
#define __CRYSTAL_PHYSICS_RIGID_ENFORCER_H__

#include "PhysicsParticle.h"
#include "Coordinator.h"

namespace Crystal{
	namespace Physics{

class RigidCoordinator : public Coordinator
{
public:
	RigidCoordinator(){};

	~RigidCoordinator(void){};

	virtual void coordinate(const PhysicsParticleSPtrVector& particles) override;

	void setTimeStep(const float timeStep) { this->proceedTime = timeStep; }

private:
	Math::Vector3d angleVelosity;
	float proceedTime;

	void convertToFluidForce(const PhysicsParticleSPtrVector& particles);

	void getAngleVelosity( const Math::Vector3d& I, const Math::Vector3d& N, const float proceedTime );

	float getWeight(const PhysicsParticleSPtrVector& particles);
};

	}
}

#endif
