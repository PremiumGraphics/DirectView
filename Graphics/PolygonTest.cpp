#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(PolygonTest, TestConstruct)
{
	Polygon p(0, nullptr);
	EXPECT_EQ( nullptr, p.getMaterial() );
}


TEST(PolygonTest, TestAddTriangle)
{
	Polygon p(0, nullptr);
	p.add(Triangle<T>());

	EXPECT_EQ(3, p.getVertices().size());
}