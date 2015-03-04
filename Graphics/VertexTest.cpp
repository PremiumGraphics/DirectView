#include <gtest/gtest.h>

#include "../Graphics/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(VertexTest, TestConstruct)
{
	Vertex v( Vector3d( 0.0, 0.0, 0.0 ), 0 );
	EXPECT_EQ( Vector3d(0.0, 0.0, 0.0), v.getPosition());
	EXPECT_EQ(0, v.getId());
}

TEST(VertexTest, TestCreateVerticesFromPositions)
{
	Vector3dVector positions{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
	};

	const VertexVector& actual = Vertex::createVerticesFromPositions(positions);
	EXPECT_EQ(2, actual.size());
}