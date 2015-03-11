#include "gtest/gtest.h"

#include "../Graphics/DisplayList.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/PolygonBuilder.h"

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

TEST(DisplayListTest, TestAddFace)
{
	VertexBuilder vBuilder;
	HalfEdgeBuilder eBuilder(vBuilder);
	FaceBuilder builder( eBuilder);
	builder.buildQuad();

	DisplayList list;
	list.add(builder.getFaces().front().get());

	const std::vector<unsigned int> expected{ 0, 0, 0, 0 };
	EXPECT_EQ( expected, list.getFaceIds());
}

TEST(DisplayListTest, TestAddPolygon)
{
	VertexBuilder vBuilder;
	HalfEdgeBuilder eBuilder(vBuilder);
	FaceBuilder fBuilder( eBuilder);
	PolygonBuilder builder( fBuilder);

	DisplayList list;
	list.add(builder.buildQuad() );

	{
		const std::vector<unsigned int> expected{ 0, 0, 0, 0 };
		EXPECT_EQ(expected, list.getPolygonIds());
	}

	{
		const std::vector<unsigned int> expected{ 0, 1, 2, 3 };
		EXPECT_EQ( expected, list.getVertexIds() );
	}

	list.clear();
	list.add(builder.buildTriangle());

	{
		const std::vector<unsigned int> expected{ 0, 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ( expected, list.getVertexIds() );
	}

}

/*
TEST(FaceTest, TestGetPositions)
{
	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildOpenFromVertices();
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildClosedFromVertices(vBuilder.getVertices());
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}
}
*/