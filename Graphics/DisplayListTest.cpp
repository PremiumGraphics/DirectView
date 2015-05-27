#include "gtest/gtest.h"

#include "../Graphics/DisplayList.h"
#include "../Graphics/Material.h"
#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(DisplayTest, TestConstructByPosition)
{
	DisplayList list({ Vector3d<T>(0.0, 0.0, 0.0) });
	const std::vector< float >& actual = list.getPositions();
	const std::vector< float > expected{ 0.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormal)
{
	DisplayList list(
		{ Vector3d<T>(0.0, 0.0, 0.0) },
		{ Vector3d<T>(1.0, 0.0, 0.0) }
	);
	const std::vector< float >& actual = list.getNormals();
	const std::vector< float > expected{ 1.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormalTexCoord)
{
	DisplayList list(
		{ Vector3d<T>(0.0, 0.0, 0.0) },
		{ Vector3d<T>(1.0, 0.0, 0.0) },
		{ Vector3d<T>(1.0, 1.0, 1.0) }
	);
	const std::vector< float >& actual = list.getTexCoords();
	const std::vector< float > expected{ 1.0, 1.0, 1.0 };
	EXPECT_EQ(expected, actual);
}
