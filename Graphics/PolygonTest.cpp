#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestCreateTriangle)
{
	std::unique_ptr< Polygon > p( Polygon::createTriangle() );
	EXPECT_EQ(3, p->getPositions().size());
	EXPECT_EQ(3, p->getNormals().size());

	const FaceVector& faces = p->getFaces();
	Face f;
	f.setNormalIds({ 0, 1, 2 });
	f.setVertexIds({ 0, 1, 2 });


	EXPECT_EQ(f, p->getFaces().front());
}

TEST(PolygonTest, TestCreateQuad)
{
	std::unique_ptr< Polygon > p( Polygon::createQuad(1.0, 1.0) );

	const Vector3dVector positions{
		Vector3d(-0.5, 0.5, 0.0),
		Vector3d(-0.5, -0.5, 0.0),
		Vector3d(0.5, -0.5, 0.0),
		Vector3d(0.5, 0.5, 0.0)
	};
	const Vector3dVector normals{
		Vector3d( 0.0, 0.0, 1.0),
		Vector3d( 0.0, 0.0, 1.0),
		Vector3d( 0.0, 0.0, 1.0),
		Vector3d( 0.0, 0.0, 1.0)
	};

	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 1, 2, 3 });
	Polygon expected;
	expected.setFaces({ f });
	expected.setPositions(positions);
	expected.setNormals(normals);

	EXPECT_EQ( expected, *p );
}

TEST(PolygonTest, TestCreateCircle)
{
	std::unique_ptr< Polygon > p(Polygon::createCircle(1.0f, 60.0f));
	EXPECT_EQ(6, p->getPositions().size());
}

TEST(PolygonTest, TestCreateCylinder)
{
	std::unique_ptr< Polygon > p(Polygon::createCylinder(1.0f, 1.0f));

}

TEST(PolygonTest, TestScale)
{
	Polygon p;
	p.setPositions( { Vector3d(1.0, 1.0, 1.0) } );
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const Vector3dVector expected = { Vector3d(0.1f, 0.01f, 10.0f) };
	const Vector3dVector& actual = p.getPositions();
	EXPECT_EQ( expected, actual );
}

TEST(PolygonTest, TestMove)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 2.0, 3.0) });

	p.move(Vector3d(1.0, 10.0, 100.0));

	const Vector3dVector expected = { Vector3d(2.0, 12.0, 103.0) };
	const Vector3dVector& actual = p.getPositions();

	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateX)
{
	/*
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.rotateX(180.0f);

	const Vector3dVector& actual = p.getPositions();
	*/
}