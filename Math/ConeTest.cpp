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