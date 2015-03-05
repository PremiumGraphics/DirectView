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

	EXPECT_EQ(1, p->getFaces().size());
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(4, p->getFaces().front()->getEdges().size());

	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};

	const VertexVector& positions = Vertex::createVerticesFromPositionsAndNormals(
	{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	},
	normals);
	
	EXPECT_TRUE( VerticesAreSame( positions, p->getVertices() ) );
}

TEST(PolygonBuilderTest, TestBuildBox)
{
	PolygonBuilder builder;
	builder.buildBox();
	std::unique_ptr< Polygon > p( builder.getPolygon());

	const VertexVector positions = Vertex::createVerticesFromPositions(
	{
		Vector3d(0.0, 1.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(1.0, 0.0, 1.0),
		Vector3d(1.0, 1.0, 1.0),
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	});

	EXPECT_EQ(8, p->getVertices().size());

	//EXPECT_TRUE( VerticesAreSame( positions, p->getVertices()) );
	EXPECT_EQ(6, p->getFaces().size());
}

TEST(PolygonBuilderTest, TestCreateCircleByAngle)
{
	PolygonBuilder builder;
	builder.buildCircleByAngle(1.0, 90.0);
	std::unique_ptr< Polygon > p(builder.getPolygon());
	EXPECT_EQ(4, p->getVertices().size());

	/*

	Polygon expected;
	const VertexVector& positions = Vertex::createVerticesFromPositions(
	{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	}
	);
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setVertices(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	expected.setFaces({ f });
	EXPECT_EQ(expected, *p);
	*/
}


TEST(PolygonBuilderTest, TestBuildTriangle)
{
	PolygonBuilder builder;
	builder.buildTriangle();
	std::unique_ptr< Polygon > p(builder.getPolygon());

	EXPECT_EQ( 3, p->getVertices().size());
	/*
	Polygon expected;
	const VertexVector positions = Vertex::createVerticesFromPositions(
	{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(std::sin(120.0f * Tolerances::getPI() / 180.0f), std::cos(120.0f * Tolerances::getPI() / 180.0f), 0.0),
		Vector3d(std::sin(240.0f * Tolerances::getPI() / 180.0f), std::cos(240.0f * Tolerances::getPI() / 180.0f), 0.0)
	});


	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	//const Vector3d expected(-0.5, 0.5, 0.0);

	expected.setVertices(positions);
	expected.setNormals(normals);
	const FaceVector& faces = p->getFaces();

	expected.setFaces({ f });

	EXPECT_EQ(expected, *p);
	*/
}

TEST(PolygonBuilderTest, TestBuildCircleByNumber)
{
	PolygonBuilder builder;
	builder.buildCircleByNumber(1.0, 4);
	std::unique_ptr< Polygon > p(builder.getPolygon());
	EXPECT_EQ(4, p->getVertices().size());

	/*
	const VertexVector& actual = p->getVertices();

	Polygon expected;
	const VertexVector positions = Vertex::createVerticesFromPositions(
	{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	});
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setVertices(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 0, 0, 0 });
	expected.setFaces({ f });
	EXPECT_EQ(expected, *p);
	*/
}


TEST(PolygonBuilderTest, TestBuildCylinder)
{
	PolygonBuilder builder;
	builder.buildCylinder(3);
	std::unique_ptr< Polygon > p(builder.getPolygon());

	EXPECT_EQ(6, p->getVertices().size());
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