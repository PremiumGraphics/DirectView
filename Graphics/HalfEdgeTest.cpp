#include "gtest/gtest.h"

#include "../Graphics/HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(HalfEdgeTest, TestIsValid)
{
	const VertexSPtr<float> v1 = std::make_shared< Vertex<float> >();
	EXPECT_FALSE( HalfEdge<float>(nullptr, nullptr).isValid() );
	EXPECT_TRUE( HalfEdge<float>(v1, nullptr).isValid() );
}

TEST(HalfEdgeTest, TestGetNext)
{
	HalfEdge<float> edge(nullptr, nullptr);
	EXPECT_EQ(nullptr, edge.getNext());
}

TEST(HalfEdgeTest, TestCreateOpen)
{
	VertexSPtrVector<float> vs = Vertex<float>::create({ Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0) } );
	HalfEdgeSPtrList<float> edges = HalfEdge<float>::createOpen(vs);
	EXPECT_EQ(1, edges.size());
}