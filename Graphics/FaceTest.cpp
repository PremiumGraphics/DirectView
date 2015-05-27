#include "gtest/gtest.h"

#include "Face.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(FaceTest, TestConstruct)
{
	const VertexSPtrVector<T> vertices{
		VertexSPtr<T>( new Vertex<T>(Vector3d<float>(0.0, 0.0, 0.0) ) ),
		VertexSPtr<T>(new Vertex<T>(Vector3d<float>(1.0, 0.0, 0.0) ) )
	};
	Face f(0);
	EXPECT_EQ(nullptr, f.getPolygon());
}
