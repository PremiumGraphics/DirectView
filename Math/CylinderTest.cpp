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

TEST(CylinderTest, TestIsInner)
{
	Cylinder c( Vector3d( 0.0, 0.0, 0.0 ), 1.0f, 1.0f );
	EXPECT_TRUE( c.isInner(Vector3d(0.5f, 0.0, 0.0)) );
}

TEST(CylinderTest, TestGetBoundingBox)
{
	Cylinder c(Vector3d(0.0, 0.0, 0.0), 1.0f, 1.0f );
	const Box& b = c.getBoundingBox();
	EXPECT_FLOAT_EQ(-1.0f, b.getMinX());
	EXPECT_FLOAT_EQ( 1.0f, b.getMaxX());
}