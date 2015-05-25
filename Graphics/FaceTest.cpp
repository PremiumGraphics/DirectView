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
