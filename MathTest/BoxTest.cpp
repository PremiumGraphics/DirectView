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
	EXPECT_TRUE( Tolerancef::isEqualLoosely(6.0f, Box(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 2.0f, 3.0f) ).getVolume()) );
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
	EXPECT_TRUE( Box(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f)).isShirinked());
	EXPECT_FALSE(Box(Vector3d(0.0f, 0.0, 0.0f), Vector3d(1.0f, 1.0f, 1.0f)).isShirinked());
}

TEST( BoxTest, TestIsValid )
{
	EXPECT_TRUE( Box(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 0.0f, 0.0f)).isValid() );
	EXPECT_TRUE( Box(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f)).isValid() );
}

TEST(BoxTest, TestHasIntersection)
{
	Box b1( Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f) );
	Box b2( Vector3d(2.0f, 2.0f, 2.0f), Vector3d(4.0f, 4.0f, 4.0f) );

	EXPECT_FALSE(b1.hasIntersection(b2));
}

TEST(BoxTest, TestGetOverlapped)
{
	Box b1(Vector3d(0.0f, 0.0f, 0.0f), Vector3d(1.0f, 1.0f, 1.0f));
	Box b2(Vector3d(0.5f, 0.5f, 0.5f), Vector3d(2.0f, 2.0f, 2.0f));
	const Box expected(Vector3d(0.5f, 0.5f, 0.5f), Vector3d(1.0f, 1.0f, 1.0f));
	const auto actual = b1.getOverlapped(b2);
	EXPECT_EQ(expected, actual);
}