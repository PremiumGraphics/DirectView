#include "gtest/gtest.h"

#include "../Math/Bitmap3d.h"

using namespace Crystal::Math;

TEST(Bitmap3dTest, TestConstruct)
{
	Bitmap3d<1, 1, 1> bitmap;
	EXPECT_EQ( bitmap.size(), 1);
}
/*
TEST(Bitmap3dTest, TestByBitmap2ds)
{
}
*/

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

	using Bitmap124 = Bitmap3d < 1, 2, 4 > ;
	{
		Bitmap124 bitmap("00000011");

	}
}


/*
TEST(Bitmap3dTest, TestByStrings2)
{
}
*/

TEST(Bitmap3dTest, TestSize)
{
	Bitmap3d<2, 2, 2> bitmap;
 	EXPECT_EQ( bitmap.size(), 8);
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
	Bitmap3d<1, 2, 4> bitmap;
	const auto actual = bitmap.sizez();
	EXPECT_EQ(actual, 4);
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

/*
TEST(Bitmap3dTest, TestToString)
{
	Bitmap3d<1, 2, 4> bitmap;
	EXPECT_EQ("00000000", bitmap.toString());
	bitmap.set(0, 0, 0);
	EXPECT_EQ("10000000", bitmap.toString());
	bitmap.set(0, 1, 0);
	EXPECT_EQ("11000000", bitmap.toString());
	bitmap.set(1, 0, 0);
	EXPECT_EQ("11100000", bitmap.toString());
	bitmap.set(1, 1, 0);
	EXPECT_EQ("11110000", bitmap.toString());
	bitmap.set(2, 0, 0);
	EXPECT_EQ("11111000", bitmap.toString());
	bitmap.set(2, 1, 0);
	EXPECT_EQ("11111100", bitmap.toString());

//	bitmap.set(0, 1, 0);
//	EXPECT_EQ("10010000", bitmap.toString());
//	bitmap.set(0, 1, 1);
//	EXPECT_EQ("11110000", bitmap.toString());
	//bitmap.set(1, 0, 0);
	//EXPECT_EQ("10010100", bitmap.toString());
}
*/

TEST(Bitmap3dTest, TestToString)
{
	Bitmap3d<1, 2, 4> bitmap;
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


	//	bitmap.set(0, 1, 0);
	//	EXPECT_EQ("10010000", bitmap.toString());
	//	bitmap.set(0, 1, 1);
	//	EXPECT_EQ("11110000", bitmap.toString());
	//bitmap.set(1, 0, 0);
	//EXPECT_EQ("10010100", bitmap.toString());
}


TEST(Bitmap3dTest, TestEquals)
{
	Bitmap3d<2, 2, 2> bmp1;
	Bitmap3d<2, 2, 2> bmp2;

	EXPECT_TRUE(bmp1.equals(bmp2));
	bmp1.set(0, 0, 0);
	EXPECT_FALSE(bmp1.equals(bmp2));
}

TEST(Bitmap3dTest, TestNot)
{
	using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 > ;

	EXPECT_EQ(Bitmap1x1x2("00").not(), Bitmap1x1x2("11"));
	EXPECT_EQ(Bitmap1x1x2("01").not(), Bitmap1x1x2("10"));
	EXPECT_EQ(Bitmap1x1x2("10").not(), Bitmap1x1x2("01"));
	EXPECT_EQ(Bitmap1x1x2("11").not(), Bitmap1x1x2("00"));
}

TEST(Bitmap3dTest, TestAnd)
{
	using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 > ;

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
	using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 > ;

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
	using Bitmap1x1x2 = Bitmap3d < 1, 1, 2 >;

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