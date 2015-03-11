#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector3d.h"
using namespace Crystal::Math;


using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestScale)
{
	Polygon p(0);
	p.setVertices( { VertexSPtr(new Vertex( Vector3d(1.0, 1.0, 1.0), 0 ) ) } );
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const VertexVector expected = { VertexSPtr( new Vertex( Vector3d(0.1f, 0.01f, 10.0f), 0) ) };
	const VertexVector& actual = p.getVertices();
	EXPECT_TRUE( VerticesAreSame( expected, actual ) );
}

TEST(PolygonTest, TestScaleWithCenter)
{
	Polygon p(0);
	p.setVertices({ VertexSPtr(new Vertex( Vector3d(1.0, 1.0, 1.0), 0 )) });
	p.setCenter(Vector3d(1.0, 1.0, 1.0));
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const VertexVector expected = { VertexSPtr( new Vertex(Vector3d(1.0f, 1.0f, 1.0f), 0 ) ) };
	const VertexVector& actual = p.getVertices();
	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

TEST(PolygonTest, TestMove)
{
	Polygon p(0);
	p.setVertices({ VertexSPtr(new Vertex(Vector3d(1.0, 2.0, 3.0), 0)) });

	p.move(Vector3d(1.0, 10.0, 100.0));

	const VertexVector expected = { VertexSPtr( new Vertex(Vector3d(2.0, 12.0, 103.0), 0 ) ) };
	const VertexVector& actual = p.getVertices();

	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

TEST(PolygonTest, TestRotateX)
{
	Polygon p(0);
	p.setVertices({ VertexSPtr(new Vertex(Vector3d(0.0, 0.0, 1.0), 0) ) });
	p.rotateX(180.0);

	const VertexVector& actual = p.getVertices();

	const VertexVector expected{ VertexSPtr(new Vertex( Vector3d(0.0, 0.0, -1.0), 0 )) };
	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

/*
TEST(PolygonTest, TestRotateXWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(0.0, 0.0, 1.0) });
	p.setCenter(Vector3d(0.0, 0.0, 1.0));
	p.rotateX(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(0.0, 0.0, 1.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateY)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.rotateY(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(-1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateYWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.setCenter(Vector3d(1.0, 0.0, 0.0));
	p.rotateY(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateZ)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.rotateZ(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(-1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateZWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.setCenter(Vector3d(1.0, 0.0, 0.0));
	p.rotateZ(180.0);

	const VertexVector& actual = p.getPositions();

	const VertexVector expected{ Vertex( Vector3d(1.0, 0.0, 0.0), 0 ) };
	EXPECT_EQ(expected, actual);
}
*/