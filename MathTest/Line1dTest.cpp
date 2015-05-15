#include "gtest/gtest.h"

#include "../Math/Line1d.h"

using namespace Crystal::Math;

TEST(Line1dTest, TestGetStart)
{
	EXPECT_EQ( 0.0f, Line1d<float>().getStart());
	EXPECT_EQ( 1.0f, Line1d<float>(1.0f).getStart());
}

TEST(Line1dTest, TestGetLength)
{
	EXPECT_EQ( 1.0f, Line1d<float>().getLength());
}