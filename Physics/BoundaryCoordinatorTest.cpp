#include "gtest/gtest.h"
 
#include "BoundaryCoordinator.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( BoundaryCoordinatorTest, Test )
{
	PhysicsParticle::Constant constant;
	PhysicsParticle particle( constant, Vector3d( 0.0, 0.0, 0.0 ) );
	//BoundaryCoordinator b;
}
