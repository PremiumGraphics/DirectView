#include "gtest/gtest.h"

#include "../Graphics/Polygon.h"

#include "PolygonFactory.h"

using namespace Crystal::Graphics;
using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PolygonFactoryTest, TestCreateFromObj)
{
	OBJFile file;
	const std::vector< Vector3d > positions = {
		Vector3d(0.0, 1.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 1.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	const std::vector< Vector3d > normals{
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0),
		Vector3d(0.0, 0.0, 1.0)
	};
	OBJFace face;
	face.setVertexIndices({ 0, 1, 2, 3 });
	face.setNormalIndices({ 0, 1, 2, 3 });
	OBJGroupSPtr group( new OBJGroup() );
	group->setPositions(positions);
	group->setNormals(normals);
	group->setFaces({ face });
	file.setGroups({ group });

	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonFactory factory(builder);
	const PolygonSPtrList& polygons = factory.create(file);


	PolygonBuilder bb;
	PolygonSPtr p = bb.buildQuad();

	EXPECT_EQ(1, polygons.size());
	EXPECT_EQ(4, polygons.front()->getVertices().size());
	EXPECT_EQ(1, polygons.front()->getFaces().size());

	VertexBuilder vBuilder;
	VertexSPtrVector vv = vBuilder.buildVerticesFromPositionsAndNormals(positions, normals);
	EXPECT_EQ(*vv[0], *p->getVertices()[0]);
	EXPECT_EQ(*vv[1], *p->getVertices()[1]);
	//EXPECT_EQ(*vv[1], *p->getVertices()[1]);
	//EXPECT_EQ(*vv[2], *p->getVertices()[2]);
}

TEST(PolygonFactoryTest, TestCreateFromSTL)
{
	STLFile file;
	STLCell cell;
	const Vector3d normal(0.0, 0.0, 0.0);
	cell.setNormal(normal);
	const std::vector< Vector3d > positions = {
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 1.0)
	};
	cell.setPositions(positions);
	cell.setNormal(Vector3d(1.0, 0.0, 0.0));
	file.setCells(STLCellVector{ cell });

	PolygonBuilderSPtr builder(new PolygonBuilder());
	PolygonFactory factory(builder);
	const PolygonSPtrList& polygons = factory.create(file);

	EXPECT_EQ( 1, polygons.size());
	EXPECT_NE( nullptr, polygons.front()->getMaterial());
	EXPECT_EQ(1, polygons.front()->getFaces().size());
	EXPECT_EQ(3, polygons.front()->getFaces().front()->getEdges().size());
	EXPECT_EQ( 3, polygons.front()->getVertices().size() );

	//EXPECT_EQ( expected.getNormals() ,actual->getNormals() );
	//EXPECT_EQ( expected, *actual );
	//delete actual;
}