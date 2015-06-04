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