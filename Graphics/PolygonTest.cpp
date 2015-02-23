#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestScale)
{
	Polygon p;
	p.setPositions( { Vector3d(1.0, 1.0, 1.0) } );
	p.scale(Vector3d(0.1, 0.01, 10.0));

	const VectorVector expected = { Vector3d(0.1, 0.01, 10.0) };
	const VectorVector& actual = p.getPositions();
	EXPECT_EQ( expected, actual );
}