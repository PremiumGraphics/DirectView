#include <gtest/gtest.h>

#include "HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(HalfEdgeTest, TestConstruct)
{
	HalfEdge edge;
	EXPECT_EQ(nullptr, edge.getPrev());
	EXPECT_EQ(nullptr, edge.getNext());
}

TEST(HalfEdgeTest, TestCreateOpenFromVertices)
{
	VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1),
		new Vertex(Vector3d(1.0, 1.0, 0.0), 2)
	};
	HalfEdgeBuilder builder;
	const HalfEdgeList& actual = builder.createOpenFromVertices( vertices, nullptr );
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(nullptr, actual.front()->getPrev());
	EXPECT_EQ(nullptr, actual.back()->getNext());
	EXPECT_NE(nullptr, actual.front()->getNext());
	EXPECT_NE(nullptr, actual.back()->getPrev());

	EXPECT_EQ(1, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(2, actual.front()->getEnd()->getEdges().size());
}

TEST(HalfEdgeTest, TestCreateClosedFromVertices)
{
	VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
	};
	HalfEdgeBuilder builder;
	const HalfEdgeList& actual = builder.createClosedFromVertices(vertices, nullptr);
	EXPECT_EQ(2, actual.size());
	EXPECT_NE(nullptr, actual.front()->getPrev());
	EXPECT_NE(nullptr, actual.back()->getNext());
	EXPECT_EQ(2, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(actual.front()->getPrev(), actual.back());
}