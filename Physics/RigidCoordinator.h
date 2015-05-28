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

	void convertToFluidForce(const ParticleSPtrVector& particles) {
		Math::Vector3d<float> totalForce(0.0, 0.0, 0.0);
		for (const auto& p : particles) {
			totalForce += p->getForce() * p->getVolume();
		}

		const float weight = getWeight(particles);
		for (const auto& p : particles) {
			p->setForce(totalForce / weight * p->getDensity());
		}
	}

	void getAngleVelosity(const Math::Vector3d<float>& I, const Math::Vector3d<float>& N, const float proceedTime);

	Math::Vector3d<float> getAverageVelosity(const ParticleSPtrVector& particles) {
		Math::Vector3d<float> averageVelosity(0.0, 0.0, 0.0);
		for (const auto& p : particles) {
			averageVelosity += p->getVelocity();// variable.velocity;
		}
		return averageVelosity / static_cast<float>(particles.size());
	}


	float getWeight(const ParticleSPtrVector& particles) {
		auto weight = 0.0f;
		for (const auto& particle : particles) {
			weight += particle->getMass();
		}
		return weight;
	}
};

	}
}

#endif
