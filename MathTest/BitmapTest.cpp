#include "gtest/gtest.h"

#include "../Math/Bitmap.h"

using namespace Crystal::Math;

TEST(Bitmap1dTest, TestGetCount)
{
	EXPECT_EQ(0, Bitmap1d({ 0, 0 }).getCount());
	EXPECT_EQ(1, Bitmap1d({ 0, 1 }).getCount());
	EXPECT_EQ(1, Bitmap1d({ 1, 0 }).getCount());
	EXPECT_EQ(2, Bitmap1d({ 1, 1 }).getCount());
}

TEST(Bitmap1dTest, TestAnd)
{
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 1, 0 })), Bitmap1d({ 0, 0}));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).and(Bitmap1d({ 1, 1 })), Bitmap1d({ 0, 0}));

	EXPECT_EQ(Bitmap1d({ 0, 1 }).and(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).and(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).and(Bitmap1d({ 1, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).and(Bitmap1d({ 1, 1 })), Bitmap1d({ 0, 1 }));

	EXPECT_EQ(Bitmap1d({ 1, 0 }).and(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).and(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).and(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).and(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 0 }));

	EXPECT_EQ(Bitmap1d({ 1, 1 }).and(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).and(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).and(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).and(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));
}


TEST(Bitmap1dTest, TestOr)
{
	EXPECT_EQ(Bitmap1d({ 0, 0 }).or(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).or(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).or(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).or(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));


	EXPECT_EQ(Bitmap1d({ 0, 1 }).or(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).or(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).or(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).or(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));

	EXPECT_EQ(Bitmap1d({ 1, 0 }).or(Bitmap1d({ 0, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).or(Bitmap1d({ 0, 1 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).or(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).or(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));


	EXPECT_EQ(Bitmap1d({ 1, 1 }).or(Bitmap1d({ 0, 0 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).or(Bitmap1d({ 0, 1 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).or(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).or(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));

}

TEST(Bitmap1dTest, TestXor)
{
	EXPECT_EQ(Bitmap1d({ 0, 0 }).xor(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).xor(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).xor(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 0 }).xor(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 1 }));

	EXPECT_EQ(Bitmap1d({ 0, 1 }).xor(Bitmap1d({ 0, 0 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).xor(Bitmap1d({ 0, 1 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).xor(Bitmap1d({ 1, 0 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 0, 1 }).xor(Bitmap1d({ 1, 1 })), Bitmap1d({ 1, 0 }));

	EXPECT_EQ(Bitmap1d({ 1, 0 }).xor(Bitmap1d({ 0, 0 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).xor(Bitmap1d({ 0, 1 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).xor(Bitmap1d({ 1, 0 })), Bitmap1d({ 0, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 0 }).xor(Bitmap1d({ 1, 1 })), Bitmap1d({ 0, 1 }));

	EXPECT_EQ(Bitmap1d({ 1, 1 }).xor(Bitmap1d({ 0, 0 })), Bitmap1d({ 1, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).xor(Bitmap1d({ 0, 1 })), Bitmap1d({ 1, 0 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).xor(Bitmap1d({ 1, 0 })), Bitmap1d({ 0, 1 }));
	EXPECT_EQ(Bitmap1d({ 1, 1 }).xor(Bitmap1d({ 1, 1 })), Bitmap1d({ 0, 0 }));
}

TEST(Bitmap1dTest, TestNot)
{
	EXPECT_EQ(Bitmap1d({ 1, 1 }), Bitmap1d({ 0, 0 }).not() );
	EXPECT_EQ(Bitmap1d({ 1, 0 }), Bitmap1d({ 0, 1 }).not() );
	EXPECT_EQ(Bitmap1d({ 0, 1 }), Bitmap1d({ 1, 0 }).not() );
	EXPECT_EQ(Bitmap1d({ 0, 0 }), Bitmap1d({ 1, 1 }).not() );
}

TEST(Bitmap1dTest, TestGetSub)
{
	EXPECT_EQ(Bitmap1d({ 1, 1 }), Bitmap1d({ 1, 1, 1 }).getSub(0,2) );
	EXPECT_EQ(Bitmap1d({ 0, 1 }), Bitmap1d({ 0, 0, 1 }).getSub(1,3) );
	//EXPECT_EQ(Bitmap1d(std::vector<bool>{ 1 }), Bitmap1d({ 1, 1, 1 }).getSub(2));
}

TEST(Bitmap1dTest, TestSetBitmap)
{
	EXPECT_EQ(Bitmap1d({ 1, 0, 0 }), Bitmap1d({ 1, 1, 1 }).set(1, Bitmap1d({ 0, 0 }) ) );
}


TEST(Bitmap1dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap1d({ 0, 0 }).isAll());
	EXPECT_FALSE(Bitmap1d({ 0, 1 }).isAll());
	EXPECT_FALSE(Bitmap1d({ 1, 0 }).isAll());
	EXPECT_TRUE( Bitmap1d({ 1, 1 }).isAll());

}
/*

TEST(Bitmap1dTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap1d({0,0}).isAny());
	EXPECT_TRUE(Bitmap1d({0,1}).isAny());
	EXPECT_TRUE(Bitmap1d({1,0}).isAny());
	EXPECT_TRUE(Bitmap1d({1,1}).isAny());
}
*/

TEST(Bitmap1dTest, TestIsNone)
{
	EXPECT_TRUE( Bitmap1d({0,0}).isNone());
	EXPECT_FALSE(Bitmap1d({0,1}).isNone());
	EXPECT_FALSE(Bitmap1d({1,0}).isNone());
	EXPECT_FALSE(Bitmap1d({1,1}).isNone());
}

/*
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

TEST(Bitmap2dTest, TestGetCount)
{
	EXPECT_EQ(0, Bitmap2d::FALSE(2,2).getCount());
	EXPECT_EQ(4, Bitmap2d::TRUE(2,2).getCount());
}

TEST(Bitmap2dTest, TestGetSub)
{
	EXPECT_EQ( Bitmap2d(1,1), Bitmap2d(2, 2).getSub(0, 1, 0, 1) );
}

TEST(Bitmap2dTest, TestGet)
{
	EXPECT_EQ(Bitmap1d(2), Bitmap2d(2, 2, false).get(1));
}

TEST(Bitmap2dTest, TestSetBitmap)
{
	Bitmap2d lhs( 2, 2, false );
	Bitmap2d rhs( 1, 1, true );
	const std::array< unsigned int, 2 > start{ 1, 1 };
	Bitmap2d actual = lhs.set(start, rhs);
	EXPECT_EQ(1, actual.getCount());
}

/*

TEST(Bitmap2dTest, TestSet)
{
	Bitmap1x2 bitmap;
	bitmap.set(0, 0);
	EXPECT_TRUE(bitmap.get(0, 0));
	bitmap.set(0, 1);
	EXPECT_TRUE(bitmap.get(0, 1));
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

*/

TEST(Bitmap2dTest, TestEquals)
{
	EXPECT_TRUE( Bitmap2d::TRUE(1,1).equals(Bitmap2d(1,1,true)));
	EXPECT_EQ( Bitmap2d(1,1,true), Bitmap2d(1,1,true) );

	EXPECT_FALSE( Bitmap2d(1,1,true).equals(Bitmap2d(1,1,false)) );
	EXPECT_NE( Bitmap2d(1,1,true), Bitmap2d(1,1,false));
}


TEST(Bitmap2dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap2d::FALSE(2, 2).isAll() );
	EXPECT_TRUE( Bitmap2d::TRUE( 2, 2).isAll() );
}

TEST(Bitmap2dTest, TestIsAny)
{
	EXPECT_FALSE( Bitmap2d::FALSE(2, 2).isAny());
	EXPECT_TRUE(  Bitmap2d::TRUE( 2, 2).isAny());
}

TEST(Bitmap2dTest, TestIsNone)
{
	EXPECT_TRUE( Bitmap2d::FALSE(2, 2).isNone());
	EXPECT_FALSE(Bitmap2d::TRUE( 2, 2).isNone());
}

TEST(Bitmap2dTest, TestNot)
{
	EXPECT_EQ( Bitmap2d::FALSE(2,2), Bitmap2d::TRUE(2,2).not());
	EXPECT_EQ( Bitmap2d(2, 2, true), Bitmap2d(2, 2, false).not());
}
/*


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

TEST(Bitmap3dTest, TestGetSizeY)
{
	EXPECT_EQ(1, Bitmap3d(1,1,1).getSizeY());
	EXPECT_EQ(2, Bitmap3d(1,2,2).getSizeY());
	EXPECT_EQ(2, Bitmap3d(2,2,3).getSizeX());
}

TEST(Bitmap3dTest, TestGetSizeZ)
{
	EXPECT_EQ(1, Bitmap3d(1, 1, 1).getSizeZ());
	EXPECT_EQ(2, Bitmap3d(1, 2, 2).getSizeZ());
	EXPECT_EQ(3, Bitmap3d(2, 2, 3).getSizeZ());
}

TEST(Bitmap3dTest, TestGetSizes)
{
	const std::array<unsigned int, 3> expected{ 1, 1, 1 };
	EXPECT_EQ( expected, Bitmap3d(1, 1, 1).getSizes());

}

TEST(Bitmap3dTest, TestNot)
{
	EXPECT_EQ(Bitmap3d::TRUE(2, 2, 2), Bitmap3d::FALSE(2,2,2).not());
}

TEST(Bitmap3dTest, TestIsAll)
{
	EXPECT_FALSE(Bitmap3d::FALSE(2, 2, 2).isAll());
	EXPECT_TRUE(Bitmap3d::TRUE(2, 2, 2).isAll());
}

/*
TEST(Bitmap3dTest, TestIsAny)
{
	EXPECT_FALSE(Bitmap2d::FALSE(2, 2).isAny());
	EXPECT_TRUE(Bitmap2d::TRUE(2, 2).isAny());
}

TEST(Bitmap3dTest, TestIsNone)
{
	EXPECT_TRUE(Bitmap2d::FALSE(2, 2).isNone());
	EXPECT_FALSE(Bitmap2d::TRUE(2, 2).isNone());
}
*/


TEST(Bitmap3dTest, TestTo8Bit)
{
	EXPECT_EQ( std::bitset<8>("00000000"), Bitmap3d::FALSE(2,2,2).to8Bit(0,0,0) );
	EXPECT_EQ( std::bitset<8>("11111111"), Bitmap3d::TRUE(2,2,2).to8Bit(0,0,0) );
}

TEST(Bitmap3dTest, TestGetSub)
{
	EXPECT_EQ(Bitmap3d(1, 1, 1), Bitmap3d(3, 3, 3).getSub({ 0, 0, 0 }, { 1, 1, 1 }));
}

TEST(Bitmap3dTest, TestSetBitmap)
{
	Bitmap3d lhs(2, 2, 2, false);
	Bitmap3d rhs(1, 1, 1, true);
	const std::array< unsigned int, 3 > start{ 1, 1, 1 };
	Bitmap3d actual = lhs.set(start, rhs);
	EXPECT_EQ(1, actual.getCount());
}



/*
TEST(Bitmap3dTest, TestSetSphere)
{
	const auto c  = Bitmap3d(3, 3, 3).setSphere().getCount();
}
*/