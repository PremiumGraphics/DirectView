#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

using namespace Crystal::Math;

TEST(MarchingCubeTest, TestBuild)
{
	MarchingCube<float> mc;
	mc.buildTable();
	//mc.Polygonise( )
	const Position3d<float> v1(0, 0, 0 );
	const Position3d<float> v2(10, 10, 10);
	const Position3d<float> actual = mc.VertexInterp(0.5, v1, v2, 0.0, 1.0);
	EXPECT_EQ( Position3d<float>({ 5, 5, 5 }), actual);
}

TEST(MarchingCubeTest, TestMarch)
{
	MarchingCube<float> mc;
	mc.buildTable();

	MarchingCube<float>::GRIDCELL cell;
	cell.p = {
		Position3d<float>(0, 0, 0),
		Position3d<float>(1, 0, 0),
		Position3d<float>(1, 1, 0),
		Position3d<float>(0, 1, 0),
		Position3d<float>(0, 0, 1),
		Position3d<float>(1, 0, 1),
		Position3d<float>(1, 1, 1),
		Position3d<float>(0, 1, 1)
	};
	
	const std::array< double, 8 > vs = { 0, 0, 0, 0, 1, 1, 1, 1 };
	const auto actual = mc.Polygonise(cell, vs,0.5);
	EXPECT_EQ(2, actual.size());

	{
		const auto actual = mc.Polygonise(cell, { 0, 0, 0, 0, 0, 0, 0, 0 }, 0.5);
		EXPECT_EQ(0, actual.size());
	}

	{
		const auto actual = mc.Polygonise(cell, { 1, 0, 0, 0, 0, 0, 0, 0 },0.5);
		EXPECT_EQ(1, actual.size());
	}

	{
		const auto actual = mc.Polygonise(cell, { 1, 1, 0, 0, 0, 0, 0, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}

	/*
	{
		const auto actual = mc.Polygonise(cell, { 1, 0, 1, 0, 0, 0, 0, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}
	*/

	{
		const auto actual = mc.Polygonise(cell, { 1, 0, 0, 0, 0, 0, 1, 0 }, 0.5);
		EXPECT_EQ(2, actual.size());
	}

	/*
	{
		const auto actual = mc.Polygonise(cell, { 0, 1, 0, 1, 0, 0, 1, 0 }, 0.5);
		EXPECT_EQ(3, actual.size());
	}
	*/


	{
		const auto actual = mc.Polygonise(cell, { 1, 0, 0, 1, 0, 1, 1, 0 }, 0.5);
		EXPECT_EQ(4, actual.size());
	}


	{
		const auto actual = mc.Polygonise(cell, { 1, 1, 1, 1, 1, 1, 1, 1 }, 0.5);
		EXPECT_EQ(0, actual.size());
	}

}