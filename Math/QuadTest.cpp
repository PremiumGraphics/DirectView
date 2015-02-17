#include "gtest/gtest.h"
 
#include "../Math/Quad.h"

using namespace Crystal::Math;

 
TEST( QuadTest, TestConstruct )
{
	Quad q;
	EXPECT_EQ( q.getCenter(), Vector3d( 0.0f, 0.0f, 0.0f ) );
}