#include <gtest/gtest.h>

#include "HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(HalfEdgeTest, TestConstruct)
{
	HalfEdge edge;
	EXPECT_EQ(nullptr, edge.getPrev());
	EXPECT_EQ(nullptr, edge.getNext());
	EXPECT_EQ(nullptr, edge.getFace());
}

TEST(HalfEdgeBuilderTest, TestInsert)
{
	VertexBuilder vBuilder;
	HalfEdgeBuilder eBuilder;
	VertexSPtr v0 = vBuilder.build(Vector3d(0.0, 0.0, 0.0));
	VertexSPtr v1 = vBuilder.build(Vector3d(1.0, 0.0, 0.0));
	HalfEdgeSPtr edge = eBuilder.build( v0, v1 );
	VertexSPtr v2 = vBuilder.build(Vector3d(0.5, 0.0, 0.0));

	HalfEdgeSPtr inserted = eBuilder.insert(edge, v2);
	EXPECT_EQ(v0.get(), edge->getStart().get());
	EXPECT_EQ(v2.get(), edge->getEnd().get());
	EXPECT_EQ(v2.get(), inserted->getStart().get());
	EXPECT_EQ(v1.get(), inserted->getEnd().get());
	EXPECT_EQ(2, v2->getEdges().size());
}

TEST(HalfEdgeBuilderTest, TestBuildOpenFromVertices)
{
	HalfEdgeBuilder builder;

	VertexBuilderSPtr vBuilder = builder.getVertexBuilder();
	VertexSPtrVector vv{
		vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
		vBuilder->build(Vector3d(1.0, 0.0, 0.0)),
		vBuilder->build(Vector3d(1.0, 1.0, 0.0))
	};

	const HalfEdgeSPtrList& actual = builder.buildOpenFromVertices(vv);
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(nullptr, actual.front()->getPrev());
	EXPECT_EQ(nullptr, actual.back()->getNext());
	EXPECT_NE(nullptr, actual.front()->getNext());
	EXPECT_NE(nullptr, actual.back()->getPrev());

	EXPECT_EQ(1, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(2, actual.front()->getEnd()->getEdges().size());
	EXPECT_EQ(nullptr, actual.front()->getFace());
	EXPECT_EQ(nullptr, actual.back()->getFace());
}

TEST(HalfEdgeBuilderTest, TestBuildClosedFromVertices)
{
	HalfEdgeBuilder builder;

	VertexBuilderSPtr vBuilder = builder.getVertexBuilder();
	VertexSPtrVector vv{
		vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
		vBuilder->build(Vector3d(1.0, 0.0, 0.0)),
		vBuilder->build(Vector3d(1.0, 1.0, 0.0))
	};

	const HalfEdgeSPtrList& actual = builder.buildClosedFromVertices(vv);
	EXPECT_EQ(3, actual.size());
	EXPECT_NE(nullptr, actual.front()->getPrev());
	EXPECT_NE(nullptr, actual.back()->getNext());
	EXPECT_EQ(2, actual.front()->getStart()->getEdges().size());
	EXPECT_EQ(actual.front()->getPrev(), actual.back());
	EXPECT_EQ(nullptr, actual.front()->getFace());
}