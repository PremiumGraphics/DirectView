#ifndef __CRYSTAL_PHYSICS_SPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_SPH_SOLVER_H__

#include "PhysicsParticle.h"
#include "PhysicsObject.h"
#include "PhysicsParticleFindAlgo.h"
#include "Coordinator.h"

#ifdef _OPENMP
#include <omp.h>
#endif


namespace Crystal{
	namespace Physics{

template<typename T = float>
class SPHSolver
{
public:
	void solve(const PhysicsObjectSPtrVector& objects, const float effectLength) {
		const auto& particles = getParticles(objects);

		if (particles.empty()) {
			return;
		}

		for (const auto& particle : particles) {
			particle->init();
		}

		ParticleFindAlgo algo;
		algo.createPairs(particles, effectLength);
		const ParticlePairVector& pairs = algo.getPairs();

		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
			const float distance = pairs[i].getDistance();
			pairs[i].getParticle1()->addDensity(getPoly6Kernel(distance, effectLength) * pairs[i].getParticle2()->getMass());
		}

		for (int i = 0; i < static_cast<int>(particles.size()); ++i) {
			particles[i]->addDensity(getPoly6Kernel(0.0, effectLength) * particles[i]->getMass());
		}

		#pragma omp parallel for
		for (int i = 0; i < static_cast<int>(pairs.size()); ++i) {
			const float pressure = pairs[i].getPressure();
			const auto& distanceVector = pairs[i].getDistanceVector();
			pairs[i].getParticle1()->addForce(getSpikyKernelGradient(distanceVector, effectLength) * pressure * pairs[i].getParticle2()->getVolume());

			const float viscosityCoe = pairs[i].getViscosityCoe();
			const auto& velocityDiff = pairs[i].getVelocityDiff();
			const float distance = pairs[i].getDistance();
			pairs[i].getParticle2()->addForce(viscosityCoe * velocityDiff * getViscosityKernelLaplacian(distance, effectLength) * pairs[i].getParticle2()->getVolume());
		}

		for (const auto& object : objects) {
			object->coordinate();
		}

	}

private:
	ParticleSPtrVector getParticles(const PhysicsObjectSPtrVector& objects) {
		ParticleSPtrVector ordered;
		for (const auto& object : objects) {
			const auto& particles = object->getParticles();
			ordered.insert(ordered.end(), particles.begin(), particles.end());
		}
		return ordered;
	}

	float getPoly6Kernel(const float distance, const float effectLength) {
		const auto poly6Constant = 315.0f / (64.0f * Tolerancef::getPI() * pow(effectLength, 9));
		return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
	}

	Math::Vector3d<T> getPoly6KernelGradient(const Math::Vector3d<T>& distanceVector, const float effectLength) {
		const auto distance = distanceVector.getLength();
		const auto poly6ConstantGradient = 945.0f / (32.0f * Tolerancef::getPI() * pow(effectLength, 9));
		const auto factor = poly6ConstantGradient * pow(effectLength * effectLength - distance * distance, 2);
		return distanceVector * factor;
	}

	float getPoly6KernelLaplacian(const float distance, const float effectLength) {
		const auto poly6ConstantLaplacian = 945.0f / (32.0f * Tolerancef::getPI() * pow(effectLength, 9));
		return poly6ConstantLaplacian * (effectLength * effectLength - distance * distance)
			* (42.0f * distance * distance - 18.0f * effectLength * effectLength);
	}

	Math::Vector3d<T> getSpikyKernelGradient(const Math::Vector3d<T> &distanceVector, const float effectLength) {
		const auto constant = 45.0f / (Tolerancef::getPI() * pow(effectLength, 6));
		const auto distance = distanceVector.getLength();
		return distanceVector * constant * pow(effectLength - distance, 2) / distance;
	}

	float getViscosityKernelLaplacian(const float distance, const float effectLength) {
		const auto constant = 45.0f / (Tolerancef::getPI() * pow(effectLength, 6));
		return (effectLength - distance) * constant;
	}
};

	}
}

#endif