#include "gtest/gtest.h"

#include "../Graphics/DisplayList.h"
#include "../Graphics/Polygon.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(DisplayTest, TestConstructByPosition)
{
	DisplayList list({ Vector3d(0.0, 0.0, 0.0) });
	const std::vector< float >& actual = list.getPositions();
	const std::vector< float > expected{ 0.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormal)
{
	DisplayList list(
		{ Vector3d(0.0, 0.0, 0.0) },
		{ Vector3d(1.0, 0.0, 0.0) }
	);
	const std::vector< float >& actual = list.getNormals();
	const std::vector< float > expected{ 1.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormalTexCoord)
{
	DisplayList list(
		{ Vector3d(0.0, 0.0, 0.0) },
		{ Vector3d(1.0, 0.0, 0.0) },
		{ Vector3d(1.0, 1.0, 1.0) }
	);
	const std::vector< float >& actual = list.getTexCoords();
	const std::vector< float > expected{ 1.0, 1.0, 1.0 };
	EXPECT_EQ(expected, actual);
}

/*
TEST(DisplayListTest, TestAddFace)
{
	Polygon polygon;
	polygon.setPositions({ Vector3d(0.0, 0.0, 0.0) });

	DisplayList list( &polygon );

	const std::vector< float > expected{ 0.0, 0.0, 0.0 };

	EXPECT_EQ( expected, list.getPositions() );
}
*/