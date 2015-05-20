#include "gtest/gtest.h"

#include "../Math/Bitmap2d.h"

using namespace Crystal::Math;


TEST(Bitmap2dTest, TestConstructByBitmap1ds)
{
	const std::array< Bitmap1d<1>, 1 > bmp1ds;
	const Bitmap2d<1, 1> bitmap( bmp1ds );
}

TEST(Bitmap2dTest, TestByString)
{
	Bitmap2d<2, 2> bitmap;
	bitmap.byString("0111");
	EXPECT_TRUE( bitmap.get(0,0) );
	EXPECT_TRUE( bitmap.get(0,1) );
	EXPECT_FALSE(bitmap.get(1,0) );
	EXPECT_TRUE( bitmap.get(1,1) );
}

TEST(Bitmap2dTest, TestByStrings)
{
	const std::array< std::string, 2 > strs = {
		"01",
		"11"
	};
	Bitmap2d<2, 2> bitmap;
	bitmap.byStrings(strs);
	EXPECT_TRUE(bitmap.get(0, 0));
	EXPECT_TRUE(bitmap.get(0, 1));
	EXPECT_FALSE(bitmap.get(1, 0));
	EXPECT_TRUE(bitmap.get(1, 1));
}

TEST(Bitmap2dTest, TestSize)
{
	EXPECT_EQ( 1, Bitmap1x1().size() );
	EXPECT_EQ( 2, Bitmap1x2().size() );
	EXPECT_EQ( 2, Bitmap2x1().size() );
	EXPECT_EQ( 4, Bitmap2x2().size() );
}

TEST(Bitmap2dTest, TestByValues)
{
	const std::array<unsigned long, 2 > v = { 0, 0 };
	EXPECT_EQ( Bitmap2x2("0000"), Bitmap2x2().byValues(v) );
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


TEST(Bitmap2dTest, TestSizeX)
{
	EXPECT_EQ( 1, Bitmap1x1().sizex() );
	EXPECT_EQ( 1, Bitmap1x2().sizex() );
	EXPECT_EQ( 2, Bitmap2x1().sizex() );
	EXPECT_EQ( 2, Bitmap2x2().sizex() );
}

TEST(Bitmap2dTest, TestSizeY)
{
	EXPECT_EQ( 1, Bitmap1x1().sizey() );
	EXPECT_EQ( 2, Bitmap1x2().sizey() );
	EXPECT_EQ( 1, Bitmap2x1().sizey() );
	EXPECT_EQ( 2, Bitmap2x2().sizey() );
}

TEST(Bitmap2dTest, TestSet)
{
	Bitmap1x2 bitmap;
	bitmap.set(0, 0);
	EXPECT_TRUE( bitmap.get(0,0) );
	bitmap.set(0, 1);
	EXPECT_TRUE( bitmap.get(0,1) );
}

TEST(Bitmap2dTest, TestSetAll)
{
	Bitmap2x1 bitmap;
	bitmap.set();

	EXPECT_TRUE(bitmap.get(0,0));
	EXPECT_TRUE(bitmap.get(1,0));
}

TEST(Bitmap2dTest, TestSet1d)
{
	Bitmap2d<2, 2> bitmap;
	bitmap.set(0, Bitmap1d<2>("01"));
	EXPECT_TRUE( bitmap.get(0,0));
	EXPECT_FALSE(bitmap.get(0,1));
}

TEST(Bitmap2dTest, TestReset)
{
	Bitmap2d<1,1> bitmap;
	bitmap.set(0, 0);
	bitmap.reset(0, 0);

	EXPECT_FALSE(bitmap.get(0,0));
}

TEST(Bitmap2dTest, TestResetAll)
{
	Bitmap2d<1, 2> bitmap;
	bitmap.set();
	bitmap.reset();

	EXPECT_FALSE(bitmap.get(0,0));
	EXPECT_FALSE(bitmap.get(0,1));
}

TEST(Bitmap2dTest, TestToString)
{
	EXPECT_EQ( "0000", Bitmap2x2("0000").toString() );
	EXPECT_EQ( "0001", Bitmap2x2("0001").toString() );
	EXPECT_EQ( "0010", Bitmap2x2("0010").toString() );
	EXPECT_EQ( "0011", Bitmap2x2("0011").toString() );
}

TEST(Bitmap2dTest, TestEquals)
{
	EXPECT_TRUE( Bitmap1x1().equals( Bitmap1x1() ) );
	EXPECT_EQ( Bitmap1x1(), Bitmap1x1() );

	EXPECT_FALSE(Bitmap1x1("1").equals(Bitmap1x1()));
	EXPECT_NE(Bitmap1x1("1"), Bitmap1x1() );
}

TEST(Bitmap2dTest, TestIsAll)
{
	EXPECT_FALSE( Bitmap1x2("00").isAll() );
	EXPECT_FALSE( Bitmap1x2("01").isAll() );
	EXPECT_FALSE( Bitmap1x2("10").isAll() );
	EXPECT_TRUE ( Bitmap1x2("11").isAll() );
}

TEST(Bitmap2dTest, TestIsNone)
{
	EXPECT_TRUE ( Bitmap2x2("0000").isNone() );
	EXPECT_FALSE( Bitmap2x2("0001").isNone() );
	EXPECT_FALSE( Bitmap2x2("0010").isNone() );
	EXPECT_FALSE( Bitmap2x2("0100").isNone() );
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
	EXPECT_EQ( Bitmap1x2("00").and( Bitmap1x2("00") ), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("00").and( Bitmap1x2("01") ), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("00").and( Bitmap1x2("10") ), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("00").and( Bitmap1x2("11") ), Bitmap1x2("00"));

	EXPECT_EQ( Bitmap1x2("01").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("01").and(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ( Bitmap1x2("01").and(Bitmap1x2("10")), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("01").and(Bitmap1x2("11")), Bitmap1x2("01"));

	EXPECT_EQ( Bitmap1x2("10").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("10").and(Bitmap1x2("01")), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("10").and(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ( Bitmap1x2("10").and(Bitmap1x2("11")), Bitmap1x2("10"));

	EXPECT_EQ( Bitmap1x2("11").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ( Bitmap1x2("11").and(Bitmap1x2("01")), Bitmap1x2("01"));
	EXPECT_EQ( Bitmap1x2("11").and(Bitmap1x2("10")), Bitmap1x2("10"));
	EXPECT_EQ( Bitmap1x2("11").and(Bitmap1x2("11")), Bitmap1x2("11"));
}

TEST(Bitmap2dTest, TestOr)
{
	EXPECT_EQ( Bitmap1x2("00").or(Bitmap1x2("00")), Bitmap1x2("00") );
	EXPECT_EQ( Bitmap1x2("00").or(Bitmap1x2("01")), Bitmap1x2("01") );
	EXPECT_EQ( Bitmap1x2("00").or(Bitmap1x2("10")), Bitmap1x2("10") );
	EXPECT_EQ( Bitmap1x2("00").or(Bitmap1x2("11")), Bitmap1x2("11") );

	EXPECT_EQ( Bitmap1x2("01").or(Bitmap1x2("00")), Bitmap1x2("01") );
	EXPECT_EQ( Bitmap1x2("01").or(Bitmap1x2("01")), Bitmap1x2("01") );
	EXPECT_EQ( Bitmap1x2("01").or(Bitmap1x2("10")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("01").or(Bitmap1x2("11")), Bitmap1x2("11") );

	EXPECT_EQ( Bitmap1x2("10").or(Bitmap1x2("00")), Bitmap1x2("10") );
	EXPECT_EQ( Bitmap1x2("10").or(Bitmap1x2("01")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("10").or(Bitmap1x2("10")), Bitmap1x2("10") );
	EXPECT_EQ( Bitmap1x2("10").or(Bitmap1x2("11")), Bitmap1x2("11") );

	EXPECT_EQ( Bitmap1x2("11").or(Bitmap1x2("00")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("11").or(Bitmap1x2("01")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("11").or(Bitmap1x2("10")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("11").or(Bitmap1x2("11")), Bitmap1x2("11") );
}

TEST(Bitmap2dTest, TestXor)
{
	EXPECT_EQ( Bitmap1x2("00").xor(Bitmap1x2("00")), Bitmap1x2("00") );
	EXPECT_EQ( Bitmap1x2("00").xor(Bitmap1x2("01")), Bitmap1x2("01") );
	EXPECT_EQ( Bitmap1x2("00").xor(Bitmap1x2("10")), Bitmap1x2("10") );
	EXPECT_EQ( Bitmap1x2("00").xor(Bitmap1x2("11")), Bitmap1x2("11") );

	EXPECT_EQ( Bitmap1x2("01").xor(Bitmap1x2("00")), Bitmap1x2("01") );
	EXPECT_EQ( Bitmap1x2("01").xor(Bitmap1x2("01")), Bitmap1x2("00") );
	EXPECT_EQ( Bitmap1x2("01").xor(Bitmap1x2("10")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("01").xor(Bitmap1x2("11")), Bitmap1x2("10") );

	EXPECT_EQ( Bitmap1x2("10").xor(Bitmap1x2("00")), Bitmap1x2("10") );
	EXPECT_EQ( Bitmap1x2("10").xor(Bitmap1x2("01")), Bitmap1x2("11") );
	EXPECT_EQ( Bitmap1x2("10").xor(Bitmap1x2("10")), Bitmap1x2("00") );
	EXPECT_EQ( Bitmap1x2("10").xor(Bitmap1x2("11")), Bitmap1x2("01") );
}

TEST(Bitmap2dTest, TestSubdivX)
{
	EXPECT_EQ( Bitmap2x1("00"), Bitmap1x1("0").subdivx() );
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