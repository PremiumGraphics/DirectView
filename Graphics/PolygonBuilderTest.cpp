#include "gtest/gtest.h"

#include "PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonBuilderTest, TestBuildQuad)
{
	PolygonBuilder builder;
	builder.buildQuad();
	Polygon* p = builder.getPolygon();

	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};

	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 1, 2, 3 });
	Polygon expected;
	expected.setFaces({ f });
	expected.setPositions(positions);
	expected.setNormals(normals);

	EXPECT_EQ(expected, *p);
}