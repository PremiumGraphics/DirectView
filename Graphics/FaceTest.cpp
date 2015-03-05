#include "gtest/gtest.h"

#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;


/*
TEST(FaceTest, TestConstruct)
{
	const VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
	};
}
*/

TEST(FaceTest, TestIsClosed)
{
	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		const HalfEdgeList& edges = HalfEdge::createOpenFromVertices(vertices);
		Face f(edges);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		const HalfEdgeList& edges = HalfEdge::createClosedFromVertices(vertices);
		Face f(edges);
		EXPECT_FALSE(f.isOpen());
		EXPECT_TRUE(f.isClosed());
	}
	//Face f;
}

TEST(FaceTest, TestGetPositions)
{
	const VertexVector vertices{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
	};
	const HalfEdgeList& edges = HalfEdge::createOpenFromVertices(vertices);
	Face f(edges);
	EXPECT_EQ(2, f.getPositions().size());
}