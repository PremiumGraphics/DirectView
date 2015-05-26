#include "gtest/gtest.h"

#include "../Math/Bitmap.h"

using namespace Crystal::Math;

TEST(BitmapTest, TestGet)
{
	EXPECT_FALSE(Bitmap<1>().get(0));
}

TEST(BitmapTest, TestSet)
{
	EXPECT_TRUE(Bitmap<1>().set(0).get(0));
	EXPECT_TRUE(Bitmap<2>().set().get(0));
	EXPECT_TRUE(Bitmap<2>().set().get(1));
}

TEST(BitmapTest, TestToULong)
{
	EXPECT_EQ(0, Bitmap<2>("00").toULong());
	EXPECT_EQ(1, Bitmap<2>("01").toULong());
	EXPECT_EQ(2, Bitmap<2>("10").toULong());
	EXPECT_EQ(3, Bitmap<2>("11").toULong());
}

TEST(BitmapTest, TestToString)
{
	EXPECT_EQ("00", Bitmap<2>("00").toString());
	EXPECT_EQ("01", Bitmap<2>("01").toString());
	EXPECT_EQ("10", Bitmap<2>("10").toString());
	EXPECT_EQ("11", Bitmap<2>("11").toString());
}

TEST(BitmapTest, TestConstructByString)
{
	Bitmap<4> bitmap("1001");
	EXPECT_TRUE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(BitmapTest, TestConstructByLong)
{
	EXPECT_EQ(Bitmap<2>("00"), Bitmap<2>(0));
	EXPECT_EQ(Bitmap<2>("01"), Bitmap<2>(1));
	EXPECT_EQ(Bitmap<2>("10"), Bitmap<2>(2));
	EXPECT_EQ(Bitmap<2>("11"), Bitmap<2>(3));
}


TEST(BitmapTest, TestResetAll)
{
	Bitmap<2> bitmap;
	bitmap.set();
	bitmap.reset();
	EXPECT_FALSE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(BitmapTest, TestCount)
{
	EXPECT_EQ(0, Bitmap<2>("00").count());
	EXPECT_EQ(1, Bitmap<2>("01").count());
	EXPECT_EQ(1, Bitmap<2>("10").count());
	EXPECT_EQ(2, Bitmap<2>("11").count());
}

TEST(BitmapTest, TestAnd)
{
	EXPECT_EQ(Bitmap<2>("00").and(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("00").and(Bitmap<2>("01")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("00").and(Bitmap<2>("10")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("00").and(Bitmap<2>("11")), Bitmap<2>("00"));

	EXPECT_EQ(Bitmap<2>("01").and(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("01").and(Bitmap<2>("01")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("01").and(Bitmap<2>("10")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("01").and(Bitmap<2>("11")), Bitmap<2>("01"));

	EXPECT_EQ(Bitmap<2>("10").and(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("10").and(Bitmap<2>("01")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("10").and(Bitmap<2>("10")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("10").and(Bitmap<2>("11")), Bitmap<2>("10"));

	EXPECT_EQ(Bitmap<2>("11").and(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("11").and(Bitmap<2>("01")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("11").and(Bitmap<2>("10")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("11").and(Bitmap<2>("11")), Bitmap<2>("11"));
}

TEST(BitmapTest, TestOr)
{
	EXPECT_EQ(Bitmap<2>("00").or(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("00").or(Bitmap<2>("01")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("00").or(Bitmap<2>("10")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("00").or(Bitmap<2>("11")), Bitmap<2>("11"));

	EXPECT_EQ(Bitmap<2>("01").or(Bitmap<2>("00")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("01").or(Bitmap<2>("01")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("01").or(Bitmap<2>("10")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("01").or(Bitmap<2>("11")), Bitmap<2>("11"));

	EXPECT_EQ(Bitmap<2>("10").or(Bitmap<2>("00")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("10").or(Bitmap<2>("01")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("10").or(Bitmap<2>("10")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("10").or(Bitmap<2>("11")), Bitmap<2>("11"));

	EXPECT_EQ(Bitmap<2>("11").or(Bitmap<2>("00")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("11").or(Bitmap<2>("01")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("11").or(Bitmap<2>("10")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("11").or(Bitmap<2>("11")), Bitmap<2>("11"));
}

TEST(BitmapTest, TestXor)
{
	EXPECT_EQ(Bitmap<2>("00").xor(Bitmap<2>("00")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("00").xor(Bitmap<2>("01")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("00").xor(Bitmap<2>("10")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("00").xor(Bitmap<2>("11")), Bitmap<2>("11"));

	EXPECT_EQ(Bitmap<2>("01").xor(Bitmap<2>("00")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("01").xor(Bitmap<2>("01")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("01").xor(Bitmap<2>("10")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("01").xor(Bitmap<2>("11")), Bitmap<2>("10"));

	EXPECT_EQ(Bitmap<2>("10").xor(Bitmap<2>("00")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("10").xor(Bitmap<2>("01")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("10").xor(Bitmap<2>("10")), Bitmap<2>("00"));
	EXPECT_EQ(Bitmap<2>("10").xor(Bitmap<2>("11")), Bitmap<2>("01"));

	EXPECT_EQ(Bitmap<2>("11").xor(Bitmap<2>("00")), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("11").xor(Bitmap<2>("01")), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("11").xor(Bitmap<2>("10")), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("11").xor(Bitmap<2>("11")), Bitmap<2>("00"));
}

TEST(BitmapTest, TestNot)
{
	EXPECT_EQ(Bitmap<2>("00").not(), Bitmap<2>("11"));
	EXPECT_EQ(Bitmap<2>("01").not(), Bitmap<2>("10"));
	EXPECT_EQ(Bitmap<2>("10").not(), Bitmap<2>("01"));
	EXPECT_EQ(Bitmap<2>("11").not(), Bitmap<2>("00"));
}

TEST(BitmapTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap<2>("00").isAll());
	EXPECT_FALSE(Bitmap<2>("01").isAll());
	EXPECT_FALSE(Bitmap<2>("10").isAll());
	EXPECT_TRUE(Bitmap<2>("11").isAll());
}

TEST(BitmapTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap<2>("00").isAny());
	EXPECT_TRUE(Bitmap<2>("01").isAny());
	EXPECT_TRUE(Bitmap<2>("10").isAny());
	EXPECT_TRUE(Bitmap<2>("11").isAny());
}

TEST(BitmapTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap<2>("00").isNone());
	EXPECT_FALSE(Bitmap<2>("01").isNone());
	EXPECT_FALSE(Bitmap<2>("10").isNone());
	EXPECT_FALSE(Bitmap<2>("11").isNone());
}

TEST(BitmapTest, TestOperatorLeftShirt)
{
	EXPECT_EQ(Bitmap<2>("00"), Bitmap<2>("00") <<= 1);
	EXPECT_EQ(Bitmap<2>("10"), Bitmap<2>("01") <<= 1);
	EXPECT_EQ(Bitmap<2>("00"), Bitmap<2>("10") <<= 1);
	EXPECT_EQ(Bitmap<2>("10"), Bitmap<2>("11") <<= 1);
}