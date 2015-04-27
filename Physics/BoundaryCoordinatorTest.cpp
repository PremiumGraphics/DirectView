#include "gtest/gtest.h"
 
#include "BoundaryCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( BoundaryCoordinatorTest, Test )
{
	PhysicsParticle::Constant constant;
	PhysicsParticleSPtr particle = std::make_shared<PhysicsParticle>( constant, Vector3d( 0.0, 0.0, 0.0 ) );
	PhysicsParticleSPtrVector particles{ particle };

	BoundaryCoordinator coordinator( Box::Unit(), 1.0f);
	coordinator.coordinate(particles);
	//BoundaryCoordinator b;
}
