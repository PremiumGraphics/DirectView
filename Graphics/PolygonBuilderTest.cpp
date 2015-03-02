#include "gtest/gtest.h"

#include "PolygonBuilder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonBuilderTest, TestBuildQuad)
{
	PolygonBuilder builder;
	builder.buildQuad();
	std::unique_ptr< Polygon > p( builder.getPolygon() );

	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};

	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	Polygon expected;
	expected.setFaces({ f });
	expected.setPositions(positions);
	expected.setNormals(normals);

	EXPECT_EQ(expected, *p);
}

TEST(PolygonBuilderTest, TestBuildBox)
{
	PolygonBuilder builder;
	builder.buildBox();
	std::unique_ptr< Polygon > p( builder.getPolygon());

	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(1.0, 0.0, 1.0),
		Vector3d(1.0, 1.0, 1.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};

	EXPECT_EQ(positions, p->getPositions());
	EXPECT_EQ(6, p->getNormals().size());
	EXPECT_EQ(6, p->getFaces().size());
}

TEST(PolygonTest, TestCreateCircleByAngle)
{
	PolygonBuilder builder;
	builder.buildCircleByAngle(1.0, 90.0);
	std::unique_ptr< Polygon > p(builder.getPolygon());

	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setPositions(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	expected.setFaces({ f });
	EXPECT_EQ(expected, *p);
}

TEST(PolygonTest, TestCreateTriangle)
{
	PolygonBuilder builder;
	builder.buildTriangle();
	std::unique_ptr< Polygon > p(builder.getPolygon());

	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(std::sin(120.0f * Tolerances::getPI() / 180.0f), std::cos(120.0f * Tolerances::getPI() / 180.0f), 0.0),
		Vector3d(std::sin(240.0f * Tolerances::getPI() / 180.0f), std::cos(240.0f * Tolerances::getPI() / 180.0f), 0.0)
	};

	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	//const Vector3d expected(-0.5, 0.5, 0.0);

	expected.setPositions(positions);
	expected.setNormals(normals);
	const FaceVector& faces = p->getFaces();
	Face f;
	f.setVertexIds({ 0, 1, 2 });
	f.setNormalIds({ 0, 0, 0 });

	expected.setFaces({ f });

	EXPECT_EQ(expected, *p);
}


TEST(PolygonTest, TestCreateCircleByNumber)
{
	PolygonBuilder builder;
	builder.buildCircleByNumber(1.0, 4);
	std::unique_ptr< Polygon > p(builder.getPolygon());
	const Vector3dVector& actual = p->getPositions();

	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setPositions(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	expected.setFaces({ f });
	EXPECT_EQ(expected, *p);
}
