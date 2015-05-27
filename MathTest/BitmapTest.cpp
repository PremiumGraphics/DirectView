#include "gtest/gtest.h"

#include "../Math/Bitmap.h"

using namespace Crystal::Math;

TEST(BitmapTest, TestGet)
{
	EXPECT_FALSE(Bitmap1d<1>().get(0));
}

TEST(BitmapTest, TestSet)
{
	EXPECT_TRUE(Bitmap1d<1>().set(0).get(0));
	EXPECT_TRUE(Bitmap1d<2>().set().get(0));
	EXPECT_TRUE(Bitmap1d<2>().set().get(1));
}

TEST(BitmapTest, TestToULong)
{
	EXPECT_EQ(0, Bitmap1d<2>("00").toULong());
	EXPECT_EQ(1, Bitmap1d<2>("01").toULong());
	EXPECT_EQ(2, Bitmap1d<2>("10").toULong());
	EXPECT_EQ(3, Bitmap1d<2>("11").toULong());
}

TEST(BitmapTest, TestToString)
{
	EXPECT_EQ("00", Bitmap1d<2>("00").toString());
	EXPECT_EQ("01", Bitmap1d<2>("01").toString());
	EXPECT_EQ("10", Bitmap1d<2>("10").toString());
	EXPECT_EQ("11", Bitmap1d<2>("11").toString());
}

TEST(BitmapTest, TestConstructByString)
{
	Bitmap1d<4> bitmap("1001");
	EXPECT_TRUE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(BitmapTest, TestConstructByLong)
{
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>(0));
	EXPECT_EQ(Bitmap1d<2>("01"), Bitmap1d<2>(1));
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>(2));
	EXPECT_EQ(Bitmap1d<2>("11"), Bitmap1d<2>(3));
}


TEST(BitmapTest, TestResetAll)
{
	Bitmap1d<2> bitmap;
	bitmap.set();
	bitmap.reset();
	EXPECT_FALSE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(BitmapTest, TestCount)
{
	EXPECT_EQ(0, Bitmap1d<2>("00").count());
	EXPECT_EQ(1, Bitmap1d<2>("01").count());
	EXPECT_EQ(1, Bitmap1d<2>("10").count());
	EXPECT_EQ(2, Bitmap1d<2>("11").count());
}

TEST(BitmapTest, TestAnd)
{
	EXPECT_EQ(Bitmap1d<2>("00").and(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("00").and(Bitmap1d<2>("01")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("00").and(Bitmap1d<2>("10")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("00").and(Bitmap1d<2>("11")), Bitmap1d<2>("00"));

	EXPECT_EQ(Bitmap1d<2>("01").and(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("01").and(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("01").and(Bitmap1d<2>("10")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("01").and(Bitmap1d<2>("11")), Bitmap1d<2>("01"));

	EXPECT_EQ(Bitmap1d<2>("10").and(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("10").and(Bitmap1d<2>("01")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("10").and(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").and(Bitmap1d<2>("11")), Bitmap1d<2>("10"));

	EXPECT_EQ(Bitmap1d<2>("11").and(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("11").and(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("11").and(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("11").and(Bitmap1d<2>("11")), Bitmap1d<2>("11"));
}

TEST(BitmapTest, TestOr)
{
	EXPECT_EQ(Bitmap1d<2>("00").or(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("00").or(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("00").or(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("00").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ(Bitmap1d<2>("01").or(Bitmap1d<2>("00")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("01").or(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("01").or(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("01").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ(Bitmap1d<2>("10").or(Bitmap1d<2>("00")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").or(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("10").or(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ(Bitmap1d<2>("11").or(Bitmap1d<2>("00")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("11").or(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("11").or(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("11").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));
}

TEST(BitmapTest, TestXor)
{
	EXPECT_EQ(Bitmap1d<2>("00").xor(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("00").xor(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("00").xor(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("00").xor(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ(Bitmap1d<2>("01").xor(Bitmap1d<2>("00")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("01").xor(Bitmap1d<2>("01")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("01").xor(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("01").xor(Bitmap1d<2>("11")), Bitmap1d<2>("10"));

	EXPECT_EQ(Bitmap1d<2>("10").xor(Bitmap1d<2>("00")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").xor(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("10").xor(Bitmap1d<2>("10")), Bitmap1d<2>("00"));
	EXPECT_EQ(Bitmap1d<2>("10").xor(Bitmap1d<2>("11")), Bitmap1d<2>("01"));

	EXPECT_EQ(Bitmap1d<2>("11").xor(Bitmap1d<2>("00")), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("11").xor(Bitmap1d<2>("01")), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("11").xor(Bitmap1d<2>("10")), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("11").xor(Bitmap1d<2>("11")), Bitmap1d<2>("00"));
}

TEST(BitmapTest, TestNot)
{
	EXPECT_EQ(Bitmap1d<2>("00").not(), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("01").not(), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").not(), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("11").not(), Bitmap1d<2>("00"));
}

TEST(BitmapTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAll());
	EXPECT_FALSE(Bitmap1d<2>("01").isAll());
	EXPECT_FALSE(Bitmap1d<2>("10").isAll());
	EXPECT_TRUE(Bitmap1d<2>("11").isAll());
}

TEST(BitmapTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAny());
	EXPECT_TRUE(Bitmap1d<2>("01").isAny());
	EXPECT_TRUE(Bitmap1d<2>("10").isAny());
	EXPECT_TRUE(Bitmap1d<2>("11").isAny());
}

TEST(BitmapTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap1d<2>("00").isNone());
	EXPECT_FALSE(Bitmap1d<2>("01").isNone());
	EXPECT_FALSE(Bitmap1d<2>("10").isNone());
	EXPECT_FALSE(Bitmap1d<2>("11").isNone());
}

TEST(BitmapTest, TestOperatorLeftShirt)
{
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>("00") <<= 1);
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>("01") <<= 1);
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>("10") <<= 1);
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>("11") <<= 1);
}

TEST(BitmapTest, TestTo8Bits)
{

}