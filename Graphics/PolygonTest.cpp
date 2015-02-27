#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include <memory>

#include "../Math/Vector3d.h"
using namespace Crystal::Math;


using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonTest, TestCreateTriangle)
{
	std::unique_ptr< Polygon > p( Polygon::createTriangle() );

	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(std::sin(120.0 * Tolerances::getPI() / 180.0), std::cos(120.0 * Tolerances::getPI() / 180.0), 0.0),
		Vector3d(std::sin(240.0 * Tolerances::getPI() / 180.0), std::cos(240.0 * Tolerances::getPI() / 180.0), 0.0)
	};

	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};
	//const Vector3d expected(-0.5, 0.5, 0.0);

	expected.setPositions(positions);
	expected.setNormals(normals);
	const FaceVector& faces = p->getFaces();
	Face f;
	f.setNormalIds({ 0, 1, 2 });
	f.setVertexIds({ 0, 1, 2 });
	expected.setFaces({ f });

	EXPECT_EQ(  expected, *p );
}


TEST(PolygonTest, TestCreateCircleByNumber)
{
	std::unique_ptr< Polygon > p(Polygon::createCricleByNumber(1.0f, 4));
	const Vector3dVector& actual = p->getPositions();
	
	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setPositions(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 1, 2, 3 });
	expected.setFaces({ f });
	EXPECT_EQ( expected, *p );
}

TEST(PolygonTest, TestCreateCircleByAngle)
{
	std::unique_ptr< Polygon > p(Polygon::createCircleByAngle(1.0f, 90.0f));
	const Vector3dVector& actual = p->getPositions();

	Polygon expected;
	const Vector3dVector positions{
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(-1.0, 0.0, 0.0)
	};
	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};
	expected.setPositions(positions);
	expected.setNormals(normals);
	Face f;
	f.setVertexIds({ 0, 1, 2, 3 });
	f.setNormalIds({ 0, 1, 2, 3 });
	expected.setFaces({ f });
	EXPECT_EQ(expected, *p);
}

TEST(PolygonTest, TestCreateCylinder)
{
	std::unique_ptr< Polygon > p(Polygon::createCylinder(1.0f, 1.0f));
	EXPECT_EQ(3, p->getFaces().size());
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

TEST(PolygonTest, TestScaleWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 1.0, 1.0) });
	p.setCenter(Vector3d(1.0, 1.0, 1.0));
	p.scale(Vector3d(0.1f, 0.01f, 10.0f));

	const Vector3dVector expected = { Vector3d(1.0f, 1.0f, 1.0f) };
	const Vector3dVector& actual = p.getPositions();
	EXPECT_EQ(expected, actual);
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
	Polygon p;
	p.setPositions({ Vector3d(0.0, 0.0, 1.0) });
	p.rotateX(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(0.0, 0.0, -1.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateXWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(0.0, 0.0, 1.0) });
	p.setCenter(Vector3d(0.0, 0.0, 1.0));
	p.rotateX(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(0.0, 0.0, 1.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateY)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.rotateY(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(-1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateYWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.setCenter(Vector3d(1.0, 0.0, 0.0));
	p.rotateY(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateZ)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.rotateZ(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(-1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}

TEST(PolygonTest, TestRotateZWithCenter)
{
	Polygon p;
	p.setPositions({ Vector3d(1.0, 0.0, 0.0) });
	p.setCenter(Vector3d(1.0, 0.0, 0.0));
	p.rotateZ(180.0);

	const Vector3dVector& actual = p.getPositions();

	const std::vector< Vector3d > expected{ Vector3d(1.0, 0.0, 0.0) };
	EXPECT_EQ(expected, actual);
}