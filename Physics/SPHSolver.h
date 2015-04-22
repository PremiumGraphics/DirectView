#ifndef __CRYSTAL_PHYSICS_SPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_SPH_SOLVER_H__

#include "Particle.h"
#include "PhysicsObject.h"

namespace Crystal{
	namespace Physics{

class SPHSolver
{
public:
	void solve(const PhysicsObjectVector& objects, const float effectLength );

private:
	ParticleSPtrVector getParticles( const PhysicsObjectVector& objects );

	float getPoly6Kernel( const float distance, const float effectLength );

	Math::Vector3d getPoly6KernelGradient( const Math::Vector3d& distanceVector, const float effectLength );

	float getPoly6KernelLaplacian(const float distance, const float effectLength );

	Math::Vector3d getSpikyKernelGradient(const Math::Vector3d &distanceVector, const float effectLength );

	float getViscosityKernelLaplacian(const float distance, const float effectLength );
};

	}
}

#endif