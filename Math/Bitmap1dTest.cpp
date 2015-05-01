#include "gtest/gtest.h"

#include "Bitmap1d.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestConstruct)
{
	Bitmap1d<1> bitmap;
	EXPECT_EQ(1, bitmap.size());
	EXPECT_FALSE(bitmap[0]);
	//bitmap[10] = true;
}

TEST(Bitmap1dTest, TestConstructByString)
{
	Bitmap1d<4> bitmap("1001");
	EXPECT_TRUE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(Bitmap1dTest, TestConstructByLong)
{
	Bitmap1d<4> bitmap(8);
	Bitmap1d<4> expected("1000");
	EXPECT_EQ(bitmap, expected);
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

TEST(Bitmap1dTest, TestTest)
{
	Bitmap1d<2> bitmap("10");
	EXPECT_FALSE(bitmap.test(0));
	EXPECT_TRUE(bitmap.test(1));
}

TEST(Bitmap1dTest, TestCount)
{
	Bitmap1d<4> bitmap("1001");
	EXPECT_EQ( 2, bitmap.count());
}

TEST(Bitmap1dTest, TestFlip)
{
	Bitmap1d<4> bitmap;
	bitmap.flip(0);
	EXPECT_EQ("0001", bitmap.to_string());
	bitmap.flip();
	EXPECT_EQ("1110",bitmap.to_string());
}


TEST(Bitmap1dTest, TestOperatorAnd)
{
	Bitmap1d<4> lhs("1100");
	const Bitmap1d<4> rhs("0111");
	lhs &= rhs;
	EXPECT_EQ("0100", lhs.to_string());
}

TEST(Bitmap1dTest, TestOperatorOr)
{
	Bitmap1d<4> lhs("1100");
	const Bitmap1d<4> rhs("0111");
	lhs |= rhs;
	EXPECT_EQ("1111", lhs.to_string());
}

TEST(Bitmap1dTest, TestOperatorNot)
{
	const Bitmap1d<4> bitmap;
	const auto actual = ~bitmap;
	EXPECT_EQ("1111", actual.to_string());
}

TEST(Bitmap1dTest, TestAllAny)
{
	EXPECT_FALSE(Bitmap1d<4>("0010").all());
	EXPECT_TRUE( Bitmap1d<4>("1111").all());
}

TEST(Bitmap1dTest, TestAny)
{
	EXPECT_TRUE( Bitmap1d<4>("0010").any());
	EXPECT_FALSE(Bitmap1d<4>("0000").any());
}

TEST(Bitmap1dTest, TestNone)
{
	{
		const Bitmap1d<4> bitmap("0010");
		EXPECT_FALSE(bitmap.none());
	}

	{
		const Bitmap1d<4> bitmap("0000");
		EXPECT_TRUE(bitmap.none());
	}
}

