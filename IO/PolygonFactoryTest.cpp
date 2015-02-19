#include "gtest/gtest.h"

#include "PolygonFactory.h"

using namespace Crystal::Graphics;
using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PolygoGroupTest, Test)
{
	PolygonGroup group;
	EXPECT_EQ( nullptr, group.getPolygon() );
	EXPECT_EQ( nullptr, group.getMaterial() );
}

::std::ostream& operator<<(::std::ostream& os, const Polygon& polygon) {
	return os
		<< "faces = " << polygon.faces.size() << " "
		<< "normals = " << polygon.normals.size();
}

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
	group.setFaces(std::vector < OBJFace > {face});
	file.setGroups({ group });
	PolygonFactory factory;
	const PolygonGroupList& polygons = factory.create(file);
	Polygon expected;
	expected.positions = positions;
	Face f;
	f.vertexIds = { 0, 1, 2 };
	expected.faces = std::vector < Face > { f };
	const Polygon* p = polygons.front().getPolygon();
	const Material* m = polygons.front().getMaterial();
	EXPECT_EQ( expected, *p );
	EXPECT_EQ( nullptr, m );
	delete p;
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
	file.setCells(STLCellVector{ cell });

	PolygonFactory factory;
	const PolygonGroupList& polygons = factory.create(file);
	Face face;
	face.normalIds = { 0 };
	face.vertexIds = { 0, 1, 2 };
	Polygon* actual = polygons.front().getPolygon();
	Polygon expected;
	expected.faces = std::vector < Face > { face };
	expected.positions = positions;
	expected.normals = { normal };
	EXPECT_EQ( expected, *actual );
	delete actual;
}