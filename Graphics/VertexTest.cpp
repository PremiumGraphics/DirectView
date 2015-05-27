#include <gtest/gtest.h>

#include "../Graphics/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(VertexTest, TestConstruct)
{
	Vertex<T> v( Vector3d<T>( 0.0, 0.0, 0.0 ) );
	EXPECT_EQ( Vector3d<T>(0.0, 0.0, 0.0), v.getPosition() );
	EXPECT_EQ( Vector3d<T>(0.0, 0.0, 0.0), v.getTexCoord() );
}
