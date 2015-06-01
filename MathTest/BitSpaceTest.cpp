#include "gtest/gtest.h"

#include "../Math/BitSpace.h"

using namespace Crystal::Math;

TEST(BitSpaceTest, TestGetUnitLength)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<T> bs(s, bmp);
	EXPECT_EQ(Vector3d<T>(5, 5, 5), bs.getUnitLengths());
}

TEST(BitSpaceTest, TestToIndex)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(10, 10, 10));
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

TEST(BitSpaceTest, TestGetNormalized)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<T> bs(s, bmp);
	EXPECT_EQ(Vector3d<T>(0.25, 0.25, 0.25), bs.getNormalized(0, 0, 0));
	EXPECT_EQ(Vector3d<T>(0.75, 0.75, 0.75), bs.getNormalized(1, 1, 1));
}

TEST(BitSpaceTest, TestSetSphere)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const Bitmap3d bmp(3, 3, 3);
	BitSpace3d<T> bs(s, bmp);
	bs.setSphere();
	EXPECT_EQ(19, bs.getBitmap().getCount());
}

TEST(BitSpaceTest, TestToCells)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	const Bitmap3d bmp(2, 2, 2);
	BitSpace3d<T> bs(s, bmp);
	const auto& cells = bs.toCells();
	EXPECT_EQ( 1, cells.size() );
	EXPECT_EQ(Space3d<T>(Vector3d<T>(0.25, 0.25, 0.25), Vector3d<T>(0.5, 0.5, 0.5)), cells.front().getSpace());
}