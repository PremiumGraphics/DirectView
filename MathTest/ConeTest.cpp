#include "gtest/gtest.h"
 
#include "../Math/Cone.h"

using namespace Crystal::Math;
 
TEST( ConeTest, TestConstruct )
{
	Cone<float> cone;
	EXPECT_EQ( Vector3d<float>( 0.0f, 0.0f, 0.0f ), cone.getCenter() );
	EXPECT_EQ( 1.0f, cone.getRadius() );
	EXPECT_EQ( 1.0f, cone.getHeight() );
}

TEST(ConeTest, TestGetSet)
{
	Cone<float> cone;
	cone.setRadius(50);
	cone.setHeight(10);

	EXPECT_EQ(50, cone.getRadius());
	EXPECT_EQ(10, cone.getHeight());
}

TEST(ConeTest, TestVolume)
{
	EXPECT_FLOAT_EQ(Tolerance<float>::getPI() / 3.0f, Cone<float>().getVolume());
}