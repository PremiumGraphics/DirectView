#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"

using namespace Crystal::Math;

TEST(GridSpace3dTest, TestGetStart)
{
	using T = float;
	ScalarSpace3d<T> gs;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), gs.getStart());
}

TEST(GridSpace3dTest, TestaddSmooth)
{
	using T = float;
	Grid3d<T> grid(3,3,3);
	ScalarSpace3d<T> gs(Space3d<T>::Unit(), grid);
	gs.addSmooth(Vector3d<T>(0.5,0.5,0.5),0.5);
	//gs.setSmooth();
}

TEST(GridSpace3dTest, TestToCells)
{
	using T = float;
	EXPECT_EQ( 1, ScalarSpace3d<T>(Space3d<T>::Unit(), Grid3d<T>(2, 2, 2)).toCells().size() );
}

TEST(GridSpace3dTest, TestGetOverlapped)
{
	using T = float;
	ScalarSpace3d<T> ss(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Grid3d<T>(2, 2, 2));
	const auto actual = ss.getOverlapped(Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2)));
	EXPECT_EQ(Grid3d<T>(1, 1, 1), actual.getGrid());

	//BitSpace3d<T> lhs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	//BitSpace3d<T> rhs(Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2)), Bitmap3d(2, 2, 2));
	//EXPECT_EQ(Bitmap3d(1, 1, 1), lhs.getOverlapped(rhs).getBitmap());
}

TEST(GridSpace3dTest, TestAdd)
{
	using T = float;
	ScalarSpace3d<T> lhs(Space3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2)), Grid3d<T>(2, 2, 2));
	ScalarSpace3d<T> rhs(Space3d<T>(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2)), Grid3d<T>(2, 2, 2));
	lhs.add(rhs);
}