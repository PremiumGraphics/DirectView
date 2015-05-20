#include "gtest/gtest.h"

#include "../Math/Bitmap3d.h"

using namespace Crystal::Math;

TEST(Bitmap3dTest, TestByStrings)
{
	Bitmap3d<2, 2, 2> bitmap;
	const std::array < std::string, 2 > strs =
	{
		"0000",
		"0011"
	};
	bitmap.byStrings(strs);
	
	const Bitmap2d<2, 2> expected1("0000");
	const Bitmap2d<2, 2> expected2("0011");

	EXPECT_EQ( expected1, bitmap[0]);
	EXPECT_EQ( expected2, bitmap[1]);
}

TEST(Bitmap3dTest, TestByString)
{
	{
		Bitmap3d<2, 2, 2> bitmap("00000011");

		const Bitmap2d<2, 2> expected1("0000");
		const Bitmap2d<2, 2> expected2("0011");

		EXPECT_EQ(expected1, bitmap[0]);
		EXPECT_EQ(expected2, bitmap[1]);
	}
}

TEST(Bitmap3dTest, TestByValue)
{
	EXPECT_EQ( Bitmap2x2x2("00000000"), Bitmap2x2x2().byValue(0) );
	EXPECT_EQ( Bitmap2x2x2("01000000"), Bitmap2x2x2().byValue(1) );
	EXPECT_EQ( Bitmap2x2x2("10000000"), Bitmap2x2x2().byValue(2) );
	EXPECT_EQ( Bitmap2x2x2("11000000"), Bitmap2x2x2().byValue(3));

}

TEST(Bitmap3dTest, TestSize)
{
	EXPECT_EQ( Bitmap1x1x1().size(), 1 );
	EXPECT_EQ( Bitmap1x1x2().size(), 2 );
	EXPECT_EQ( Bitmap1x2x4().size(), 8 );
	EXPECT_EQ( Bitmap2x2x2().size(), 8 );
}

TEST(Bitmap3dTest, TestSizeX)
{
	EXPECT_EQ( 1, Bitmap1x2x4().sizex() );
}

TEST(Bitmap3dTest, TestSizeY)
{
	EXPECT_EQ(1, Bitmap1x1x1().sizey());
	EXPECT_EQ(2, Bitmap1x2x4().sizey());
}

TEST(Bitmap3dTest, TestSizeZ)
{
	EXPECT_EQ(1, Bitmap1x1x1().sizez());
	EXPECT_EQ(2, Bitmap1x1x2().sizez());
	EXPECT_EQ(4, Bitmap1x2x4().sizez());
}

TEST(Bitmap3dTest, TestSet)
{
	Bitmap3d<1, 2, 4> bitmap;
	bitmap.set(0, 0, 0);

	EXPECT_TRUE(bitmap.get(0,0,0));

	bitmap.set(0, 1, 0);
	EXPECT_TRUE(bitmap.get(0,1,0));

	bitmap.set(0, 1, 1);
	EXPECT_TRUE(bitmap.get(0,1,1));
}

TEST(Bitmap3dTest, TestReset)
{
	Bitmap3d<2, 2, 2> bitmap;
	bitmap.reset(0, 0, 0);

	EXPECT_FALSE(bitmap.get(0,0,0) );
}

TEST(Bitmap3dTest, TestToString)
{
	Bitmap1x2x4 bitmap;
	EXPECT_EQ("00000000", bitmap.toString());
	bitmap.set(0, 0, 0);
	EXPECT_EQ("10000000", bitmap.toString());
	bitmap.set(0, 0, 1);
	EXPECT_EQ("10100000", bitmap.toString());
	bitmap.set(0, 0, 2);
	EXPECT_EQ("10101000", bitmap.toString());
	bitmap.set(0, 0, 3);
	EXPECT_EQ("10101010", bitmap.toString());
	bitmap.set(0, 1, 0);
	EXPECT_EQ("11101010", bitmap.toString());
	bitmap.set(0, 1, 1);
	EXPECT_EQ("11111010", bitmap.toString());
	bitmap.set(0, 1, 2);
	EXPECT_EQ("11111110", bitmap.toString());
	bitmap.set(0, 1, 3);
	EXPECT_EQ("11111111", bitmap.toString());

	EXPECT_EQ( "10111111", Bitmap1x2x4("10111111").toString() );
	EXPECT_EQ( "10000000", Bitmap1x2x4("10000000").toString() );
	EXPECT_EQ( "11111111", Bitmap1x2x4("11111111").toString() );

	//	bitmap.set(0, 1, 0);
	//	EXPECT_EQ("10010000", bitmap.toString());
	//	bitmap.set(0, 1, 1);
	//	EXPECT_EQ("11110000", bitmap.toString());
	//bitmap.set(1, 0, 0);
	//EXPECT_EQ("10010100", bitmap.toString());
}


TEST(Bitmap3dTest, TestEquals)
{
	EXPECT_TRUE( Bitmap2x2x2().equals( Bitmap2x2x2() ) );
	EXPECT_EQ( Bitmap2x2x2(), Bitmap2x2x2() );
}

TEST(Bitmap3dTest, TestNot)
{
	EXPECT_EQ(Bitmap1x1x2("00").not(), Bitmap1x1x2("11"));
	EXPECT_EQ(Bitmap1x1x2("01").not(), Bitmap1x1x2("10"));
	EXPECT_EQ(Bitmap1x1x2("10").not(), Bitmap1x1x2("01"));
	EXPECT_EQ(Bitmap1x1x2("11").not(), Bitmap1x1x2("00"));
}

TEST(Bitmap3dTest, TestAnd)
{
	EXPECT_EQ( Bitmap1x1x2("00").and(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("00").and(Bitmap1x1x2("01")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("00").and(Bitmap1x1x2("10")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("00").and(Bitmap1x1x2("11")), Bitmap1x1x2("00"));

	EXPECT_EQ( Bitmap1x1x2("01").and(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("01").and(Bitmap1x1x2("01")), Bitmap1x1x2("01"));
	EXPECT_EQ( Bitmap1x1x2("01").and(Bitmap1x1x2("10")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("01").and(Bitmap1x1x2("11")), Bitmap1x1x2("01"));

	EXPECT_EQ( Bitmap1x1x2("10").and(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("10").and(Bitmap1x1x2("01")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("10").and(Bitmap1x1x2("10")), Bitmap1x1x2("10"));
	EXPECT_EQ( Bitmap1x1x2("10").and(Bitmap1x1x2("11")), Bitmap1x1x2("10"));

	EXPECT_EQ( Bitmap1x1x2("11").and(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("11").and(Bitmap1x1x2("01")), Bitmap1x1x2("01"));
	EXPECT_EQ( Bitmap1x1x2("11").and(Bitmap1x1x2("10")), Bitmap1x1x2("10"));
	EXPECT_EQ( Bitmap1x1x2("11").and(Bitmap1x1x2("11")), Bitmap1x1x2("11"));
}

TEST(Bitmap3dTest, TestOr)
{
	EXPECT_EQ( Bitmap1x1x2("00").or(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ( Bitmap1x1x2("00").or(Bitmap1x1x2("01")), Bitmap1x1x2("01"));
	EXPECT_EQ( Bitmap1x1x2("00").or(Bitmap1x1x2("10")), Bitmap1x1x2("10"));
	EXPECT_EQ( Bitmap1x1x2("00").or(Bitmap1x1x2("11")), Bitmap1x1x2("11"));

	EXPECT_EQ( Bitmap1x1x2("01").or(Bitmap1x1x2("00")), Bitmap1x1x2("01"));
	EXPECT_EQ( Bitmap1x1x2("01").or(Bitmap1x1x2("01")), Bitmap1x1x2("01"));
	EXPECT_EQ( Bitmap1x1x2("01").or(Bitmap1x1x2("10")), Bitmap1x1x2("11"));
	EXPECT_EQ( Bitmap1x1x2("01").or(Bitmap1x1x2("11")), Bitmap1x1x2("11"));

	EXPECT_EQ( Bitmap1x1x2("10").or(Bitmap1x1x2("00")), Bitmap1x1x2("10"));
	EXPECT_EQ( Bitmap1x1x2("10").or(Bitmap1x1x2("01")), Bitmap1x1x2("11"));
	EXPECT_EQ( Bitmap1x1x2("10").or(Bitmap1x1x2("10")), Bitmap1x1x2("10"));
	EXPECT_EQ( Bitmap1x1x2("10").or(Bitmap1x1x2("11")), Bitmap1x1x2("11"));

	EXPECT_EQ( Bitmap1x1x2("11").or(Bitmap1x1x2("00")), Bitmap1x1x2("11"));
	EXPECT_EQ( Bitmap1x1x2("11").or(Bitmap1x1x2("01")), Bitmap1x1x2("11"));
	EXPECT_EQ( Bitmap1x1x2("11").or(Bitmap1x1x2("10")), Bitmap1x1x2("11"));
	EXPECT_EQ( Bitmap1x1x2("11").or(Bitmap1x1x2("11")), Bitmap1x1x2("11"));
}

TEST(Bitmap3dTest, TestXor)
{
	EXPECT_EQ(Bitmap1x1x2("00").xor(Bitmap1x1x2("00")), Bitmap1x1x2("00"));
	EXPECT_EQ(Bitmap1x1x2("00").xor(Bitmap1x1x2("01")), Bitmap1x1x2("01"));
	EXPECT_EQ(Bitmap1x1x2("00").xor(Bitmap1x1x2("10")), Bitmap1x1x2("10"));
	EXPECT_EQ(Bitmap1x1x2("00").xor(Bitmap1x1x2("11")), Bitmap1x1x2("11"));

	EXPECT_EQ(Bitmap1x1x2("01").xor(Bitmap1x1x2("00")), Bitmap1x1x2("01"));
	EXPECT_EQ(Bitmap1x1x2("01").xor(Bitmap1x1x2("01")), Bitmap1x1x2("00"));
	EXPECT_EQ(Bitmap1x1x2("01").xor(Bitmap1x1x2("10")), Bitmap1x1x2("11"));
	EXPECT_EQ(Bitmap1x1x2("01").xor(Bitmap1x1x2("11")), Bitmap1x1x2("10"));

	EXPECT_EQ(Bitmap1x1x2("10").xor(Bitmap1x1x2("00")), Bitmap1x1x2("10"));
	EXPECT_EQ(Bitmap1x1x2("10").xor(Bitmap1x1x2("01")), Bitmap1x1x2("11"));
	EXPECT_EQ(Bitmap1x1x2("10").xor(Bitmap1x1x2("10")), Bitmap1x1x2("00"));
	EXPECT_EQ(Bitmap1x1x2("10").xor(Bitmap1x1x2("11")), Bitmap1x1x2("01"));

	EXPECT_EQ(Bitmap1x1x2("11").xor(Bitmap1x1x2("00")), Bitmap1x1x2("11"));
	EXPECT_EQ(Bitmap1x1x2("11").xor(Bitmap1x1x2("01")), Bitmap1x1x2("10"));
	EXPECT_EQ(Bitmap1x1x2("11").xor(Bitmap1x1x2("10")), Bitmap1x1x2("01"));
	EXPECT_EQ(Bitmap1x1x2("11").xor(Bitmap1x1x2("11")), Bitmap1x1x2("00"));
}

TEST(Bitmap3dTest, TestMoveX)
{
	EXPECT_EQ(Bitmap2x2x2("10101010"), Bitmap2x2x2("01010101").movex(1));
	EXPECT_EQ(Bitmap2x2x2("10101010"), Bitmap2x2x2("11111111").movex(1));

	EXPECT_EQ(Bitmap2x2x2("00000000"), Bitmap2x2x2("01010101").movex(2));

	//EXPECT_EQ(Bitmap2x2x2("1010"), Bitmap2x2x2("1101").movex(1));
}

TEST(Bitmap3dTest, TestMoveY)
{
	using Bitmap1x2x1 = Bitmap3d < 1, 2, 1 > ;
	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("00").movedy(1));
	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("01").movedy(1));
	EXPECT_EQ(Bitmap1x2x1("01"), Bitmap1x2x1("10").movedy(1));
	EXPECT_EQ(Bitmap1x2x1("01"), Bitmap1x2x1("11").movedy(1));

	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("00").movedy(2));
	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("01").movedy(2));
	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("10").movedy(2));
	EXPECT_EQ(Bitmap1x2x1("00"), Bitmap1x2x1("11").movedy(2));

}

TEST(Bitmap3dTest, TestMoveZ)
{
	using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 >;
	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("00").movedz(1));
	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("01").movedz(1));
	EXPECT_EQ(Bitmap1x1x2("01"), Bitmap1x1x2("10").movedz(1));
	EXPECT_EQ(Bitmap1x1x2("01"), Bitmap1x1x2("11").movedz(1));

	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("00").movedz(2));
	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("01").movedz(2));
	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("10").movedz(2));
	EXPECT_EQ(Bitmap1x1x2("00"), Bitmap1x1x2("11").movedz(2));

}