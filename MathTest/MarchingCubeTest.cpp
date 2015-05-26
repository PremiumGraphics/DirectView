#include "gtest/gtest.h"

#include "../Math/MarchingCube.h"

using namespace Crystal::Math;

TEST(MarchingCubeTest, TestBuild)
{
	MarchingCube mc;
	mc.buildTable();
	//mc.Polygonise( )
	const Vector3d__<float> v1({ 0, 0, 0 });
	const Vector3d__<float> v2({ 10, 10, 10 });
	Vector3d__<float> actual = mc.VertexInterp(0.5, v1, v2, 0.0, 1.0);
	EXPECT_EQ(Vector3d__<float>({ 5, 5, 5 }), actual);
}