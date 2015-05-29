#include "gtest/gtest.h"

#include "../Math/Bitmap.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestGet)
{
	EXPECT_FALSE(Bitmap1d(1)[0]);
}

/*
TEST(Bitmap1dTest, TestSet)
{
	EXPECT_TRUE(Bitmap1d(1).set(0).get(0));
	EXPECT_TRUE(Bitmap1d().set().get(0));
	EXPECT_TRUE(Bitmap1d().set().get(1));
}


TEST(Bitmap1dTest, TestResetAll)
{
	Bitmap1d bitmap(2);
	bitmap.set();
	bitmap.reset();
	EXPECT_FALSE(bitmap[0]);
	EXPECT_FALSE(bitmap[1]);
}

TEST(Bitmap1dTest, TestGetCount)
{
	EXPECT_EQ(0, Bitmap1d("00").getCount());
	EXPECT_EQ(1, Bitmap1d({0,1}).getCount());
	EXPECT_EQ(1, Bitmap1d({1,0}).getCount());
	EXPECT_EQ(2, Bitmap1d({1,1}).getCount());
}
*/


TEST(Bitmap1dTest, TestAnd)
{
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({0,0}).and(Bitmap1d({1,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,0}).and(Bitmap1d({1,1})), Bitmap1d({0,0}));

	EXPECT_EQ(Bitmap1d({0,1}).and(Bitmap1d({0,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,1}).and(Bitmap1d({0,1})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,1}).and(Bitmap1d({1,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,1}).and(Bitmap1d({1,1})), Bitmap1d({0,1}));

	EXPECT_EQ(Bitmap1d({1,0}).and(Bitmap1d({0,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({1,0}).and(Bitmap1d({0,1})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({1,0}).and(Bitmap1d({1,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,0}).and(Bitmap1d({1,1})), Bitmap1d({1,0}));

	EXPECT_EQ(Bitmap1d({1,1}).and(Bitmap1d({0,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({1,1}).and(Bitmap1d({0,1})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({1,1}).and(Bitmap1d({1,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,1}).and(Bitmap1d({1,1})), Bitmap1d({1,1}));
}


TEST(Bitmap1dTest, TestOr)
{
	EXPECT_EQ(Bitmap1d({0,0}).or(Bitmap1d({0,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,0}).or(Bitmap1d({0,1})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,0}).or(Bitmap1d({1,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({0,0}).or(Bitmap1d({1,1})), Bitmap1d({1,1}));

	EXPECT_EQ(Bitmap1d({0,1}).or(Bitmap1d({0,0})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,1}).or(Bitmap1d({0,1})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,1}).or(Bitmap1d({1,0})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({0,1}).or(Bitmap1d({1,1})), Bitmap1d({1,1}));

	EXPECT_EQ(Bitmap1d({1,0}).or(Bitmap1d({0,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,0}).or(Bitmap1d({0,1})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,0}).or(Bitmap1d({1,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,0}).or(Bitmap1d({1,1})), Bitmap1d({1,1}));

	EXPECT_EQ(Bitmap1d({1,1}).or(Bitmap1d({0,0})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,1}).or(Bitmap1d({0,1})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,1}).or(Bitmap1d({1,0})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,1}).or(Bitmap1d({1,1})), Bitmap1d({1,1}));
}

TEST(Bitmap1dTest, TestXor)
{
	EXPECT_EQ(Bitmap1d({0,0}).xor(Bitmap1d({0,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,0}).xor(Bitmap1d({0,1})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,0}).xor(Bitmap1d({1,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({0,0}).xor(Bitmap1d({1,1})), Bitmap1d({1,1}));

	EXPECT_EQ(Bitmap1d({0,1}).xor(Bitmap1d({0,0})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({0,1}).xor(Bitmap1d({0,1})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({0,1}).xor(Bitmap1d({1,0})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({0,1}).xor(Bitmap1d({1,1})), Bitmap1d({1,0}));

	EXPECT_EQ(Bitmap1d({1,0}).xor(Bitmap1d({0,0})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,0}).xor(Bitmap1d({0,1})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,0}).xor(Bitmap1d({1,0})), Bitmap1d({0,0}));
	EXPECT_EQ(Bitmap1d({1,0}).xor(Bitmap1d({1,1})), Bitmap1d({0,1}));

	EXPECT_EQ(Bitmap1d({1,1}).xor(Bitmap1d({0,0})), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({1,1}).xor(Bitmap1d({0,1})), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,1}).xor(Bitmap1d({1,0})), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({1,1}).xor(Bitmap1d({1,1})), Bitmap1d({0,0}));
}

TEST(Bitmap1dTest, TestNot)
{
	EXPECT_EQ(Bitmap1d({0,0}).not(), Bitmap1d({1,1}));
	EXPECT_EQ(Bitmap1d({0,1}).not(), Bitmap1d({1,0}));
	EXPECT_EQ(Bitmap1d({1,0}).not(), Bitmap1d({0,1}));
	EXPECT_EQ(Bitmap1d({1,1}).not(), Bitmap1d({0,0}));
}
/*

TEST(Bitmap1dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1d({0,0}).isAll());
	EXPECT_FALSE(Bitmap1d({0,1}).isAll());
	EXPECT_FALSE(Bitmap1d({1,0}).isAll());
	EXPECT_TRUE(Bitmap1d({1,1}).isAll());
}

TEST(Bitmap1dTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap1d({0,0}).isAny());
	EXPECT_TRUE(Bitmap1d({0,1}).isAny());
	EXPECT_TRUE(Bitmap1d({1,0}).isAny());
	EXPECT_TRUE(Bitmap1d({1,1}).isAny());
}

TEST(Bitmap1dTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap1d({0,0}).isNone());
	EXPECT_FALSE(Bitmap1d({0,1}).isNone());
	EXPECT_FALSE(Bitmap1d({1,0}).isNone());
	EXPECT_FALSE(Bitmap1d({1,1}).isNone());
}

TEST(Bitmap1dTest, TestMoveX)
{
	EXPECT_EQ(Bitmap1d({0,0}), Bitmap1d({0,0}).movex(1) );
	EXPECT_EQ(Bitmap1d({1,0}), Bitmap1d({0,1}).movex(1) );
	EXPECT_EQ(Bitmap1d({0,0}), Bitmap1d({1,0}).movex(1) );
	EXPECT_EQ(Bitmap1d({1,0}), Bitmap1d({1,1}).movex(1) );
}
*/



TEST(Bitmap2dTest, TestGetSizeX)
{
	EXPECT_EQ(1, Bitmap2d(1,1).getSizeX());
	EXPECT_EQ(1, Bitmap2d(1,2).getSizeX());
	EXPECT_EQ(2, Bitmap2d(2,1).getSizeX());
	EXPECT_EQ(2, Bitmap2d(2,2).getSizeX());
}

TEST(Bitmap2dTest, TestGetSizeY)
{
	EXPECT_EQ(1, Bitmap2d(1,1).getSizeY());
	EXPECT_EQ(2, Bitmap2d(1,2).getSizeY());
	EXPECT_EQ(1, Bitmap2d(2,1).getSizeY());
	EXPECT_EQ(2, Bitmap2d(2,2).getSizeY());
}

/*

TEST(Bitmap2dTest, TestGet)
{
	EXPECT_FALSE(Bitmap2d<1>(1).get(0, 0));
	EXPECT_FALSE(Bitmap2d<1>(2).get(1, 0));
	EXPECT_FALSE(Bitmap2d<2>(1).get(0, 1));

}

TEST(Bitmap2dTest, TestByString)
{
	Bitmap2d<2> bitmap;
	bitmap.byString("0111",2);
	EXPECT_TRUE(bitmap.get(0, 0));
	EXPECT_FALSE(bitmap.get(0, 1));
	EXPECT_TRUE(bitmap.get(1, 0));
	EXPECT_TRUE(bitmap.get(1, 1));
}


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
	bitmap.set(0, Bitmap1d({0,1}));
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
	EXPECT_FALSE(Bitmap1x2({0,1}).isAll());
	EXPECT_FALSE(Bitmap1x2({1,0}).isAll());
	EXPECT_TRUE(Bitmap1x2({1,1}).isAll());
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
	EXPECT_EQ(Bitmap1x2("00").not(), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).not(), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,0}).not(), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({1,1}).not(), Bitmap1x2("00"));
}

TEST(Bitmap2dTest, TestAnd)
{
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2({0,1})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2({1,0})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").and(Bitmap1x2({1,1})), Bitmap1x2("00"));

	EXPECT_EQ(Bitmap1x2({0,1}).and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({0,1}).and(Bitmap1x2({0,1})), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).and(Bitmap1x2({1,0})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({0,1}).and(Bitmap1x2({1,1})), Bitmap1x2({0,1}));

	EXPECT_EQ(Bitmap1x2({1,0}).and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({1,0}).and(Bitmap1x2({0,1})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({1,0}).and(Bitmap1x2({1,0})), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,0}).and(Bitmap1x2({1,1})), Bitmap1x2({1,0}));

	EXPECT_EQ(Bitmap1x2({1,1}).and(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({1,1}).and(Bitmap1x2({0,1})), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({1,1}).and(Bitmap1x2({1,0})), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,1}).and(Bitmap1x2({1,1})), Bitmap1x2({1,1}));
}

TEST(Bitmap2dTest, TestOr)
{
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2({0,1})), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2({1,0})), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2("00").or(Bitmap1x2({1,1})), Bitmap1x2({1,1}));

	EXPECT_EQ(Bitmap1x2({0,1}).or(Bitmap1x2("00")), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).or(Bitmap1x2({0,1})), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).or(Bitmap1x2({1,0})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).or(Bitmap1x2({1,1})), Bitmap1x2({1,1}));

	EXPECT_EQ(Bitmap1x2({1,0}).or(Bitmap1x2("00")), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,0}).or(Bitmap1x2({0,1})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({1,0}).or(Bitmap1x2({1,0})), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,0}).or(Bitmap1x2({1,1})), Bitmap1x2({1,1}));

	EXPECT_EQ(Bitmap1x2({1,1}).or(Bitmap1x2("00")), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({1,1}).or(Bitmap1x2({0,1})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({1,1}).or(Bitmap1x2({1,0})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({1,1}).or(Bitmap1x2({1,1})), Bitmap1x2({1,1}));
}

TEST(Bitmap2dTest, TestXor)
{
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2("00")), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2({0,1})), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2({1,0})), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2("00").xor(Bitmap1x2({1,1})), Bitmap1x2({1,1}));

	EXPECT_EQ(Bitmap1x2({0,1}).xor(Bitmap1x2("00")), Bitmap1x2({0,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).xor(Bitmap1x2({0,1})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({0,1}).xor(Bitmap1x2({1,0})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({0,1}).xor(Bitmap1x2({1,1})), Bitmap1x2({1,0}));

	EXPECT_EQ(Bitmap1x2({1,0}).xor(Bitmap1x2("00")), Bitmap1x2({1,0}));
	EXPECT_EQ(Bitmap1x2({1,0}).xor(Bitmap1x2({0,1})), Bitmap1x2({1,1}));
	EXPECT_EQ(Bitmap1x2({1,0}).xor(Bitmap1x2({1,0})), Bitmap1x2("00"));
	EXPECT_EQ(Bitmap1x2({1,0}).xor(Bitmap1x2({1,1})), Bitmap1x2({0,1}));
}

TEST(Bitmap2dTest, TestSubdivX)
{
	EXPECT_EQ(Bitmap2x1("00"), Bitmap1x1("0").subdivx());
}

TEST(Bitmap2dTest, TestGetEdgesX)
{
	{
		Bitmap1dArray<2, 2> bmps = {
			Bitmap1d("00"),
			Bitmap1d("00")
		};
		Bitmap2d<2, 2> b(bmps);
		const auto actual = b.getEdgesx();
		EXPECT_EQ(Bitmap2x2("0000"), actual);
	}

	{
		Bitmap1dArray<2, 2> bmps = {
			Bitmap1d({0,1}),
			Bitmap1d("00")
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

TEST(Bitmap3dTest, TestGetSizeX)
{
	EXPECT_EQ(1, Bitmap3d(1,1,1).getSizeX());
	EXPECT_EQ(1, Bitmap3d(1,2,2).getSizeX());
	EXPECT_EQ(2, Bitmap3d(2,2,1).getSizeX());
	EXPECT_EQ(2, Bitmap3d(2,2,2).getSizeX());
}

/*
TEST(Bitmap3dTest, TestGetSizeY)
{
	EXPECT_EQ(1, Bitmap3d<1>(1, 1).getSizeY());
	EXPECT_EQ(2, Bitmap3d<1>(2, 2).getSizeY());
	EXPECT_EQ(2, Bitmap3d<2>(2, 3).getSizeX());
}
/*

TEST(Bitmap3dTest, TestNot)
{
	const Bitmap3d<2> actual = Bitmap3d<2>(2, 2).not();
	EXPECT_TRUE(actual.get(0, 0, 0));
}
*/

TEST(Bitmap3dTest, TestTo8Bit)
{
	EXPECT_EQ( std::bitset<8>("00000000"), Bitmap3d(2,2,2).to8Bit(0,0,0) );
	EXPECT_EQ( std::bitset<8>("11111111"), Bitmap3d(2,2,2).not().to8Bit(0, 0, 0) );
}