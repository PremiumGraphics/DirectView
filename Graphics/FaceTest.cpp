#include "gtest/gtest.h"

#include "Face.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;


TEST(FaceTest, TestConstruct)
{
	const VertexVector vertices{
		VertexSPtr( new Vertex(Vector3d(0.0, 0.0, 0.0), 0) ),
		VertexSPtr(new Vertex(Vector3d(1.0, 0.0, 0.0), 1) )
	};
	Face f(0);
	EXPECT_EQ(nullptr, f.getPolygon());
}

TEST(FaceTest, TestIsClosed)
{
	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildOpenFromVertices();
		Face f(edges, 0);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildClosedFromVertices(vBuilder.getVertices());
		Face f(edges, 0);
		EXPECT_FALSE(f.isOpen());
		EXPECT_TRUE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());

	}
	//Face f;
}

TEST(FaceTest, TestGetNormals)
{
	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 0.0) );
		vBuilder.build(Vector3d(1.0, 0.0, 0.0), Vector3d( 0.0, 0.0, 0.0) );
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildOpenFromVertices();
		Face f(edges, 0);
		EXPECT_EQ(2, f.getNormals().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

}

TEST(FaceBuilderTest, TestBuildQuad)
{
	VertexBuilder vBuilder;
	HalfEdgeBuilder eBuilder(vBuilder);
	FaceBuilder builder( eBuilder);
	std::shared_ptr< Face > f( builder.buildQuad() );
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirlceByNumber)
{
	VertexBuilder vBuilder;
	HalfEdgeBuilder eBuilder(vBuilder);
	FaceBuilder builder( eBuilder);
	std::shared_ptr< Face > f(builder.buildCircleByNumber(3, 3));
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirleByAngle)
{

}