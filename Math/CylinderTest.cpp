#include "gtest/gtest.h"
 
#include "../Math/Cylinder.h"

using namespace Crystal::Math;

TEST( CylinderTest, TestConstruct )
{
	Cylinder c;
	EXPECT_TRUE( c.isValid() );
	EXPECT_EQ( 1.0f, c.getRadius() );
	EXPECT_EQ( 1.0f, c.getHeight());
}

TEST(CylinderTest, TestGetSet)
{
	Cylinder c;
	c.setHeight(10.0f);
	c.setRadius(50.0f);

	EXPECT_EQ(10.0f, c.getHeight());
	EXPECT_EQ(50.0f, c.getRadius());
}

TEST(CylinderTest, TestVolume)
{
	Cylinder c;
	EXPECT_FLOAT_EQ( Tolerances::getPI(), c.getVolume() );
}