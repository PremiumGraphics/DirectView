#include "gtest/gtest.h"

#include "../Math/Line1d.h"

using namespace Crystal::Math;

TEST(Line1dTest, TestGetStart)
{
	EXPECT_EQ( 0.0f, Line1d<float>().getStart());
	EXPECT_EQ( 1.0f, Line1d<float>(1.0f).getStart());

	//EXPECT_EQ( Vector1d(0.0f), Line1d< Vect>().getStart());

}

TEST(Line1dTest, TestGetLength)
{
	EXPECT_EQ( 1.0f, Line1d<float>().getLength());
	EXPECT_EQ( 10.0f, Line1d<float>( 1.0f, 10.0f).getLength());
}

TEST(Line1dTest, TestMove)
{
	EXPECT_EQ( Line1d<float>(1.0f, 1.0f), Line1d<float>().move(1.0f) );
	EXPECT_EQ( Line1d<float>(11.0f, 1.0f), Line1d<float>(10.0f).move(1.0f) );

}