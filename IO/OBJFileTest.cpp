#include "gtest/gtest.h"
 
#include "OBJFile.h"
#include "Helper.h"

using namespace Crystal::Math;
using namespace Crystal::IO;



::std::ostream& operator<<(::std::ostream& os, const OBJFace& face) {
	os << "faces " << face.getVertexIndices().size() << std::endl;
	for (unsigned int i : face.getVertexIndices()) {
		os << " " << i;
	}
	os << std::endl;
	os << "normals " << face.getNormalIndices().size() << std::endl;
	for (unsigned int i : face.getNormalIndices()) {
		os << " " << i;
	}
	os << std::endl;
	os << "texIds " << face.getTexIndices().size() << std::endl;
	for (unsigned int i : face.getTexIndices()) {
		os << " " << i;
	}
	os << std::endl;
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const OBJMTLLib& lib)
{
	os << "name " << lib.getName() << std::endl;
	for (const std::string& m : lib.getMaterials()) {
		os << m << std::endl;
	}
	return os;
}

/*
::std::ostream& operator<<(::std::ostream& os, const OBJFile& file) {
	for (const OBJFace& f : file.getFaces()) {
		os << f;
	}
	for (const OBJMTLLib& lib : file.getLibs() ) {
		os << lib;
	}

	os << std::endl;
	return os;
}
*/

TEST(OBJFileTest, TestReadVertices)
{
	std::stringstream stream;
	stream
		<< "v 0.1 0.2 0.3" << std::endl
		<< "vt 0.5 1.0" << std::endl
		<< "vn 1.0 0.0 0.0" << std::endl;
	OBJFileReader reader;
	OBJFile file = reader.read(stream);

	const OBJGroupSPtr actual = file.getGroups().front();

	EXPECT_EQ( std::vector < Vector3d > { Vector3d(0.1f, 0.2f, 0.3f) }, actual->getPositions() );
	EXPECT_EQ( std::vector < Vector3d > { Vector3d(0.5f, 1.0f, 0.0f) }, actual->getTexCoords());
	EXPECT_EQ( std::vector < Vector3d > { Vector3d(1.0f, 0.0f, 0.0f) }, actual->getNormals() );
}

TEST(OBJFileTest, TestReadFaces)
{
	std::stringstream stream;
	stream
		<< "f 1 2 3" << std::endl
		<< "f 3/1 4/2 5/3" << std::endl
		<< "f 1//1 2//2 3//3 4//4 "<< std::endl
		<< "f 6/4/1 3/5/3 7/6/5" << std::endl;

	OBJFileReader reader;
	OBJFile file =reader.read(stream);

	const std::vector<OBJFace> expected = {
		OBJFace({ 1, 2, 3 } ),
		OBJFace({ 3, 4, 5 }, { 1, 2, 3 } ),
		OBJFace({ 1, 2, 3, 4 }, {}, {1, 2, 3, 4}),
		OBJFace({ 6, 3, 7 }, { 4, 5, 6 }, { 1, 3, 5 })
	};
	EXPECT_EQ( expected, file.getGroups().front()->getFaces() );
}

TEST(OBJFileTest, TestReadComments)
{
	std::stringstream stream;
	stream
		<< "# comment1" << std::endl
		<< "v 0.0 0.0 0.0" << std::endl
		<< "# comment2" << std::endl;

	const OBJFileReader file(stream);

	OBJFile expected;
	OBJGroup group;
	group.setPositions( {Vector3d(0.0, 0.0, 0.0)} );
	//expected.setGroups({ group });
	//EXPECT_EQ( expected, file );
}

TEST(OBJFileTest, TestReadSquare)
{
	std::stringstream stream;
	stream
		<< "v 0.0 2.0 0.0" << std::endl
		<< "v 0.0 0.0 0.0" << std::endl
		<< "v 2.0 0.0 0.0" << std::endl
		<< "v 2.0 2.0 0.0" << std::endl
		<< "f 1 2 3 4" << std::endl;
	const OBJFileReader actual(stream);

	OBJFile expected;
	const std::vector< Vector3d > positions = {
		Vector3d(0.0, 2.0, 0.0),
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(2.0, 0.0, 0.0),
		Vector3d(2.0, 2.0, 0.0)
	};
	OBJGroup group;
	group.setPositions( positions );
	OBJFace face({ 1, 2, 3, 4 });
	group.setFaces({ face });
	//expected.setGroups({ group });
	//EXPECT_EQ( expected, actual );
}

TEST(OBJFileTest, TestReadGroup )
{
	std::stringstream stream;
	stream
		<< "g front" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "g back" << std::endl
		<< "f 4 3 2 1" << std::endl;

	OBJFileReader reader;
	OBJFile file = reader.read(stream);
	EXPECT_EQ(3, file.getGroups().size() );

	/*
	std::vector< OBJGroup > expected = {
		OBJGroup("", {}),
		OBJGroup(" front", { OBJFace({ 1, 2, 3, 4 }) }),
		OBJGroup(" back", { OBJFace({ 4, 3, 2, 1 }) })
	};
	EXPECT_EQ( 3, file.getGroups().size() ) ;
	*/
}

TEST( OBJFileTest, TestReadUseMtl )
{
	std::stringstream stream;
	stream
		<< "mtllib master.mtl" << std::endl
		<< "usemtl wood" << std::endl
		<< "f 1 2 3 4" << std::endl;

	OBJFileReader reader;
	OBJFile file = reader.read(stream);

	EXPECT_EQ(1, file.getGroups().front()->getFaces().size());
}

TEST(OBJFileTest, TestWriteEmpty)
{
	std::ostringstream stream;
	OBJFile file;
	OBJFileWriter writer;
	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_TRUE(strs.empty() );
}

TEST(OBJFileTest, TestWriteNormals)
{
	OBJFileWriter writer;
	OBJGroupSPtr group( new OBJGroup() );
	group->setNormals({ Vector3d(0.5f, 1.0f, 0.0f) });
	std::stringstream stream;
	OBJFile file;
	//stream << file;
	file.setGroups({ group });

	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ(strs[0], "g ");
	EXPECT_EQ(strs[1], "vn 0.500000 1.000000 0.000000");
}

	/*
	{
		OBJFile file;
		OBJGroup group;
		group.setTexCoords({ Vector3d(0.5f, 0.5f, 0.0f) });
		file.setGroups({ group });
		std::stringstream stream;
		file.write(stream);
		EXPECT_EQ("g \nvt 0.5 0.5 0\n", stream.str());
	}
	*/

TEST(OBJFileTest, TestWrite2)
{
	std::stringstream stream;
	OBJFileWriter writer;
	OBJGroupSPtr group( new OBJGroup() );
	group->setPositions({ Vector3d(0.1f, 0.2f, 0.3f) });
	OBJFile file;
	file.setGroups({ group });

	writer.write(stream, file);

	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ( strs[0], "g ");
	EXPECT_EQ( strs[1], "v 0.1000 0.2000 0.3000");
}

TEST(OBJFileTest, TestWriteFaces)
{
	OBJFileWriter writer;
	OBJFace face({ 0, 1, 2 }, {}, {} );
	OBJGroupSPtr group(new OBJGroup());
	group->setFaces(std::vector < OBJFace > { face });
	std::stringstream stream;
	OBJFile file;
	file.setGroups({ group });
	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();

	EXPECT_EQ( strs[0], "g ");
	EXPECT_EQ( strs[1], "f 0 1 2");
}

TEST(OBJFileTest, TestWriteFacesVertexTex)
{
	OBJFileWriter writer;
	OBJFace face({ 0, 1, 2 }, { 1, 1, 1 }, {} );
	OBJGroupSPtr group( new OBJGroup() );
	group->setFaces(std::vector < OBJFace > { face });
	std::stringstream stream;
	OBJFile file;
	file.setGroups({ group });

	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();

	EXPECT_EQ(strs[0], "g ");
	EXPECT_EQ(strs[1], "f 0/1 1/1 2/1");
}


TEST(OBJFileTest, TestWriteFacesVertexNormal)
{
	OBJFileWriter writer;
	OBJFace face({ 0, 1, 2 }, {}, {3, 4, 5});
	OBJGroupSPtr group(new OBJGroup());
	group->setFaces(std::vector < OBJFace > { face });
	std::stringstream stream;
	OBJFile file;
	file.setGroups({ group });
	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ(strs[0], "g ");
	EXPECT_EQ(strs[1], "f 0//3 1//4 2//5");

}

TEST(OBJFileTest, TestWriteFacesVertexTexNormal)
{
	OBJFileWriter writer;
	OBJFace face({ 0, 1, 2 }, { 1, 1, 1 }, {2, 2, 2});
	OBJGroupSPtr group(new OBJGroup());
	group->setFaces(std::vector < OBJFace > { face });
	std::stringstream stream;
	OBJFile file;
	file.setGroups({ group });
	writer.write(stream, file);

	const std::vector< std::string >& strs = writer.getStrs();

	EXPECT_EQ(strs[0], "g ");
	EXPECT_EQ(strs[1], "f 0/1/2 1/1/2 2/1/2" );
}

TEST(OBJFileTest, TestWriteGroups)
{
	OBJFileWriter writer;
	OBJGroupSPtr group(new OBJGroup("name") );
	std::stringstream stream;
	OBJFile file;
	file.setGroups( {group});
	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();

	EXPECT_EQ(strs[0], "g name");
}

	/*
	{
		OBJFile file;
		OBJFace face({ 0, 1, 2 });
		OBJGroup group("name", { face });
		std::stringstream stream;
		file.setGroups({ group });
		file.write(stream);
		EXPECT_EQ("g name\nf 0 1 2\n", stream.str());
	}
	*/

TEST(OBJFileTest, TestExample1)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "f 1 2 3 4" << std::endl;
}

// from http://www.martinreddy.net/gfx/3d/OBJ.spec
TEST(OBJFileTest, TestExampleGroups)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "# 8 vertices" << std::endl
		<< "g front cube" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "g back cube" << std::endl
		<< "f 8 7 6 5" << std::endl
		<< "g right cube" << std::endl
		<< "f 4 3 7 8" << std::endl
		<< "g top cube" << std::endl
		<< "f 5 1 4 8" << std::endl
		<< "g left cube" << std::endl
		<< "f 5 6 2 1" << std::endl
		<< "g bottom cube" << std::endl
		<< "f 2 6 7 3" << std::endl
		<< "# 6 elements" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ( 7, file.getGroups().size() );
}