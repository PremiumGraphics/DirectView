#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector.h"
#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;


TEST(PolygonTest, TestAddTriangle)
{
	EXPECT_EQ(3, Polygon().add(Triangle<T>(), ColorRGBA<float>() ).getVertices().size());
}