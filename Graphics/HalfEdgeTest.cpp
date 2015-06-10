#include "gtest/gtest.h"

#include "../Graphics/HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(HalfEdgeTest, TestIsValid)
{
	using T = float;
	const VertexSPtr<T> v1 = std::make_shared< Vertex<T> >();
	EXPECT_FALSE( HalfEdge<T>(nullptr, nullptr).isValid() );
	EXPECT_TRUE( HalfEdge<T>(v1, nullptr).isValid() );
}

TEST(HalfEdgeTest, TestGetNext)
{
	using T = float;
	const HalfEdge<T> edge(nullptr, nullptr);
	EXPECT_EQ(nullptr, edge.getNext());
}

TEST(HalfEdgeTest, TestCreateOpen)
{
	using T = float;
	const auto& vs = Vertex<T>::create({ Vector3d<T>(0, 0, 0), Vector3d<T>(1, 0, 0) } );
	const auto& edges = HalfEdge<T>::createOpen(vs);
	EXPECT_EQ(1, edges.size());
	EXPECT_EQ(nullptr, edges.front()->getNext());
}

TEST(HalfEdgeTest, TestCreateClosed)
{
	using T = float;
	const auto& vs = Vertex<T>::create({ Vector3d<T>(0, 0, 0), Vector3d<T>(1, 0, 0) });
	const auto& edges = HalfEdge<T>::createClosed(vs);
	EXPECT_EQ(2, edges.size());
}