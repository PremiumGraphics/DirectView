#include "gtest/gtest.h"

#include "../Math/Space.h"

using namespace Crystal::Math;


TEST(SpaceTest, TestGetStart)
{
	using T = float;
	EXPECT_EQ( Vector3d<T>(0,0,0), Space3d<T>().getStart());
	EXPECT_EQ( Vector3d<T>(1,1,1), Space3d<T>(Vector3d<T>(1,1,1)).getStart());
}

TEST(SpaceTest, TestGetEnd)
{
	using T = float;
	EXPECT_EQ( Vector3d<T>(0,0,0), Space3d<T>().getEnd());
	EXPECT_EQ( Vector3d<T>(10, 10, 10), Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(5, 5, 5)).getEnd() );
}

TEST(SpaceTest, TestGetVolume)
{
	using T = float;
	EXPECT_EQ(0, Space3d<T>().getVolume());
	EXPECT_EQ(125, Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(5, 5, 5)).getVolume());
}


TEST(SpaceTest, TestGetDivided)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	{
		const auto actual = s.getDivided(2, 1, 1);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(5, 10, 10)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(5, 0, 0), Vector3d<T>(5, 10, 10)), actual[1]);
	}
	{
		const auto actual = s.getDivided(1, 2, 1);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 5, 10)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 5, 0), Vector3d<T>(10, 5, 10)), actual[1]);
	}
	{
		const auto actual = s.getDivided(1, 1, 2);
		EXPECT_EQ(2, actual.size());
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 5)), actual[0]);
		EXPECT_EQ(Space3d<T>(Vector3d<T>(0, 0, 5), Vector3d<T>(10, 10, 5)), actual[1]);
	}

}

TEST(SpaceTest, TestHasIntersection)
{
	using T = float;
	const auto lhs = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	const auto rhs = Space3d<T>(Vector3d<T>(5, 5, 5), Vector3d<T>(10, 10, 10));
	EXPECT_TRUE(lhs.hasIntersection(rhs));
}

TEST(SpaceTest, TestToArray)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const std::array< Vector3d<T>, 8 >& actual = s.toArray();
	EXPECT_EQ(Vector3d<T>(0, 0, 0), actual[0]);
	EXPECT_EQ(Vector3d<T>(1, 0, 0), actual[1]);
	EXPECT_EQ(Vector3d<T>(1, 1, 0), actual[2]);
	EXPECT_EQ(Vector3d<T>(0, 1, 0), actual[3]);
	EXPECT_EQ(Vector3d<T>(0, 0, 1), actual[4]);
	EXPECT_EQ(Vector3d<T>(1, 0, 1), actual[5]);
	EXPECT_EQ(Vector3d<T>(1, 1, 1), actual[6]);
	EXPECT_EQ(Vector3d<T>(0, 1, 1), actual[7]);
}

TEST(BitSpaceTest, TestGetUnitLength)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<T> bs(s, bmp);
	EXPECT_EQ( Vector3d<T>( 5,5, 5), bs.getUnitLengths() );
}

TEST(BitSpaceTest, TestToIndex)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10) );
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<T> bs(s, bmp);
	{
		const std::array<int, 3> expected = { 0, 0, 0 };
		EXPECT_EQ(expected, bs.toIndex(Vector3d<T>(2, 2, 2)));
	}

	{
		const std::array<int, 3> expected = { 1, 1, 1 };
		EXPECT_EQ(expected, bs.toIndex(Vector3d<T>(8, 8, 8)));
	}

//	bs.toIndex(Vector3d<T>(8, 8, 8));
}
/*

TEST(SpaceTest, TestEquals)
{
	using T = float;
	EXPECT_EQ(Space1d<T>(), Space1d<T>());
	EXPECT_NE(Space1d<T>(), Space1d<T>(Position1d<T>({ 1 })));

}
*/