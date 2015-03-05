#include "gtest/gtest.h"

#include "PolygonBuilder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonBuilderTest, TestBuildQuad)
{
	std::unique_ptr< Polygon > p( PolygonBuilder::buildQuad() );

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
	std::unique_ptr< Polygon > p( PolygonBuilder::buildBox() );

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
	std::unique_ptr< Polygon > p( PolygonBuilder::buildCircleByAngle( 1.0f, 90.0f) );
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
	std::unique_ptr< Polygon > p(PolygonBuilder::buildTriangle());

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
	std::unique_ptr< Polygon > p(PolygonBuilder::buildCircleByNumber(1.0f, 4));
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
	std::unique_ptr< Polygon > p( PolygonBuilder::buildCylinder(3) );

	EXPECT_EQ(6, p->getVertices().size());
	EXPECT_EQ(5, p->getFaces().size());
}

TEST(PolygonBuilderTest, TestBuildCone)
{
	std::unique_ptr< Polygon > p( PolygonBuilder::buildCone(3) );
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(4, p->getFaces().size());
}