#include "gtest/gtest.h"

#include "Face.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;


TEST(FaceTest, TestConstruct)
{
	const VertexSPtrVector vertices{
		VertexSPtr( new Vertex(Vector3d(0.0, 0.0, 0.0), 0) ),
		VertexSPtr(new Vertex(Vector3d(1.0, 0.0, 0.0), 1) )
	};
	Face f(0);
	EXPECT_EQ(nullptr, f.getPolygon());
}

TEST(FaceTest, TestIsClosed)
{
	{
		HalfEdgeBuilder builder;
		VertexBuilderSPtr vBuilder = builder.getVertexBuilder();
		const VertexSPtrVector vv{
			vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
			vBuilder->build(Vector3d(1.0, 0.0, 0.0))
		};

		const HalfEdgeSPtrList& edges = builder.buildOpenFromVertices(vv);
		Face f(edges, 0);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		HalfEdgeBuilder builder;
		VertexBuilderSPtr vBuilder = builder.getVertexBuilder();
		const VertexSPtrVector vv{
			vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
			vBuilder->build(Vector3d(1.0, 0.0, 0.0))
		};
		const HalfEdgeSPtrList& edges = builder.buildClosedFromVertices(vv);
		Face f(edges, 0);
		EXPECT_FALSE(f.isOpen());
		EXPECT_TRUE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());

	}
	//Face f;
}

TEST(FaceTest, TestGetCenter)
{
	HalfEdgeBuilder builder;
	VertexBuilderSPtr vBuilder = builder.getVertexBuilder();
	const VertexSPtrVector vv{
		vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
		vBuilder->build(Vector3d(1.0, 0.0, 0.0))
	};

	const HalfEdgeSPtrList& edges = builder.buildClosedFromVertices(vv);
	Face f(edges, 0);
	EXPECT_EQ( Vector3d( 0.5, 0.0, 0.0), f.getCenter());
}

TEST(FaceBuilderTest, TestBuildQuad)
{
	FaceBuilder builder;
	FaceSPtr f( builder.buildQuad() );
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
	EXPECT_EQ(1, builder.getFaces().size());
}

TEST(FaceBuilderTest, TestBuildCirlceByNumber)
{
	FaceBuilder builder;
	FaceSPtr f( builder.buildCircleByNumber(3, 3));
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
	EXPECT_EQ(1, builder.getFaces().size());
}

TEST(FaceBuilderTest, TestBuildCirleByAngle)
{

}

TEST(FaceBuilderTest, TestBuildOffset)
{
	FaceBuilder builder;
	FaceSPtr original( builder.buildQuad() );

	FaceSPtr dest = builder.createOffset(original);
	EXPECT_EQ(2, builder.getFaces().size());
	EXPECT_EQ(8, builder.getVertices().size());

	EXPECT_EQ(4, dest->getEdges().size());
}

TEST(FaceBuilderTest, TestBuildSides)
{
	FaceBuilder builder;
	FaceSPtr original(builder.buildQuad());

	FaceSPtr dest = builder.createOffset(original);

	const FaceSPtrVector& faces = builder.buildSides(original, dest);
	EXPECT_EQ(4, faces.size());
}