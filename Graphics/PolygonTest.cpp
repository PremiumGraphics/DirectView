#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector3d.h"
#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(PolygonTest, TestConstruct)
{
	Polygon p(0, nullptr);
	EXPECT_EQ( nullptr, p.getMaterial() );
}


TEST(PolygonTest, TestMove)
{
	Polygon p(0, nullptr);
	p.setVertices({ VertexSPtr(new Vertex<T>(Vector3d<T>(1.0, 2.0, 3.0), 0)) });

	p.move(Vector3d<T>(1.0, 10.0, 100.0));

	const VertexSPtrVector expected = { VertexSPtr( new Vertex<T>(Vector3d<T>(2.0, 12.0, 103.0), 0 ) ) };
	const VertexSPtrVector& actual = p.getVertices();

	EXPECT_TRUE(VerticesAreSame(expected, actual));
}