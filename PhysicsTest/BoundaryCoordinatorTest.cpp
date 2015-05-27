#include "gtest/gtest.h"
 
#include "../Physics/BoundaryCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
using T = float;

TEST( BoundaryCoordinatorTest, Test )
{
	const PhysicsParticleSPtr particle = std::make_shared<PhysicsParticle<T> >( Vector3d<T>( 0.0, 0.0, 0.0 ) );
	const PhysicsParticleSPtrVector particles{ particle };

	BoundaryCoordinator coordinator( Box::Unit(), 1.0f);
	coordinator.coordinate(particles);
	//BoundaryCoordinator b;
}
