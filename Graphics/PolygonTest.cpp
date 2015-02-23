#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestScale)
{
	Polygon p;
	p.positions = { Vector3d(1.0, 1.0, 1.0) };
	p.scale(Vector3d(0.1, 0.01, 10.0));
	EXPECT_EQ(Vector3d(0.1, 0.01, 10.0), p.positions.front());
}