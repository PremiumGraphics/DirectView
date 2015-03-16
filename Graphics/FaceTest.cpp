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
		VertexBuilderSPtr vBuilder( new VertexBuilder() );
		const VertexSPtrVector vv{
			vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
			vBuilder->build(Vector3d(1.0, 0.0, 0.0))
		};
		HalfEdgeBuilderSPtr builder( new HalfEdgeBuilder( vBuilder ));
		const HalfEdgeSPtrList& edges = builder->buildOpenFromVertices(vv);
		Face f(edges, 0);
		EXPECT_TRUE(f.isOpen());
		EXPECT_FALSE(f.isClosed());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		VertexBuilderSPtr vBuilder( new VertexBuilder() );
		const VertexSPtrVector vv{
			vBuilder->build(Vector3d(0.0, 0.0, 0.0)),
			vBuilder->build(Vector3d(1.0, 0.0, 0.0))
		};
		HalfEdgeBuilderSPtr builder( new HalfEdgeBuilder( vBuilder ) );
		const HalfEdgeSPtrList& edges = builder->buildClosedFromVertices(vv);
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
		VertexBuilderSPtr vBuilder(new VertexBuilder());
		const VertexSPtrVector vv{
			vBuilder->build(Vector3d(0.0, 0.0, 0.0), Vector3d(0.0, 0.0, 0.0)),
			vBuilder->build(Vector3d(1.0, 0.0, 0.0), Vector3d(0.0, 0.0, 0.0))
		};
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeSPtrList& edges = builder.buildOpenFromVertices(vv);
		Face f(edges, 0);
		EXPECT_EQ(2, f.getNormals().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

}

TEST(FaceBuilderTest, TestBuildQuad)
{
	HalfEdgeBuilderSPtr eBuilder( new HalfEdgeBuilder() );
	FaceBuilder builder( eBuilder);
	std::shared_ptr< Face > f( builder.buildQuad() );
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirlceByNumber)
{
	HalfEdgeBuilderSPtr eBuilder( new HalfEdgeBuilder() );
	FaceBuilder builder( eBuilder);
	std::shared_ptr< Face > f(builder.buildCircleByNumber(3, 3));
	EXPECT_EQ(0, f->getId());
	EXPECT_EQ(nullptr, f->getPolygon());
}

TEST(FaceBuilderTest, TestBuildCirleByAngle)
{

}