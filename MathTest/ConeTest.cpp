#include "gtest/gtest.h"
 
#include "../Math/Cone.h"

using namespace Crystal::Math;
 
TEST( ConeTest, TestConstruct )
{
	Cone cone;
	EXPECT_EQ( Vector3d( 0.0f, 0.0f, 0.0f ), cone.getCenter() );
	EXPECT_EQ( 1.0f, cone.getRadius() );
	EXPECT_EQ( 1.0f, cone.getHeight() );
}

TEST(ConeTest, TestGetSet)
{
	Cone cone;
	cone.setRadius(50.0f);
	cone.setHeight(10.0f);

	EXPECT_EQ(50.0f, cone.getRadius());
	EXPECT_EQ(10.0f, cone.getHeight());
}

TEST(ConeTest, TestVolume)
{
	Cone cone;
	const float actual = cone.getVolume();
	EXPECT_FLOAT_EQ(Tolerancef::getPI() / 3.0f, actual);
}