#include <gtest/gtest.h>

#include "../Graphics/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(VertexTest, TestConstruct)
{
	Vertex v( Vector3d( 0.0, 0.0, 0.0 ), 0 );
	EXPECT_EQ( Vector3d(0.0, 0.0, 0.0), v.getPosition() );
	EXPECT_EQ( 0, v.getId() );
	EXPECT_EQ( Vector3d(0.0, 0.0, 0.0), v.getTexCoord() );
}

TEST(VertexBuilderTest, TestBuildVerticesFromPositions)
{
	const Vector3dVector positions{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
	};

	VertexBuilder builder;
	const VertexSPtrVector& actual = builder.buildVerticesFromPositions(positions);

	const VertexSPtrVector expected{
		VertexSPtr( new Vertex(Vector3d(0.0, 0.0, 0.0), 0) ),
		VertexSPtr( new Vertex(Vector3d(1.0, 0.0, 0.0), 1) )
	};

	EXPECT_TRUE( VerticesAreSame( expected, actual ) );
}

TEST(VertexTest, TestCreateVerticesFromPositionsAndNormals)
{
	const Vector3dVector positions{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
	};

	const Vector3dVector normals{
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0)
	};

	VertexBuilder vBuilder;
	const VertexSPtrVector& actual = vBuilder.buildVerticesFromPositionsAndNormals(positions, normals);

	const VertexSPtrVector expected{
		VertexSPtr( new Vertex(Vector3d(0.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), 0) ),
		VertexSPtr( new Vertex(Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), 1) )
	};

	EXPECT_TRUE( VerticesAreSame(expected, actual) );
}