#include "gtest/gtest.h"

#include "../Math/Discretized.h"

using namespace Crystal::Math;

TEST(Discretized3dTest, TestGetSizeX)
{
	EXPECT_EQ( 1, Discretized3d<float>(Space3d<float>(), Index3d{ 1, 2, 3 } ).getSizeX() );
}

TEST(Discretized3dTest, TestGetSizeY)
{
	EXPECT_EQ(2, Discretized3d<float>(Space3d<float>(), Index3d{ 1, 2, 3 }).getSizeY());
}

TEST(Discretized3dTest, TestGetUnitLengths)
{
	EXPECT_EQ( Vector3d<float>(0.5,0.5,0.5), Discretized3d<float>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getUnitLengths() );
	EXPECT_EQ(Vector3d<float>(0.5, 0.25, 0.125), Discretized3d<float>(Space3d<float>::Unit(), Index3d{ 2, 4, 8 }).getUnitLengths());
}

TEST(Discretized3dTest, TestGetUnitVolume)
{
	EXPECT_EQ( 0.125, Discretized3d<float>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getUnitVolume());
}

TEST(Discretized3dTest, TestGetNormalized)
{
	using T = float;
	EXPECT_EQ(Vector3d<T>(0.25, 0.25, 0.25), Discretized3d<T>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getNormalized(0, 0, 0));
	EXPECT_EQ(Vector3d<T>(0.75, 0.75, 0.75), Discretized3d<T>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getNormalized(1, 1, 1));
}

TEST(Discretized3dTest, TestToIndex)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	Discretized3d<T> bs(s, Index3d{ 2, 2, 2 });
	{
		const std::array<unsigned int, 3> expected = { 0, 0, 0 };
		EXPECT_EQ(expected, bs.toIndex(Vector3d<T>(2, 2, 2)));
	}

	{
		const std::array<unsigned int, 3> expected = { 1, 1, 1 };
		EXPECT_EQ(expected, bs.toIndex(Vector3d<T>(8, 8, 8)));
	}

	//	bs.toIndex(Vector3d<T>(8, 8, 8));
}
