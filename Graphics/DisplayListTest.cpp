#include "gtest/gtest.h"

#include "../Graphics/DisplayList.h"
#include "../Graphics/Material.h"
#include "../Graphics/Polygon.h"
#include "../Graphics/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

TEST(DisplayTest, TestConstructByPosition)
{
	DisplayList list({ Vector3d(0.0, 0.0, 0.0) });
	const std::vector< float >& actual = list.getPositions();
	const std::vector< float > expected{ 0.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormal)
{
	DisplayList list(
		{ Vector3d(0.0, 0.0, 0.0) },
		{ Vector3d(1.0, 0.0, 0.0) }
	);
	const std::vector< float >& actual = list.getNormals();
	const std::vector< float > expected{ 1.0, 0.0, 0.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayTest, TestConstructByPosNormalTexCoord)
{
	DisplayList list(
		{ Vector3d(0.0, 0.0, 0.0) },
		{ Vector3d(1.0, 0.0, 0.0) },
		{ Vector3d(1.0, 1.0, 1.0) }
	);
	const std::vector< float >& actual = list.getTexCoords();
	const std::vector< float > expected{ 1.0, 1.0, 1.0 };
	EXPECT_EQ(expected, actual);
}

TEST(DisplayListTest, TestAddFace)
{
	FaceBuilderSPtr builder( new FaceBuilder() );
	FaceSPtr f = builder->buildQuad();

	DisplayList list;
	list.add(f.get(), ColorRGBA<float>::Black());

	const std::vector<unsigned int> expected{ 0, 0, 0, 0 };
	EXPECT_EQ( expected, list.getFaceIds());
}

TEST(DisplayListTest, TestAddPolygon)
{
	//FaceBuilderSPtr fBuilder( new FaceBuilder() );
	PolygonBuilder builder;
	PolygonSPtr p = builder.buildQuad();
	p->setMaterial(MaterialSPtr(new Material(0)));

	DisplayList list;
	list.add( p );

	{
		const std::vector<unsigned int> expected{ 0, 0, 0, 0 };
		EXPECT_EQ(1, list.getIds().size());
		EXPECT_EQ(expected, list.getPolygonIds());
	}

	{
		const std::vector<unsigned int> expected{ 0, 1, 2, 3 };
		EXPECT_EQ( expected, list.getVertexIds() );
	}


	{
		const std::vector<float> expected{
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0,
			0.0, 0.0, 0.0
		};
		EXPECT_EQ(expected, list.getColors() );
	}

	list.clear();
	Triangle t;
	p = builder.build(t);
	p->setMaterial(MaterialSPtr(new Material(1)));

	list.add(p);

	{
		const std::vector<unsigned int> expected{ 0, 1, 2, 3, 4, 5, 6 };
		EXPECT_EQ( expected, list.getVertexIds() );
	}


}

/*
TEST(FaceTest, TestGetPositions)
{
	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildOpenFromVertices();
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}

	{
		VertexBuilder vBuilder;
		vBuilder.build(Vector3d(0.0, 0.0, 0.0));
		vBuilder.build(Vector3d(1.0, 0.0, 0.0));
		HalfEdgeBuilder builder(vBuilder);
		const HalfEdgeList& edges = builder.buildClosedFromVertices(vBuilder.getVertices());
		Face f(edges, 0);
		EXPECT_EQ(2, f.getPositions().size());
		EXPECT_EQ(nullptr, f.getPolygon());
	}
}
*/