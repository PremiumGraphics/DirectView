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

	virtual void coordinate(const ParticleSPtrVector& particles) override;

	void setTimeStep(const float timeStep) { this->proceedTime = timeStep; }

private:
	Math::Vector3d<float> angleVelosity;
	float proceedTime;

	void convertToFluidForce(const ParticleSPtrVector& particles);

	void getAngleVelosity( const Math::Vector3d<float>& I, const Math::Vector3d<float>& N, const float proceedTime );

	float getWeight(const ParticleSPtrVector& particles);
};

	}
}

#endif
