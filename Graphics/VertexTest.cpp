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
