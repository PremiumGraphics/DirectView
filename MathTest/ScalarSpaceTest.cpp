#include "gtest/gtest.h"

#include "../Math/ScalarSpace.h"

using namespace Crystal::Math;

TEST(GridSpace3dTest, TestGetStart)
{
	using T = float;
	ScalarSpace3d<T> gs;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), gs.getStart());
}

TEST(GridSpace3dTest, TestSetSmooth)
{
	using T = float;
	Grid3d<T> grid(3,3,3);
	ScalarSpace3d<T> gs(Space3d<T>::Unit(), grid);
	gs.setSmooth();
	//gs.setSmooth();
}