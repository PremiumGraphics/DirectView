#include "gtest/gtest.h"
 
#include "PhysicsObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;
 
TEST( PhysicsObjectTest, Test )
{
	PhysicsObject object;
	EXPECT_TRUE( object.getParticles().empty() );
	//Particle::Constant constant;
	//Particle particle( constant, Vector3d( 0.0, 0.0, 0.0 ) );
}

TEST(PhysicsObjectTest, TestGetMass)
{
	PhysicsObject object;
	EXPECT_EQ(0.0f, object.getMass());
}