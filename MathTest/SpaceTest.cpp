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

TEST(SpaceTest, TestToArray)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const std::array< Vector3d<T>, 8 >& actual = s.toArray();
	EXPECT_EQ(Vector3d<T>(0, 0, 0), actual[0]);
	EXPECT_EQ(Vector3d<T>(0, 0, 1), actual[1]);
	EXPECT_EQ(Vector3d<T>(0, 1, 0), actual[2]);
	EXPECT_EQ(Vector3d<T>(0, 1, 1), actual[3]);
	EXPECT_EQ(Vector3d<T>(1, 0, 0), actual[4]);
	EXPECT_EQ(Vector3d<T>(1, 0, 1), actual[5]);
	EXPECT_EQ(Vector3d<T>(1, 1, 0), actual[6]);
	EXPECT_EQ(Vector3d<T>(1, 1, 1), actual[7]);

}
/*

TEST(SpaceTest, TestEquals)
{
	using T = float;
	EXPECT_EQ(Space1d<T>(), Space1d<T>());
	EXPECT_NE(Space1d<T>(), Space1d<T>(Position1d<T>({ 1 })));

}
*/