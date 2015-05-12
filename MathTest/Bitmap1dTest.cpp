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
	EXPECT_TRUE( bitmap[0]);
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
	Bitmap1d<2> bitmap;
	bitmap.set(0);
	EXPECT_TRUE(bitmap[0]);
	bitmap.set(1);
	EXPECT_TRUE(bitmap[1]);
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

TEST(Bitmap1dTest, TestAnd)
{
	EXPECT_EQ( Bitmap1d<2>("00").and(Bitmap1d<2>("00") ), Bitmap1d<2>("00") );
	EXPECT_EQ( Bitmap1d<2>("00").and(Bitmap1d<2>("01") ), Bitmap1d<2>("00") );
	EXPECT_EQ( Bitmap1d<2>("00").and(Bitmap1d<2>("10") ), Bitmap1d<2>("00") );
	EXPECT_EQ( Bitmap1d<2>("00").and(Bitmap1d<2>("11") ), Bitmap1d<2>("00") );

	EXPECT_EQ( Bitmap1d<2>("01").and(Bitmap1d<2>("00") ), Bitmap1d<2>("00") );
	EXPECT_EQ( Bitmap1d<2>("01").and(Bitmap1d<2>("01") ), Bitmap1d<2>("01") );
	EXPECT_EQ( Bitmap1d<2>("01").and(Bitmap1d<2>("10") ), Bitmap1d<2>("00") );
	EXPECT_EQ( Bitmap1d<2>("01").and(Bitmap1d<2>("11") ), Bitmap1d<2>("01") );

	EXPECT_EQ( Bitmap1d<2>("10").and(Bitmap1d<2>("00") ), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("10").and(Bitmap1d<2>("01") ), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("10").and(Bitmap1d<2>("10") ), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("10").and(Bitmap1d<2>("11") ), Bitmap1d<2>("10"));

	EXPECT_EQ( Bitmap1d<2>("11").and(Bitmap1d<2>("00") ), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("11").and(Bitmap1d<2>("01") ), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("11").and(Bitmap1d<2>("10") ), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("11").and(Bitmap1d<2>("11") ), Bitmap1d<2>("11"));
}

TEST(Bitmap1dTest, TestOr)
{
	EXPECT_EQ( Bitmap1d<2>("00").or(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("00").or(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("00").or(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("00").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ( Bitmap1d<2>("01").or(Bitmap1d<2>("00")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("01").or(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("01").or(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("01").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ( Bitmap1d<2>("10").or(Bitmap1d<2>("00")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("10").or(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("10").or(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("10").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ( Bitmap1d<2>("11").or(Bitmap1d<2>("00")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("11").or(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("11").or(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("11").or(Bitmap1d<2>("11")), Bitmap1d<2>("11"));
}

TEST(Bitmap1dTest, TestXor)
{
	EXPECT_EQ( Bitmap1d<2>("00").xor(Bitmap1d<2>("00")), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("00").xor(Bitmap1d<2>("01")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("00").xor(Bitmap1d<2>("10")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("00").xor(Bitmap1d<2>("11")), Bitmap1d<2>("11"));

	EXPECT_EQ( Bitmap1d<2>("01").xor(Bitmap1d<2>("00")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("01").xor(Bitmap1d<2>("01")), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("01").xor(Bitmap1d<2>("10")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("01").xor(Bitmap1d<2>("11")), Bitmap1d<2>("10"));

	EXPECT_EQ( Bitmap1d<2>("10").xor(Bitmap1d<2>("00")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("10").xor(Bitmap1d<2>("01")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("10").xor(Bitmap1d<2>("10")), Bitmap1d<2>("00"));
	EXPECT_EQ( Bitmap1d<2>("10").xor(Bitmap1d<2>("11")), Bitmap1d<2>("01"));

	EXPECT_EQ( Bitmap1d<2>("11").xor(Bitmap1d<2>("00")), Bitmap1d<2>("11"));
	EXPECT_EQ( Bitmap1d<2>("11").xor(Bitmap1d<2>("01")), Bitmap1d<2>("10"));
	EXPECT_EQ( Bitmap1d<2>("11").xor(Bitmap1d<2>("10")), Bitmap1d<2>("01"));
	EXPECT_EQ( Bitmap1d<2>("11").xor(Bitmap1d<2>("11")), Bitmap1d<2>("00"));
}

TEST(Bitmap1dTest, TestNot)
{
	EXPECT_EQ( Bitmap1d<2>("00").not(), Bitmap1d<2>("11") );
	EXPECT_EQ( Bitmap1d<2>("01").not(), Bitmap1d<2>("10") );
	EXPECT_EQ( Bitmap1d<2>("10").not(), Bitmap1d<2>("01") );
	EXPECT_EQ( Bitmap1d<2>("11").not(), Bitmap1d<2>("00") );
}

TEST(Bitmap1dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAll());
	EXPECT_FALSE(Bitmap1d<2>("01").isAll());
	EXPECT_FALSE(Bitmap1d<2>("10").isAll());
	EXPECT_TRUE( Bitmap1d<2>("11").isAll());
}

TEST(Bitmap1dTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAny());
	EXPECT_TRUE( Bitmap1d<2>("01").isAny());
	EXPECT_TRUE( Bitmap1d<2>("10").isAny());
	EXPECT_TRUE( Bitmap1d<2>("11").isAny());
}

TEST(Bitmap1dTest, TestIsNone)
{
	EXPECT_TRUE( Bitmap1d<2>("00").isNone());
	EXPECT_FALSE(Bitmap1d<2>("01").isNone());
	EXPECT_FALSE(Bitmap1d<2>("10").isNone());
	EXPECT_FALSE(Bitmap1d<2>("11").isNone());
}

TEST(Bitmap1dTest, TestGetEdge)
{
	Bitmap1d<4> bmp("1110");
	Bitmap1d<4> actual = bmp.getEdge();
	Bitmap1d<4> expected("0010");
	EXPECT_EQ(expected, actual);
}