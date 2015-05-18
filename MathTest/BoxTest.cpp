#include "gtest/gtest.h"
 
#include "../Math/Box.h"

using namespace Crystal::Math;
 
TEST( BoxTest, TestGetMin )
{
	EXPECT_EQ( Position3d<float>(0.0f, 0.0f, 0.0f), Box().getMin() );
	EXPECT_EQ( Position3d<float>(1.0f, 2.0f, 3.0f), Box(Vector3d(1.0f, 2.0f, 3.0f), Vector3d(4.0f, 5.0f, 6.0f)).getMin());
}

TEST(BoxTest, TestGetMax)
{
	EXPECT_EQ( Position3d<float>(1.0f, 1.0f, 1.0f), Box().getMax());
	EXPECT_EQ( Position3d<float>(4.0f, 5.0f, 6.0f), Box(Vector3d(1.0f, 2.0f, 3.0f), Vector3d(4.0f, 5.0f, 6.0f)).getMax());
}

TEST( BoxTest, TestGetVolume )
{
	Box b( Vector3d( 0.0f, 0.0f, 0.0f ), Vector3d( 1.0f, 2.0f, 3.0f ) );
	EXPECT_TRUE( Tolerancef::isEqualLoosely( b.getVolume(), 6.0f ) );
}

TEST( BoxTest, TestGetLength )
{
	EXPECT_EQ( Vector3d(0.0, 1.0, 2.0), Box(Vector3d(1.0f, 1.0f, 1.0f), Vector3d(1.0f, 2.0f, 3.0f)).getLength() );
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

TEST(BoxTest, TestHasIntersection)
{
	Box b1( Vector3d(0.0f, 0.0f, 0.0f), Vector3d( 1.0f, 1.0f, 1.0f ) );
	Box b2(Vector3d(2.0f, 2.0f, 2.0f), Vector3d(4.0f, 4.0f, 4.0f));

	EXPECT_FALSE(b1.hasIntersection(b2));
}