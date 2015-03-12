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
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 1.0)
	};
	OBJFace face;
	face.setVertexIndices({ 0, 1, 2 });
	OBJGroup group;
	group.setPositions(positions);
	group.setFaces( {face} );
	file.setGroups({ group });

	FaceBuilderSPtr fBuilder(new FaceBuilder());
	PolygonBuilder builder(fBuilder);
	PolygonFactory factory(builder);
	const PolygonSPtrList& polygons = factory.create(file);

	EXPECT_EQ(1, polygons.size());
	EXPECT_EQ(3, polygons.front()->getVertices().size());
	EXPECT_EQ(1, polygons.front()->getFaces().size());
	//Polygon expected;
	//expected.setPositions( positions );
	//Face f;
	//f.setVertexIds({ 0, 1, 2 });
	//expected.setFaces( { f } );
	//const Polygon* p = polygons.front().getPolygon();
	//const Material* m = polygons.front().getMaterial();
	//EXPECT_EQ( expected, *p );
	//EXPECT_EQ( nullptr, m );
	//delete p;
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

	VertexBuilder vBuilder;
	const HalfEdgeBuilderSPtr hBuilder(new HalfEdgeBuilder() );
	FaceBuilderSPtr fBuilder(new FaceBuilder());
	PolygonBuilder builder(fBuilder);
	PolygonFactory factory(builder);
	const PolygonSPtrList& polygons = factory.create(file);

	EXPECT_EQ( 1, polygons.size());
	EXPECT_EQ( nullptr, polygons.front()->getMaterial());
	EXPECT_EQ(1, polygons.front()->getFaces().size());
	EXPECT_EQ(3, polygons.front()->getFaces().front()->getEdges().size());
	EXPECT_EQ( 3, polygons.front()->getVertices().size() );

	//EXPECT_EQ( expected.getNormals() ,actual->getNormals() );
	//EXPECT_EQ( expected, *actual );
	//delete actual;
}