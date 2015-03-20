#include "gtest/gtest.h"

#include "PolygonBuilder.h"

#include <memory>

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(PolygonBuilderTest, TestBuildQuad)
{
	PolygonBuilderSPtr builder( new PolygonBuilder() );
	PolygonSPtr p(builder->buildQuad() );

	EXPECT_EQ(1, builder->getPolygons().size());

	EXPECT_EQ(1, p->getFaces().size());
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(4, p->getFaces().front()->getEdges().size());
	EXPECT_EQ(0, p->getId());
	EXPECT_EQ( p.get(), p->getFaces().front()->getPolygon().get() );

	const Vector3dVector normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};

	VertexBuilderSPtr vBuilder2( new VertexBuilder() );
	const VertexSPtrVector& positions = vBuilder2->buildVerticesFromPositionsAndNormals(
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
	PolygonBuilderSPtr builder( new PolygonBuilder() );
	PolygonSPtr p(builder->buildBox());

	EXPECT_EQ(1, builder->getPolygons().size());

	VertexBuilder vBuilder2;
	const VertexSPtrVector positions = vBuilder2.buildVerticesFromPositions(
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
	EXPECT_EQ(p.get(), p->getFaces().front()->getPolygon().get());

	//EXPECT_TRUE( VerticesAreSame( positions, p->getVertices()) );
	EXPECT_EQ(6, p->getFaces().size());

	EXPECT_EQ(4, p->getFaces().front()->getVertices().size());
	EXPECT_EQ(4, p->getFaces().back()->getVertices().size());
}

TEST(PolygonBuilderTest, TestCreateCircleByAngle)
{
	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonSPtr p(builder->buildCircleByAngle(1.0f, 90.0f));

	EXPECT_EQ(1, builder->getPolygons().size());

	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(p.get(), p->getFaces().front()->getPolygon().get());

	const Vertex v0(
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		0
		);
	const Vertex v1(
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		1);
	const Vertex v2(
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		2);
	const Vertex v3(
		Vector3d(-1.0, 0.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		3
		);

	EXPECT_EQ(v0, *(p->getVertices()[0]));
	EXPECT_EQ(v1, *(p->getVertices()[1]));
	EXPECT_EQ(v2, *(p->getVertices()[2]));
	EXPECT_EQ(v3, *(p->getVertices()[3]));
}


TEST(PolygonBuilderTest, TestBuildTriangle)
{
	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonSPtr p(builder->buildTriangle());

	EXPECT_EQ(1, builder->getPolygons().size());

	EXPECT_EQ(3, p->getVertices().size());

	const Vertex v0(
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		0
		);
	const Vertex v1(
		Vector3d(std::sin(120.0f * Tolerances::getPI() / 180.0f), std::cos(120.0f * Tolerances::getPI() / 180.0f), 0.0),
		Vector3d(0.0, 0.0, 1.0),
		1);
	const Vertex v2(
		Vector3d(std::sin(240.0f * Tolerances::getPI() / 180.0f), std::cos(240.0f * Tolerances::getPI() / 180.0f), 0.0),
		Vector3d(0.0, 0.0, 1.0),
		2);


	EXPECT_EQ(v0, *(p->getVertices()[0]));
	EXPECT_EQ(v1, *(p->getVertices()[1]));
	EXPECT_EQ(v2, *(p->getVertices()[2]));


}

TEST(PolygonBuilderTest, TestBuildCircleByNumber)
{
	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonSPtr p(builder->buildCircleByNumber(1.0f, 4));
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(p.get(), p->getFaces().front()->getPolygon().get());

	EXPECT_EQ(1, builder->getPolygons().size());

	const Vertex v0(
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		0
		);
	const Vertex v1(
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		1);
	const Vertex v2(
		Vector3d(0.0, -1.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		2);
	const Vertex v3(
		Vector3d(-1.0, 0.0, 0.0),
		Vector3d(0.0, 0.0, 1.0),
		3
		);

	EXPECT_EQ(v0, *(p->getVertices()[0]));
	EXPECT_EQ(v1, *(p->getVertices()[1]));
	EXPECT_EQ(v2, *(p->getVertices()[2]));
	EXPECT_EQ(v3, *(p->getVertices()[3]));
}


TEST(PolygonBuilderTest, TestBuildCylinder)
{
	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonSPtr p(builder->buildCylinder(3));
	EXPECT_EQ(p.get(), p->getFaces().front()->getPolygon().get());

	EXPECT_EQ(1, builder->getPolygons().size());

	//EXPECT_EQ(6, p->getVertices().size());
	//EXPECT_EQ(5, p->getFaces().size());
}

TEST(PolygonBuilderTest, TestBuildCone)
{
	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonSPtr p(builder->buildCone(3));

	EXPECT_EQ(1, builder->getPolygons().size());

	EXPECT_EQ(p.get(), p->getFaces().front()->getPolygon().get());
	EXPECT_EQ(4, p->getVertices().size());
	EXPECT_EQ(4, p->getFaces().size());
	EXPECT_EQ(0, p->getId());
}