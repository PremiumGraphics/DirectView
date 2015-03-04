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

TEST(HalfEdgeTest, TestCreateFromVertices)
{
	VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1),
		new Vertex(Vector3d(1.0, 1.0, 0.0), 2)
	};
	const HalfEdgeList& actual = HalfEdge::createFromVertices( vertices );
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(nullptr, actual.front()->getPrev());
	EXPECT_EQ(nullptr, actual.back()->getNext());
	EXPECT_NE(nullptr, actual.front()->getNext());
	EXPECT_NE(nullptr, actual.back()->getPrev());
}