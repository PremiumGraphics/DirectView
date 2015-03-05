#include "gtest/gtest.h"

#include "../Graphics/DisplayList.h"
#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(DisplayListTest, TestFromPolygon)
{
	Polygon polygon;
	polygon.setPositions({ Vector3d(0.0, 0.0, 0.0) });

	DisplayList list( &polygon );

	EXPECT_EQ(3, list.getPositions().size());
}