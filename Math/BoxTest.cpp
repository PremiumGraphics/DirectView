#include "gtest/gtest.h"
 
#include "../Math/Box.h"

using namespace Crystal::Math;
 
TEST( BoxTest, TestConstruct )
{
	Box b;
	EXPECT_EQ( b.getVolume(), 1.0f );
}

TEST( BoxTest, getVolumeTest )
{
	Box b( Vector3d( 0.0f, 0.0f, 0.0f ), Vector3d( 1.0f, 2.0f, 3.0f ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( b.getVolume(), 6.0f ) );
}

TEST( BoxTest, LengthTest )
{
	Box b( Vector3d( 1.0f, 1.0f, 1.0f ), Vector3d( 1.0f, 2.0f, 3.0f ) );
	const Vector3d& lengths = b.getLength();
	EXPECT_EQ( lengths, Vector3d( 0.0, 1.0, 2.0 ) );

}

TEST( BoxTest, offsetTest )
{
	Box b;
	b.outerOffset( 1.0f );
	EXPECT_EQ( b, Box( Vector3d( -1.0f, -1.0f, -1.0f ), Vector3d( 2.0f, 2.0f, 2.0f ) ) );
}

TEST( BoxTest, isShrinkedTest )
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

TEST( BoxTest, isValidTest )
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