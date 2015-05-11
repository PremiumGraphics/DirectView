#include "gtest/gtest.h"

#include "../Math/Bitmap2d.h"

using namespace Crystal::Math;


TEST(Bitmap2dTest, TestConstruct)
{
	const Bitmap2d<1,1> bitmap;
}

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
	EXPECT_TRUE(bitmap.get(1, 1));
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
	{
		const Bitmap2d<1, 1> bitmap;
		EXPECT_EQ(bitmap.size(), 1);
	}
	{
		const Bitmap2d<2, 2> bitmap;
		EXPECT_EQ(bitmap.size(), 4);
	}
}

TEST(Bitmap2dTest, TestSizeX)
{
	{
		const Bitmap2d<1, 2> bitmap;
		EXPECT_EQ(bitmap.sizex(), 1);
	}
	{
		const Bitmap2d<2, 4> bitmap;
		EXPECT_EQ(bitmap.sizex(), 2);
	}
}

TEST(Bitmap2dTest, TestSizeY)
{
	{
		Bitmap2d<1, 2> bitmap;
		EXPECT_EQ(bitmap.sizey(), 2);
	}

	{
		const Bitmap2d<2, 4> bitmap;
		EXPECT_EQ(bitmap.sizey(), 4);
	}
}

TEST(Bitmap2dTest, TestSet)
{
	Bitmap2d<1,2> bitmap;
	bitmap.set(0, 0);
	EXPECT_TRUE( bitmap.get(0,0) );
	bitmap.set(0, 1);
	EXPECT_TRUE( bitmap.get(0,1) );
}

TEST(Bitmap2dTest, TestSetAll)
{
	Bitmap2d<2, 1> bitmap;
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
	Bitmap2d<1, 2> bitmap;
	EXPECT_EQ("00", bitmap.toString());
	bitmap.set(0, 0);
	EXPECT_EQ("10", bitmap.toString());
	bitmap.set(0, 1);
	EXPECT_EQ("11", bitmap.toString());

	/*
	bitmap.set(0, 1);
	EXPECT_EQ("1100", bitmap.toString());
	bitmap.set(1, 0);
	EXPECT_EQ("1101", bitmap.toString());
	bitmap.set(1, 1);
	EXPECT_EQ("1111", bitmap.toString());
	*/
}

TEST(Bitmap2dTest, TestEquals)
{
	Bitmap2d<1, 1> bmp1;
	Bitmap2d<1, 1> bmp2;

	EXPECT_TRUE( bmp1.equals(bmp2) );
	EXPECT_EQ( bmp1, bmp2 );
	bmp1.set(0, 0);
	EXPECT_FALSE(bmp1.equals(bmp2));
	EXPECT_NE( bmp1, bmp2 );
}


TEST(Bitmap2dTest, TestAll)
{
	Bitmap2d<2,2> bitmap;
	bitmap.set(0, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(0, 1);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 0);
	EXPECT_FALSE(bitmap.all());
	bitmap.set(1, 1);
	EXPECT_TRUE( bitmap.all());
}

TEST(Bitmap2dTest, TestNone)
{
	Bitmap2d<2, 2> bitmap;
	bitmap.set();

	EXPECT_FALSE( bitmap.none());
	bitmap.reset(0, 0);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(0, 1);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(1, 0);
	EXPECT_FALSE( bitmap.none());
	bitmap.reset(1, 1);
	EXPECT_TRUE(  bitmap.none());
}

TEST(Bitmap2dTest, TestNot)
{
	using Bitmap1x2 = Bitmap2d < 1, 2 >;

	EXPECT_EQ(Bitmap1x2("00").not(), Bitmap1x2("11"));
	EXPECT_EQ(Bitmap1x2("01").not(), Bitmap1x2("10"));
	EXPECT_EQ(Bitmap1x2("10").not(), Bitmap1x2("01"));
	EXPECT_EQ(Bitmap1x2("11").not(), Bitmap1x2("00"));
}

TEST(Bitmap2dTest, TestAnd)
{
	using Bitmap1x2 = Bitmap2d < 1, 2 >;
	
	EXPECT_EQ(Bitmap1x2("00").and( Bitmap1x2("00") ), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and( Bitmap1x2("01") ), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and( Bitmap1x2("10") ), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and( Bitmap1x2("11") ), Bitmap1x2("00"));

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
	using Bitmap1x2 = Bitmap2d < 1, 2 > ;

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
	using Bitmap1x2 = Bitmap2d < 1, 2 > ;

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