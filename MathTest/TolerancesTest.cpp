#include "gtest/gtest.h"
 
#include "../Math/Tolerances.h"

using namespace Crystal::Math;
 
TEST( TolerancesTest, isEqualLooseyTest )
{
	EXPECT_FALSE( Tolerances::isEqualLoosely( 0.0f, 1.0e-6f ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( 0.0f, 1.0e-12f ) );
	EXPECT_TRUE( Tolerances::isEqualLoosely( 0.0f, 1.0e-20f ) );
}

TEST( TolerancesTest, isEqualStrictlyTest )
{
	EXPECT_FALSE( Tolerances::isEqualStrictly( 0.0f, 1.0e-6f ) );
	EXPECT_FALSE( Tolerances::isEqualStrictly( 0.0f, 1.0e-12f ) );
	EXPECT_TRUE( Tolerances::isEqualStrictly( 0.0f, 1.0e-20f ) );
}