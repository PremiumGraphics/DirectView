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

	const VertexVector positions{
		Vertex( Vector3d(0.0, 1.0, 0.0),0),
		Vertex( Vector3d(0.0, 0.0, 0.0),1),
		Vertex( Vector3d(1.0, 0.0, 0.0),2),
		Vertex( Vector3d(1.0, 1.0, 0.0),3 )
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

	const VertexVector positions{
		Vertex(Vector3d(0.0, 1.0, 1.0),0),
		Vertex(Vector3d(0.0, 0.0, 1.0),1),
		Vertex(Vector3d(1.0, 0.0, 1.0),2),
		Vertex(Vector3d(1.0, 1.0, 1.0),3),
		Vertex(Vector3d(0.0, 1.0, 0.0),4),
		Vertex(Vector3d(0.0, 0.0, 0.0),5),
		Vertex(Vector3d(1.0, 0.0, 0.0),6),
		Vertex(Vector3d(1.0, 1.0, 0.0),7),
	};

	EXPECT_EQ(positions, p->getVertices());
	EXPECT_EQ(6, p->getNormals().size());
	EXPECT_EQ(6, p->getFaces().size());
}

TEST(PolygonBuilderTest, TestCreateCircleByAngle)
{
	PolygonBuilder builder;
	builder.buildCircleByAngle(1.0, 90.0);
	std::unique_ptr< Polygon > p(builder.getPolygon());

	Polygon expected;
	const VertexVector positions{
		Vertex(Vector3d(0.0, 1.0, 0.0), 0 ),
		Vertex(Vector3d(1.0, 0.0, 0.0), 1 ),
		Vertex(Vector3d(0.0, -1.0, 0.0),2 ),
		Vertex(Vector3d(-1.0, 0.0, 0.0),3 )
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


TEST(PolygonBuilderTest, TestBuildTriangle)
{
	PolygonBuilder builder;
	builder.buildTriangle();
	std::unique_ptr< Polygon > p(builder.getPolygon());

	Polygon expected;
	const VertexVector positions{
		Vertex(Vector3d(0.0, 1.0, 0.0),0),
		Vertex(Vector3d(std::sin(120.0f * Tolerances::getPI() / 180.0f), std::cos(120.0f * Tolerances::getPI() / 180.0f), 0.0), 1),
		Vertex(Vector3d(std::sin(240.0f * Tolerances::getPI() / 180.0f), std::cos(240.0f * Tolerances::getPI() / 180.0f), 0.0), 2)
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

TEST(PolygonBuilderTest, TestBuildCircleByNumber)
{
	PolygonBuilder builder;
	builder.buildCircleByNumber(1.0, 4);
	std::unique_ptr< Polygon > p(builder.getPolygon());
	const VertexVector& actual = p->getVertices();

	Polygon expected;
	const VertexVector positions{
		Vertex( Vector3d(0.0, 1.0, 0.0), 0 ),
		Vertex( Vector3d(1.0, 0.0, 0.0), 1 ),
		Vertex( Vector3d(0.0, -1.0, 0.0), 2 ),
		Vertex( Vector3d(-1.0, 0.0, 0.0), 3 )
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


TEST(PolygonBuilderTest, TestBuildCylinder)
{
	PolygonBuilder builder;
	builder.buildCylinder(3);
	std::unique_ptr< Polygon > p(builder.getPolygon());

	EXPECT_EQ(6, p->getVertices().size());
	EXPECT_EQ(5, p->getNormals().size());
	EXPECT_EQ(5, p->getFaces().size());
}

TEST(PolygonBuilderTest, TestBuildCone)
{
	PolygonBuilder builder;
	builder.buildCone(3);
	std::unique_ptr< Polygon > p(builder.getPolygon());
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(4, p->getFaces().size());
}