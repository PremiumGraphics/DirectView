#include "gtest/gtest.h"
 
#include "../Math/Sphere.h"
#include "../Math/Box.h"

using namespace Crystal::Math;

TEST( SphereTest, TestConstruct )
{
	Sphere s;
	EXPECT_TRUE( s.isValid() );
	EXPECT_EQ( s, Sphere::UnitSphere() );

	//EXPECT_TRUE( s.isShrinked() );
}

TEST( SphereTest, ShrinkTest )
{

}

TEST( SphereTest, BoundingBoxTest )
{
	Sphere s;
	const Box& bb = s.getBoundingBox();
	const Box expected( Vector3d( -1.0, -1.0, -1.0 ), Vector3d( 1.0, 1.0, 1.0 ) );
	EXPECT_EQ( expected, bb );
}

TEST( SphereTest, OffsetTest )
{
	Sphere s;
	s.outerOffset( 1.0f );
	EXPECT_EQ( 2.0f, s.getRadius() );

	s.innerOffset( 1.0f );
	EXPECT_EQ( 1.0f, s.getRadius() );
}

TEST(SphereTest, TestIsInner)
{
	Sphere s( Vector3d( 0.0, 0.0, 0.0 ), 1.0f );
	EXPECT_TRUE( s.isInner(Vector3d(0.0f, 0.0f, 0.0f) ) );
	EXPECT_FALSE( s.isInner(Vector3d( 2.0f, 0.0f, 0.0f) ) );
}