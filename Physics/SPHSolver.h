#ifndef __CRYSTAL_PHYSICS_SPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_SPH_SOLVER_H__

#include "PhysicsParticle.h"
#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics{

template<typename T = float>
class SPHSolver
{
public:
	void solve(const PhysicsObjectSPtrVector& objects, const float effectLength );

private:
	PhysicsParticleSPtrVector getParticles(const PhysicsObjectSPtrVector& objects) {
		PhysicsParticleSPtrVector ordered;
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

	Math::Vector3d<T> getPoly6KernelGradient( const Math::Vector3d<T>& distanceVector, const float effectLength );

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