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
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices, nullptr);
		Face f(edges, 0);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createClosedFromVertices(vertices, nullptr);
		Face f(edges, 0);
		EXPECT_FALSE(f.isOpen());
		EXPECT_TRUE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());

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
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices, nullptr);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		const VertexVector vertices{
			new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
			new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
		};
		HalfEdgeBuilder builder;
		const HalfEdgeList& edges = builder.createClosedFromVertices(vertices, nullptr);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
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
		const HalfEdgeList& edges = builder.createOpenFromVertices(vertices, nullptr);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getNormals().size());
	}

}

TEST(FaceBuilderTest, TestBuildQuad)
{
	VertexBuilder vBuilder;
	FaceBuilder builder(vBuilder);
	builder.buildQuad();
	const FaceVector& faces = builder.getFaces();
	EXPECT_EQ(1, faces.size());
	EXPECT_EQ(0, faces.front()->getId());
	EXPECT_EQ(nullptr, faces.front()->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirlceByNumber)
{
	VertexBuilder vBuilder;
	FaceBuilder builder(vBuilder);
	builder.buildCircleByNumber(3, 3);
	const FaceVector& faces = builder.getFaces();
	EXPECT_EQ(1, faces.size());
	EXPECT_EQ(0, faces.front()->getId());
	EXPECT_EQ(nullptr, faces.front()->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirleByAngle)
{

}