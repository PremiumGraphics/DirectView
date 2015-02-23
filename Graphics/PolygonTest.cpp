#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestCreateTriangle)
{
	std::unique_ptr< Polygon > p( Polygon::createTriangle() );
	EXPECT_EQ(3, p->getPositions().size());
	EXPECT_EQ(3, p->getNormals().size());
}

TEST(PolygonTest, TestCreateQuad)
{
	std::unique_ptr< Polygon > p( Polygon::createQuad() );
	EXPECT_EQ(4, p->getPositions().size());
}

TEST(PolygonTest, TestCreateCircle)
{
	std::unique_ptr< Polygon > p(Polygon::createCircle(1.0f, 60.0f));
	EXPECT_EQ(6, p->getPositions().size());
}

TEST(PolygonTest, TestScale)
{
	Polygon p;
	p.setPositions( { Vector3d(1.0, 1.0, 1.0) } );
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const VectorVector expected = { Vector3d(0.1f, 0.01f, 10.0f) };
	const VectorVector& actual = p.getPositions();
	EXPECT_EQ( expected, actual );
}