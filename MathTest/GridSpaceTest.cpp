#include "gtest/gtest.h"

#include "../Math/GridSpace.h"

using namespace Crystal::Math;

TEST(GridSpace3dTest, TestGetStart)
{
	using T = float;
	GridSpace3d<T> gs;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), gs.getStart());
}

TEST(GridSpace3dTest, TestSetSmooth)
{
	using T = float;
	Grid3d<T> grid(3,3,3);
	Discretized3d<T> ds(Space3d<T>::Unit(), Index3d{ 3, 3, 3 });
	GridSpace3d<T> gs(ds, grid);
	gs.setSmooth();
	//gs.setSmooth();
}