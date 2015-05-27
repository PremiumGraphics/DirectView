#include "BoundaryCoordinator.h"

#include "../Math/Box.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

#ifdef _OPENMP
#include <omp.h>
#endif


Vector3d<float> BoundaryCoordinator::getForceY(const float y, const Box<float>& box, const float timeStep)
{
	float over = 0.0f;
	if( y > box.getMaxY() ) {
		over = y - box.getMaxY();
	}
	else if( y < box.getMinY() ) {
		over = y - box.getMinY();
	}
	const float force = getForce( over );
	return Vector3d<float>::UnitY() * force;
}

Vector3d<float> BoundaryCoordinator::getForceZ(const float z, const Box<float>& box, const float timeStep)
{
	float over = 0.0f;
	if( z > box.getMaxZ() ) {
		over = z - box.getMaxZ();
	}
	else if( z < box.getMinZ() ) {
		over = z - box.getMinZ();
	}
	const float force = getForce( over );
	return Vector3d<float>::UnitZ() * force;
}


void BoundaryCoordinator::coordinate(const PhysicsParticleSPtrVector& particles )
{
	#pragma omp parallel for
	for( int i = 0; i < static_cast<int>( particles.size() ); ++i ) {
		particles[i]->addForce( getForce( particles[i]->getCenter(), box ) * particles[i]->getDensity() );
	}
};