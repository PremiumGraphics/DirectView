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