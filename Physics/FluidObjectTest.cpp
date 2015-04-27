#include "gtest/gtest.h"

#include "FluidObject.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(FluidObjectTest, TestConstruct)
{
	FluidObject object;
	EXPECT_TRUE( object.getParticles().empty());
}