#include "gtest/gtest.h"

#include "../Math/BitSpace.h"

using namespace Crystal::Math;



TEST(BitSpaceTest, TestSetSphere)
{
	using T = float;
	EXPECT_EQ(0, BitSpace3d<T>( Bitmap3d(2, 2, 2) ).setSphere().getBitmap().getCount());
	EXPECT_EQ(1, BitSpace3d<T>( Bitmap3d(3, 3, 3) ).setSphere().getBitmap().getCount());
	EXPECT_EQ(8, BitSpace3d<T>( Bitmap3d(4, 4, 4) ).setSphere().getBitmap().getCount());
}

TEST(BitSpaceTest, TestToCells)
{
	using T = float;
	BitSpace3d<T> bs(Space3d<T>::Unit(), Bitmap3d(2,2,2));
	const auto& cells = bs.toCells();
	EXPECT_EQ( 1, cells.size() );
	EXPECT_EQ(Space3d<T>(Vector3d<T>(0.25, 0.25, 0.25), Vector3d<T>(0.5, 0.5, 0.5)), cells.front().getSpace());
}

TEST(BitSpaceTest, TestEnabledSpaces)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	Bitmap3d bmp(2, 2, 2);
	bmp.set(1,0,0);
	BitSpace3d<T> bs(s, bmp);
	const auto& cells = bs.toEnabledSpaces();
	EXPECT_EQ(1, cells.size());
}


TEST(BitSpaceTest, TestEnabledPositions)
{
	using T = float;
	const auto s = Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1));
	Bitmap3d bmp(2, 2, 2);
	bmp.set(1, 0, 0);
	BitSpace3d<T> bs(s, bmp);
	const auto& positons = bs.toEnabledPositions();
	EXPECT_EQ(1, positons.size());
}

TEST(BitSpaceTest, TestGetOverlapped)
{
	using T = float;
	BitSpace3d<T> bs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	const auto actual = bs.getOverlapped( Space3d<T>( Vector3d<T>(1, 1, 1), Vector3d<T>(2,2,2) ) );
	EXPECT_EQ( Bitmap3d(1,1,1), actual.getBitmap() );

	BitSpace3d<T> lhs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	BitSpace3d<T> rhs(Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	EXPECT_EQ(Bitmap3d(1, 1, 1), lhs.getOverlapped(rhs).getBitmap());
}

TEST(BitSpaceTest, TestAnd)
{
	using T = float;
	BitSpace3d<T> lhs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	BitSpace3d<T> rhs(Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	const BitSpace3d<T> actual = lhs.and(rhs);
	EXPECT_EQ( Bitmap3d(1, 1, 1), actual.getBitmap() );
}

TEST(BitSpaceTest, TestNot)
{
	using T = float;
	BitSpace3d<T> bs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	EXPECT_EQ(8, bs.not().getBitmap().getCount());
}