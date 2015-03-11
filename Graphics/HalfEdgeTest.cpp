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

TEST(HalfEdgeTest, TestBuildOpenFromVertices)
{
	VertexBuilder vBuilder;
	vBuilder.build(Vector3d(0.0, 0.0, 0.0));
	vBuilder.build(Vector3d(1.0, 0.0, 0.0));
	vBuilder.build(Vector3d(1.0, 1.0, 0.0));

	HalfEdgeBuilder builder( vBuilder );
	const HalfEdgeList& actual = builder.buildOpenFromVertices( );
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(nullptr, actual.front()->getPrev());
	EXPECT_EQ(nullptr, actual.back()->getNext());
	EXPECT_NE(nullptr, actual.front()->getNext());
	EXPECT_NE(nullptr, actual.back()->getPrev());

	EXPECT_EQ(1, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(2, actual.front()->getEnd()->getEdges().size());
	EXPECT_EQ(nullptr, actual.front()->getFace());
}

TEST(HalfEdgeTest, TestBuilderClosedFromVertices)
{
	VertexBuilder vBuilder;
	vBuilder.build(Vector3d(0.0, 0.0, 0.0));
	vBuilder.build(Vector3d(1.0, 0.0, 0.0));
	vBuilder.build(Vector3d(1.0, 1.0, 0.0));

	HalfEdgeBuilder builder( vBuilder );
	const HalfEdgeList& actual = builder.buildClosedFromVertices(vBuilder.getVertices() );
	EXPECT_EQ(3, actual.size());
	EXPECT_NE(nullptr, actual.front()->getPrev());
	EXPECT_NE(nullptr, actual.back()->getNext());
	EXPECT_EQ(2, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(actual.front()->getPrev(), actual.back());
	EXPECT_EQ(nullptr, actual.front()->getFace());
}