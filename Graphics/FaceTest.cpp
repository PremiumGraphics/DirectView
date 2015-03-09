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
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices);
		Face f(edges, 0);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createClosedFromVertices(vertices);
		Face f(edges, 0);
		EXPECT_FALSE(f.isOpen());
		EXPECT_TRUE(f.isClosed());
	}
	//Face f;
}

TEST(FaceTest, TestGetPositions)
{
	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createClosedFromVertices(vertices);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
	}
}

TEST(FaceTest, TestGetNormals)
{
	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getNormals().size());
	}

}