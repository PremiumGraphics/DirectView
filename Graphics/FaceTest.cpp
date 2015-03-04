#include "gtest/gtest.h"

#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(FaceTest, TestIsClosed)
{
	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		const HalfEdgeList& edges = HalfEdge::createFromVertices(vertices);
		Face f(edges);
		EXPECT_FALSE(f.isClosed());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
		Face f(edges);
		EXPECT_TRUE(f.isClosed());
	}
	//Face f;
}

/*
TEST(FaceTest, TestIsClosed)
{
	const VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
	};

}
*/