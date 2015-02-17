#include "gtest/gtest.h"
 
#include "../Math/Cylinder.h"

using namespace Crystal::Math;

TEST( CylinderTest, TestConstruct )
{
	Cylinder c;
	EXPECT_TRUE( c.isValid() );
	EXPECT_EQ( 1.0f, c.getRadius() );
}
