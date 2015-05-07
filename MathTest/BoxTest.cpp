#include "gtest/gtest.h"
 
#include "../Math/Box.h"

using namespace Crystal::Math;
 
TEST( BoxTest, TestConstruct )
{
	Box b;
	EXPECT_EQ( Vector3d(0.0f, 0.0f, 0.0f), b.getMin() );
	EXPECT_EQ( Vector3d(1.0f, 1.0f, 1.0f), b.getMax() );
}

TEST(BoxTest, TestConstrutByVectors)
{
	Box b(Vector3d(1.0f, 2.0f, 3.0f), Vector3d(4.0f, 5.0f, 6.0f));
	EXPECT_EQ(Vector3d(1.0f, 2.0f, 3.0f), b.getMin());
	EXPECT_EQ(Vector3d(4.0f, 5.0f, 6.0f), b.getMax());
}

TEST( BoxTest, TestGetVolume )
{
	Box b( Vector3d( 0.0f, 0.0f, 0.0f ), Vector3d( 1.0f, 2.0f, 3.0f ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( b.getVolume(), 6.0f ) );
}

TEST( BoxTest, TestGetLength )
{
	Box b( Vector3d( 1.0f, 1.0f, 1.0f ), Vector3d( 1.0f, 2.0f, 3.0f ) );
	const Vector3d& lengths = b.getLength();
	EXPECT_EQ( lengths, Vector3d( 0.0, 1.0, 2.0 ) );

}

TEST( BoxTest, TestOuterOffset )
{
	Box b;
	b.outerOffset( 1.0f );
	EXPECT_EQ( b, Box( Vector3d( -1.0f, -1.0f, -1.0f ), Vector3d( 2.0f, 2.0f, 2.0f ) ) );
}

TEST( BoxTest, TestIsShrinked )
{
	{
		Box b( Vector3d( 0.0f, 0.0f, 0.0f ), Vector3d( 0.0f, 0.0f, 0.0f ) );
		EXPECT_TRUE( b.isShirinked() );
	}

	{
		Box b( Vector3d( 0.0f, 0.0, 0.0f ), Vector3d( 1.0f, 1.0f, 1.0f ) );
		EXPECT_FALSE( b.isShirinked() );
	}
}

TEST( BoxTest, TestIsValid )
{
	{
		Box b( Vector3d( 0.0f, 0.0f, 0.0f ), Vector3d( 0.0f, 0.0f, 0.0f ) );
		EXPECT_TRUE( b.isValid() );
	}

	{
		Box b( Vector3d( 0.0f, 0.0, 0.0f ), Vector3d( 1.0f, 1.0f, 1.0f ) );
		EXPECT_TRUE( b.isValid() );
	}
}