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
