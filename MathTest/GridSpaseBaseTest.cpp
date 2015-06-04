#include "gtest/gtest.h"

#include "../Math/GridSpaceBase.h"

using namespace Crystal::Math;

template<typename T>
class GridSpaceBaseTest : public GridSpaceBase<T>
{
public:
	explicit GridSpaceBaseTest(const Space3d<T>& space) :
		GridSpaceBase(space)
	{
	}

	GridSpaceBaseTest(const Space3d<T>& space, const Index3d& sizes) :
		GridSpaceBase(space, sizes)
	{
	}

private:

};


TEST(Discretized3dTest, TestGetSizeX)
{
	EXPECT_EQ( 1, GridSpaceBase<float>(Space3d<float>(), Index3d{ 1, 2, 3 } ).getSizeX() );
}

TEST(Discretized3dTest, TestGetSizeY)
{
	EXPECT_EQ( 2, GridSpaceBase<float>(Space3d<float>(), Index3d{ 1, 2, 3 }).getSizeY());
}

TEST(Discretized3dTest, TestGetUnitLengths)
{
	EXPECT_EQ( Vector3d<float>(0.5,0.5,0.5), GridSpaceBase<float>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getUnitLengths() );
	EXPECT_EQ( Vector3d<float>(0.5, 0.25, 0.125), GridSpaceBase<float>(Space3d<float>::Unit(), Index3d{ 2, 4, 8 }).getUnitLengths());
}

TEST(Discretized3dTest, TestGetUnitVolume)
{
	EXPECT_EQ( 0.125, GridSpaceBase<float>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getUnitVolume());
}

TEST(Discretized3dTest, TestGetNormalized)
{
	using T = float;
	EXPECT_EQ( Vector3d<T>(0.25, 0.25, 0.25), GridSpaceBase<T>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getNormalized(0, 0, 0));
	EXPECT_EQ( Vector3d<T>(0.75, 0.75, 0.75), GridSpaceBase<T>(Space3d<float>::Unit(), Index3d{ 2, 2, 2 }).getNormalized(1, 1, 1));
}

TEST(Discretized3dTest, TestToIndex)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	GridSpaceBase<T> bs(s, Index3d{ 2, 2, 2 });
	{
		const std::array<unsigned int, 3> expected = { 0, 0, 0 };
		EXPECT_EQ( expected, bs.toIndex(Vector3d<T>(2, 2, 2)));
	}

	{
		const std::array<unsigned int, 3> expected = { 1, 1, 1 };
		EXPECT_EQ(expected, bs.toIndex(Vector3d<T>(8, 8, 8)));
	}

	//	bs.toIndex(Vector3d<T>(8, 8, 8));
}
