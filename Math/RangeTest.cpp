#include "gtest/gtest.h"

#include "../Math/Range.h"

using namespace Crystal::Math;

TEST(RangeTest, TestGetClamped)
{
	Range<float> r;
	EXPECT_EQ(0.0, r.getClamped(-1.0));
	EXPECT_EQ(0.5, r.getClamped( 0.5));
	EXPECT_EQ(1.0, r.getClamped( 2.0));
}

TEST(RangeTest, TestGetNormalized)
{
	Range<float> r(-1, 1);
	EXPECT_EQ(0.0, r.getNormalized(-1.0));
	EXPECT_EQ(0.5, r.getNormalized( 0.0));
	EXPECT_EQ(1.0, r.getNormalized( 1.0));
}

TEST(RangeTest, TestIsIn)
{
	Range<float> r;
	EXPECT_FALSE( r.isIn(-1.0) );
	EXPECT_TRUE(  r.isIn( 0.0) );
	EXPECT_TRUE(  r.isIn( 0.5) );
	EXPECT_TRUE(  r.isIn( 1.0) );
	EXPECT_FALSE( r.isIn( 2.0) );
}

TEST(RangeTest, TestIsOut)
{
	Range<float> r;
	EXPECT_TRUE(r.isOut(-1.0));
	EXPECT_FALSE(r.isOut(0.0));
	EXPECT_TRUE(r.isOut( 2.0));

	/*
	EXPECT_TRUE(r.isIn(0.0));
	EXPECT_TRUE(r.isIn(0.5));
	EXPECT_TRUE(r.isIn(1.0));
	EXPECT_FALSE(r.isIn(2.0));
	*/
}