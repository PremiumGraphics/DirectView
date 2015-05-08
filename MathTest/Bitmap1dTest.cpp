#include "gtest/gtest.h"

#include "../Math/Bitmap1d.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestConstruct)
{
	Bitmap1d<1> bitmap;
	EXPECT_EQ(1, bitmap.size());
	EXPECT_FALSE(bitmap[0]);
}

TEST(Bitmap1dTest, TestConstructByString)
{
	Bitmap1d<4> bitmap("1001");
	EXPECT_TRUE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(Bitmap1dTest, TestConstructByLong)
{
	EXPECT_EQ( Bitmap1d<2>("00"), Bitmap1d<2>(0) );
	EXPECT_EQ( Bitmap1d<2>("01"), Bitmap1d<2>(1) );
	EXPECT_EQ( Bitmap1d<2>("10"), Bitmap1d<2>(2) );
	EXPECT_EQ( Bitmap1d<2>("11"), Bitmap1d<2>(3) );
}

TEST(Bitmap1dTest, TestSet)
{
	Bitmap1d<1> bitmap(1);
	bitmap.set(0);

	EXPECT_TRUE(bitmap[0]);
}

TEST(Bitmap1dTest, TestSetAll)
{
	Bitmap1d<2> bitmap;
	bitmap.set();
	EXPECT_TRUE(bitmap[0]);
	EXPECT_TRUE(bitmap[1]);
}

TEST(Bitmap1dTest, TestResetAll)
{
	Bitmap1d<2> bitmap;
	bitmap.set();
	bitmap.reset();
	EXPECT_FALSE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(Bitmap1dTest, TestCount)
{
	EXPECT_EQ( 0, Bitmap1d<2>("00").count() );
	EXPECT_EQ( 1, Bitmap1d<2>("01").count() );
	EXPECT_EQ( 1, Bitmap1d<2>("10").count() );
	EXPECT_EQ( 2, Bitmap1d<2>("11").count() );
}

TEST(Bitmap1dTest, TestFlip)
{
	Bitmap1d<4> bitmap;
	bitmap.flip(0);
	EXPECT_EQ("0001", bitmap.toString());
	bitmap.flip();
	EXPECT_EQ("1110", bitmap.toString());
}

TEST(Bitmap1dTest, TestOperatorAnd)
{
	Bitmap1d<4> lhs("1100");
	const Bitmap1d<4> rhs("0111");
	lhs &= rhs;
	EXPECT_EQ("0100", lhs.toString());
}

TEST(Bitmap1dTest, TestOperatorOr)
{
	Bitmap1d<4> lhs("1100");
	const Bitmap1d<4> rhs("0111");
	lhs |= rhs;
	EXPECT_EQ("1111", lhs.toString());
}

TEST(Bitmap1dTest, TestAll)
{
	EXPECT_FALSE(Bitmap1d<2>("00").all());
	EXPECT_FALSE(Bitmap1d<2>("01").all());
	EXPECT_FALSE(Bitmap1d<2>("10").all());
	EXPECT_TRUE( Bitmap1d<2>("11").all());
}

TEST(Bitmap1dTest, TestAny)
{
	EXPECT_FALSE(Bitmap1d<2>("00").any());
	EXPECT_TRUE( Bitmap1d<2>("01").any());
	EXPECT_TRUE( Bitmap1d<2>("10").any());
	EXPECT_TRUE( Bitmap1d<2>("11").any());
}

TEST(Bitmap1dTest, TestNone)
{
	EXPECT_FALSE(Bitmap1d<4>("0010").none());
	EXPECT_TRUE( Bitmap1d<4>("0000").none());
}

