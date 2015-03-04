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

TEST(VertexTest, TestCreateVerticesFromPositions)
{
	const Vector3dVector positions{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
	};

	const VertexVector& actual = Vertex::createVerticesFromPositions(positions);

	const VertexVector expected{
		new Vertex(Vector3d(0.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), 1)
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

	const VertexVector& actual = Vertex::createVerticesFromPositionsAndNormals(positions, normals);

	const VertexVector expected{
		new Vertex(Vector3d(0.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), 0),
		new Vertex(Vector3d(1.0, 0.0, 0.0), Vector3d(1.0, 0.0, 0.0), 1)
	};

	EXPECT_TRUE( VerticesAreSame(expected, actual) );
}