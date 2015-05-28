#include "gtest/gtest.h"

#include "../Math/Bitmap.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestGet)
{
	EXPECT_FALSE(Bitmap1d<1>().get(0));
}

TEST(Bitmap1dTest, TestSet)
{
	EXPECT_TRUE(Bitmap1d<1>().set(0).get(0));
	EXPECT_TRUE(Bitmap1d<2>().set().get(0));
	EXPECT_TRUE(Bitmap1d<2>().set().get(1));
}

TEST(Bitmap1dTest, TestToULong)
{
	EXPECT_EQ(0, Bitmap1d<2>("00").toULong());
	EXPECT_EQ(1, Bitmap1d<2>("01").toULong());
	EXPECT_EQ(2, Bitmap1d<2>("10").toULong());
	EXPECT_EQ(3, Bitmap1d<2>("11").toULong());
}

TEST(Bitmap1dTest, TestToString)
{
	EXPECT_EQ("00", Bitmap1d<2>("00").toString());
	EXPECT_EQ("01", Bitmap1d<2>("01").toString());
	EXPECT_EQ("10", Bitmap1d<2>("10").toString());
	EXPECT_EQ("11", Bitmap1d<2>("11").toString());
}

TEST(Bitmap1dTest, TestConstructByString)
{
	Bitmap1d<4> bitmap("1001");
	EXPECT_TRUE(bitmap.get(0));
	EXPECT_FALSE(bitmap.get(1));
}

TEST(Bitmap1dTest, TestConstructByLong)
{
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>(0));
	EXPECT_EQ(Bitmap1d<2>("01"), Bitmap1d<2>(1));
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>(2));
	EXPECT_EQ(Bitmap1d<2>("11"), Bitmap1d<2>(3));
}


TEST(Bitmap1dTest, TestResetAll)
{
	Bitmap1d<2> bitmap;
	bitmap.set();
	bitmap.reset();
	EXPECT_FALSE(bitmap.get(0));
	EXPECT_FALSE(bitmap.get(1));
}

TEST(Bitmap1dTest, TestGetCount)
{
	EXPECT_EQ(0, Bitmap1d<2>("00").getCount());
	EXPECT_EQ(1, Bitmap1d<2>("01").getCount());
	EXPECT_EQ(1, Bitmap1d<2>("10").getCount());
	EXPECT_EQ(2, Bitmap1d<2>("11").getCount());
}

TEST(Bitmap1dTest, TestAnd)
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

TEST(Bitmap1dTest, TestOr)
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

TEST(Bitmap1dTest, TestXor)
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

TEST(Bitmap1dTest, TestNot)
{
	EXPECT_EQ(Bitmap1d<2>("00").not(), Bitmap1d<2>("11"));
	EXPECT_EQ(Bitmap1d<2>("01").not(), Bitmap1d<2>("10"));
	EXPECT_EQ(Bitmap1d<2>("10").not(), Bitmap1d<2>("01"));
	EXPECT_EQ(Bitmap1d<2>("11").not(), Bitmap1d<2>("00"));
}

TEST(Bitmap1dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAll());
	EXPECT_FALSE(Bitmap1d<2>("01").isAll());
	EXPECT_FALSE(Bitmap1d<2>("10").isAll());
	EXPECT_TRUE(Bitmap1d<2>("11").isAll());
}

TEST(Bitmap1dTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap1d<2>("00").isAny());
	EXPECT_TRUE(Bitmap1d<2>("01").isAny());
	EXPECT_TRUE(Bitmap1d<2>("10").isAny());
	EXPECT_TRUE(Bitmap1d<2>("11").isAny());
}

TEST(Bitmap1dTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap1d<2>("00").isNone());
	EXPECT_FALSE(Bitmap1d<2>("01").isNone());
	EXPECT_FALSE(Bitmap1d<2>("10").isNone());
	EXPECT_FALSE(Bitmap1d<2>("11").isNone());
}

TEST(Bitmap1dTest, TestMoveX)
{
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>("00").movex(1) );
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>("01").movex(1) );
	EXPECT_EQ(Bitmap1d<2>("00"), Bitmap1d<2>("10").movex(1) );
	EXPECT_EQ(Bitmap1d<2>("10"), Bitmap1d<2>("11").movex(1) );
}


TEST(Bitmap2dTest, TestGetTotalSize)
{
	EXPECT_EQ(1, Bitmap2d<1>(1).getTotalSize());
	EXPECT_EQ(2, Bitmap2d<1>(2).getTotalSize());
	EXPECT_EQ(2, Bitmap2d<2>(1).getTotalSize());
	EXPECT_EQ(4, Bitmap2d<2>(2).getTotalSize());
}


TEST(Bitmap2dTest, TestGetSizeX)
{
	EXPECT_EQ(1, Bitmap2d<1>(1).getSizeX());
	EXPECT_EQ(1, Bitmap2d<1>(2).getSizeX());
	EXPECT_EQ(2, Bitmap2d<2>(1).getSizeX());
	EXPECT_EQ(2, Bitmap2d<2>(2).getSizeX());
}

TEST(Bitmap2dTest, TestGetSizeY)
{
	EXPECT_EQ(1, Bitmap2d<1>(1).getSizeY());
	EXPECT_EQ(2, Bitmap2d<1>(2).getSizeY());
	EXPECT_EQ(1, Bitmap2d<2>(1).getSizeY());
	EXPECT_EQ(2, Bitmap2d<2>(2).getSizeY());
}

TEST(Bitmap2dTest, TestGet)
{
	EXPECT_FALSE(Bitmap2d<1>(1).get(0, 0));
	EXPECT_FALSE(Bitmap2d<1>(2).get(1, 0));
	EXPECT_FALSE(Bitmap2d<2>(1).get(0, 1));

}

/*
TEST(Bitmap2dTest, TestByValues)
{
	const std::array<unsigned long, 2 > v = { 0, 0 };
	EXPECT_EQ(Bitmap2x2("0000"), Bitmap2x2().byValues(v));
}

TEST(Bitmap2dTest, TestByValue)
{
	EXPECT_EQ(Bitmap2x2("0000"), Bitmap2x2().byValue(0));
	EXPECT_EQ(Bitmap2x2("0100"), Bitmap2x2().byValue(1));
	EXPECT_EQ(Bitmap2x2("1000"), Bitmap2x2().byValue(2));
	EXPECT_EQ(Bitmap2x2("1100"), Bitmap2x2().byValue(3));

	EXPECT_EQ(Bitmap2x2("0001"), Bitmap2x2().byValue(4));
	EXPECT_EQ(Bitmap2x2("0101"), Bitmap2x2().byValue(5));
	EXPECT_EQ(Bitmap2x2("1001"), Bitmap2x2().byValue(6));


	EXPECT_TRUE(Bitmap2x2().byValue(1).get(0, 0));
}


TEST(Bitmap2dTest, TestSet)
{
	Bitmap1x2 bitmap;
	bitmap.set(0, 0);
	EXPECT_TRUE(bitmap.get(0, 0));
	bitmap.set(0, 1);
	EXPECT_TRUE(bitmap.get(0, 1));
}

TEST(Bitmap2dTest, TestSetAll)
{
	Bitmap2x1 bitmap;
	bitmap.set();

	EXPECT_TRUE(bitmap.get(0, 0));
	EXPECT_TRUE(bitmap.get(1, 0));
}

TEST(Bitmap2dTest, TestSet1d)
{
	Bitmap2d<2, 2> bitmap;
	bitmap.set(0, Bitmap1d<2>("01"));
	EXPECT_TRUE(bitmap.get(0, 0));
	EXPECT_FALSE(bitmap.get(0, 1));
}

TEST(Bitmap2dTest, TestReset)
{
	Bitmap2d<1, 1> bitmap;
	bitmap.set(0, 0);
	bitmap.reset(0, 0);

	EXPECT_FALSE(bitmap.get(0, 0));
}

TEST(Bitmap2dTest, TestResetAll)
{
	Bitmap2d<1, 2> bitmap;
	bitmap.set();
	bitmap.reset();

	EXPECT_FALSE(bitmap.get(0, 0));
	EXPECT_FALSE(bitmap.get(0, 1));
}

TEST(Bitmap2dTest, TestToString)
{
	EXPECT_EQ("0000", Bitmap2x2("0000").toString());
	EXPECT_EQ("0001", Bitmap2x2("0001").toString());
	EXPECT_EQ("0010", Bitmap2x2("0010").toString());
	EXPECT_EQ("0011", Bitmap2x2("0011").toString());
}

TEST(Bitmap2dTest, TestToULong)
{
	EXPECT_EQ(0, Bitmap2x2("0000").toULong());
	EXPECT_EQ(1, Bitmap2x2("0001").toULong());
	EXPECT_EQ(2, Bitmap2x2("0010").toULong());
	//EXPECT_EQ( 3, Bitmap2x2("0100").toULong());
	//EXPECT_EQ( 4, Bitmap2x2("0101").toULong());
	//EXPECT_EQ( 8, Bitmap2x2("1000").toULong());
}


TEST(Bitmap2dTest, TestEquals)
{
	EXPECT_TRUE(Bitmap1x1().equals(Bitmap1x1()));
	EXPECT_EQ(Bitmap1x1(), Bitmap1x1());

	EXPECT_FALSE(Bitmap1x1("1").equals(Bitmap1x1()));
	EXPECT_NE(Bitmap1x1("1"), Bitmap1x1());
}

TEST(Bitmap2dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1x2("00").isAll());
	EXPECT_FALSE(Bitmap1x2("01").isAll());
	EXPECT_FALSE(Bitmap1x2("10").isAll());
	EXPECT_TRUE(Bitmap1x2("11").isAll());
}

TEST(Bitmap2dTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap2x2("0000").isNone());
	EXPECT_FALSE(Bitmap2x2("0001").isNone());
	EXPECT_FALSE(Bitmap2x2("0010").isNone());
	EXPECT_FALSE(Bitmap2x2("0100").isNone());
}

TEST(Bitmap2dTest, TestNot)
{
	EXPECT_EQ(Bitmap1x2("00").not(), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("01").not(), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").not(), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("11").not(), Bitmap1x2("00"));
}

TEST(Bitmap2dTest, TestAnd)
{
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2("01")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2("10")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2("11")), Bitmap1x2("00"));

	EXPECT_EQ(Bitmap1x2("01").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("01").and(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("01").and(Bitmap1x2("10")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("01").and(Bitmap1x2("11")), Bitmap1x2("01"));

	EXPECT_EQ(Bitmap1x2("10").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("10").and(Bitmap1x2("01")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("10").and(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").and(Bitmap1x2("11")), Bitmap1x2("10"));

	EXPECT_EQ(Bitmap1x2("11").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("11").and(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("11").and(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("11").and(Bitmap1x2("11")), Bitmap1x2("11"));
}

TEST(Bitmap2dTest, TestOr)
{
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2("11")), Bitmap1x2("11"));

	EXPECT_EQ(Bitmap1x2("01").or(Bitmap1x2("00")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("01").or(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("01").or(Bitmap1x2("10")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("01").or(Bitmap1x2("11")), Bitmap1x2("11"));

	EXPECT_EQ(Bitmap1x2("10").or(Bitmap1x2("00")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").or(Bitmap1x2("01")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("10").or(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").or(Bitmap1x2("11")), Bitmap1x2("11"));

	EXPECT_EQ(Bitmap1x2("11").or(Bitmap1x2("00")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("11").or(Bitmap1x2("01")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("11").or(Bitmap1x2("10")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("11").or(Bitmap1x2("11")), Bitmap1x2("11"));
}

TEST(Bitmap2dTest, TestXor)
{
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2("11")), Bitmap1x2("11"));

	EXPECT_EQ(Bitmap1x2("01").xor(Bitmap1x2("00")), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("01").xor(Bitmap1x2("01")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("01").xor(Bitmap1x2("10")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("01").xor(Bitmap1x2("11")), Bitmap1x2("10"));

	EXPECT_EQ(Bitmap1x2("10").xor(Bitmap1x2("00")), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").xor(Bitmap1x2("01")), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("10").xor(Bitmap1x2("10")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("10").xor(Bitmap1x2("11")), Bitmap1x2("01"));
}

TEST(Bitmap2dTest, TestSubdivX)
{
	EXPECT_EQ(Bitmap2x1("00"), Bitmap1x1("0").subdivx());
}

TEST(Bitmap2dTest, TestGetEdgesX)
{
	{
		Bitmap1dArray<2, 2> bmps = {
			Bitmap1d<2>("00"),
			Bitmap1d<2>("00")
		};
		Bitmap2d<2, 2> b(bmps);
		const auto actual = b.getEdgesx();
		EXPECT_EQ(Bitmap2x2("0000"), actual);
	}

	{
		Bitmap1dArray<2, 2> bmps = {
			Bitmap1d<2>("01"),
			Bitmap1d<2>("00")
		};
		Bitmap2d<2, 2> b(bmps);
		const auto actual = b.getEdgesx();
		EXPECT_EQ(Bitmap2x2("0001"), actual);
	}

}

TEST(Bitmap2dTest, TestMoveX)
{
	EXPECT_EQ(Bitmap2x2("1010"), Bitmap2x2("0101").movex(1));
	EXPECT_EQ(Bitmap2x2("1010"), Bitmap2x2("1101").movex(1));

	EXPECT_EQ(Bitmap2x2("0000"), Bitmap2x2("1010").movex(1));
	EXPECT_EQ(Bitmap2x2("0010"), Bitmap2x2("0001").movex(1));

	EXPECT_EQ(Bitmap2x2("0000"), Bitmap2x2("0101").movex(2));
}

TEST(Bitmap2dTest, TestMoveY)
{
	EXPECT_EQ(Bitmap2x2("0001"), Bitmap2x2("0101").movey(1));
	EXPECT_EQ(Bitmap2x2("0000"), Bitmap2x2("0001").movey(1));
	EXPECT_EQ(Bitmap2x2("0011"), Bitmap2x2("1100").movey(1));


	//EXPECT_EQ(Bitmap2x2("1100"), Bitmap2x2("0011").movey(1));
}
*/

TEST(Bitmap3dTest, TestTo8Bits)
{

}