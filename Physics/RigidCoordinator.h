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


	void getAngleVelosity(const Math::Vector3d<float>& I, const Math::Vector3d<float>& N, const float proceedTime)
	{
		float x1, x2, x3;
		const int innerSteps = 10;
		float h = proceedTime / innerSteps;

		x1 = angleVelosity.getX();
		x2 = angleVelosity.getY();
		x3 = angleVelosity.getZ();

		for (int i = 0; i < innerSteps; i++){
			const float k11 = h * getAngleAccelerationX(x1, x2, x3, I, N);
			const float k21 = h * getAngleAccelerationY(x1, x2, x3, I, N);
			const float k31 = h * getAngleAccelerationZ(x1, x2, x3, I, N);
			const float k12 = h * getAngleAccelerationX(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
			const float k22 = h * getAngleAccelerationY(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
			const float k32 = h * getAngleAccelerationZ(x1 + k11 / 2.0f, x2 + k21 / 2.0f, x3 + k31 / 2.0f, I, N);
			const float k13 = h * getAngleAccelerationX(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
			const float k23 = h * getAngleAccelerationY(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
			const float k33 = h * getAngleAccelerationZ(x1 + k12 / 2.0f, x2 + k22 / 2.0f, x3 + k32 / 2.0f, I, N);
			const float k14 = h * getAngleAccelerationX(x1 + k13, x2 + k23, x3 + k33, I, N);
			const float k24 = h * getAngleAccelerationY(x1 + k13, x2 + k23, x3 + k33, I, N);
			const float k34 = h * getAngleAccelerationZ(x1 + k13, x2 + k23, x3 + k33, I, N);

			const float dx1 = (k11 + 2.0f * k12 + 2.0f * k13 + k14) / 6.0f;
			const float dx2 = (k21 + 2.0f * k22 + 2.0f * k23 + k24) / 6.0f;
			const float dx3 = (k31 + 2.0f * k32 + 2.0f * k33 + k34) / 6.0f;

			x1 += dx1;
			x2 += dx2;
			x3 += dx3;
		}

		//angleVelosity.x = x1;
		//angleVelosity.y = x2;
		//angleVelosity.z = x3;
		angleVelosity = Math::Vector3d<float>(x1, x2, x3);
	}


	float getAngleAccelerationX(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getX() + (I.getY() - I.getZ()) * x2 * x3) / I.getX() - 10.0f * x1;
	}

	float getAngleAccelerationY(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getY() + (I.getZ() - I.getX()) * x3 * x1) / I.getY() - 10.0f * x2;
	}

	float getAngleAccelerationZ(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getZ() + (I.getX() - I.getY()) * x1 * x2) / I.getZ() - 10.0f * x3;
	}

};

	}
}

#endif
