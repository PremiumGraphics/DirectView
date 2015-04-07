#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Box.h"


using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestConstruct)
{
	Polygon p(0, nullptr);
	EXPECT_EQ( nullptr, p.getMaterial() );
}

TEST(PolygonTest, TestScale)
{
	Polygon p(0, nullptr);
	p.setVertices( { VertexSPtr(new Vertex( Vector3d(1.0, 1.0, 1.0), 0 ) ) } );
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const VertexSPtrVector expected = { VertexSPtr( new Vertex( Vector3d(0.1f, 0.01f, 10.0f), 0) ) };
	const VertexSPtrVector& actual = p.getVertices();
	EXPECT_TRUE( VerticesAreSame( expected, actual ) );
}

TEST(PolygonTest, TestScaleWithCenter)
{
	Polygon p(0, nullptr);
	p.setVertices({ VertexSPtr(new Vertex( Vector3d(1.0, 1.0, 1.0), 0 )) });
	p.setCenter(Vector3d(1.0, 1.0, 1.0));
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const VertexSPtrVector expected = { VertexSPtr( new Vertex(Vector3d(1.0f, 1.0f, 1.0f), 0 ) ) };
	const VertexSPtrVector& actual = p.getVertices();
	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

TEST(PolygonTest, TestMove)
{
	Polygon p(0, nullptr);
	p.setVertices({ VertexSPtr(new Vertex(Vector3d(1.0, 2.0, 3.0), 0)) });

	p.move(Vector3d(1.0, 10.0, 100.0));

	const VertexSPtrVector expected = { VertexSPtr( new Vertex(Vector3d(2.0, 12.0, 103.0), 0 ) ) };
	const VertexSPtrVector& actual = p.getVertices();

	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

TEST(PolygonTest, TestRotateX)
{
	Polygon p(0, nullptr);
	p.setVertices({ VertexSPtr(new Vertex(Vector3d(0.0, 0.0, 1.0), 0) ) });
	p.rotateX(180.0);

	const VertexSPtrVector& actual = p.getVertices();

	const VertexSPtrVector expected{ VertexSPtr(new Vertex( Vector3d(0.0, 0.0, -1.0), 0 )) };
	EXPECT_TRUE(VerticesAreSame(expected, actual));
}

TEST(PolygonTest, TestBoundingBox)
{
	Polygon p(0, nullptr);
	const VertexSPtrVector vertices = {
		VertexSPtr(new Vertex(Vector3d(0.0, 0.0, 0.0), 0)),
		VertexSPtr(new Vertex(Vector3d(1.0, 0.0, 1.0), 0))
	};
	p.setVertices(vertices);
	Box box = p.getBoundingBox();
	EXPECT_EQ(box.getMin(), Vector3d(0.0f, 0.0f, 0.0f));
	EXPECT_EQ(box.getMax(), Vector3d(1.0f, 0.0f, 1.0f));
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

	const VertexSPtrVector& actual = p.getPositions();

	const VertexSPtrVector expected{ Vertex( Vector3d(1.0, 0.0, 0.0), 0 ) };
	EXPECT_EQ(expected, actual);
}
*/