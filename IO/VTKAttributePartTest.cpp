#include "gtest/gtest.h"

#include "VTKAttributePart.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

TEST( VTKScalarsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "SCALARS scalars float" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0 1 2 3" << std::endl;

	VTKScalars scalars;
	scalars.read( stream, 4 );

	const std::vector< float > expected = { 0.0, 1.0, 2.0, 3.0 };

	EXPECT_EQ( expected, scalars.getValues() );
	EXPECT_EQ( "float", scalars.getType().toString() );
}

TEST( VTKScalarsTest, TestReadWithOption )
{
	std::stringstream stream;
	stream
		<< "SCALARS scalars float 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0.0 1.0 2.0 3.0" << std::endl;

	VTKScalars scalars;
	scalars.read( stream, 4 );

	EXPECT_EQ( 4, scalars.getValues().size() );
	EXPECT_EQ( "float", scalars.getType().toString() );
}

TEST( VTKScalarsTest, TestWrite )
{
	std::ostringstream stream;
	VTKScalars scalars;

	scalars.setType( VTKType::FLOAT );
	scalars.setName( "scalars" );
	const std::vector< float > values = { 0.0, 1.0, 2.0, 3.0 };
	scalars.setValues( values );
	scalars.setLookupTableName( "default" );
	scalars.write( stream );

	std::stringstream expected;
	expected
		<< "SCALARS scalars float" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0" << std::endl
		<< "1" << std::endl
		<< "2" << std::endl
		<< "3" << std::endl;


	const std::string& actual = stream.str();

	EXPECT_EQ( expected.str(), actual );
}

TEST( VTKColorScalarsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "COLOR_SCALARS sample 3" << std::endl
		<< "0.0 0.0 0.0" << std::endl
		<< "1.0 0.0 0.0" << std::endl;

	VTKColorScalars scalars;
	scalars.read( stream, 2 );
	EXPECT_EQ( "sample", scalars.getName() );
	/*
	const std::vector< Vector3d > expected = {
		Vector3d( 0.0, 0.0, 0.0 ),
		Vector3d( 1.0, 0.0, 0.0 )
	};
	EXPECT_EQ( expected, scalars.ge)
	*/
}


TEST( VTKVectorsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "VECTORS vectors float" << std::endl
		<< "1.0 0.0 0.0" << std::endl
		<< "1 1 0" << std::endl;

	VTKVectors vectors;
	vectors.read( stream, 2 );

	EXPECT_EQ( "vectors", vectors.getName() );
	EXPECT_EQ( 2, vectors.getValues().size() );

	EXPECT_EQ( Vector3d( 1.0, 0.0, 0.0), vectors.getValues().front() );
	EXPECT_EQ( Vector3d( 1.0, 1.0, 0.0), vectors.getValues().back() );

	EXPECT_EQ( "float", vectors.getType().toString() );
}

TEST( VTKVectorsTest, TestWrite )
{
	std::ostringstream stream;
	std::stringstream expected;
	expected
		<< "VECTORS vectors float" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl;

	VTKVectors vectors;
	const std::vector< Vector3d > positions = {
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};

	vectors.setName( "vectors" );
	vectors.setValues( positions );
	vectors.setType( VTKType::FLOAT );
	vectors.write( stream );

	//const std::string& expected = getSampleVector().str();
	const std::string& actual = stream.str();

	EXPECT_EQ( expected.str(), actual );
}


TEST( VTKNormalsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "NORMALS normals float" << std::endl
		<< "1 0 0" << std::endl
		<< "0 2 0" << std::endl;

	VTKNormals normals;
	normals.read( stream, 2 );

	EXPECT_EQ( "normals", normals.getName() );

	const std::vector< Vector3d > expected = {
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, 2.0, 0.0)
	};

	EXPECT_EQ( expected, normals.getValues() );
}

TEST( VTKNormalsTest, TestWrite )
{
	std::ostringstream stream;
	VTKNormals normals;
	normals.setName( "normals" );
	normals.setType( VTKType::FLOAT );
	const std::vector< Vector3d > values = {
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(0.0, 2.0, 0.0)
	};
	normals.setValues( values );
	normals.write( stream );
	
	std::stringstream estream;
	estream
		<< "NORMALS normals float" << std::endl
		<< "1 0 0" << std::endl
		<< "0 2 0" << std::endl;

	const std::string& expected = estream.str();
	const std::string& actual = stream.str();

	EXPECT_EQ( expected, actual );
}

TEST( VTKLookupTableTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "LOOKUP_TABLE my_table 2" << std::endl
		<< "0 0 0 1" << std::endl
		<< "1 1 1 1" << std::endl;

	VTKLookupTable table;
	table.read( stream );
	EXPECT_EQ( "my_table", table.getName() );
	EXPECT_EQ( 2, table.getColors().size() );
}

TEST( VTKLookupTableTest, TestWrite )
{
	std::ostringstream stream;
	VTKLookupTable table;
	table.setName( "my_table" );
	std::vector< ColorRGBA<float> > colors{
		ColorRGBA<float>(0.0, 0.0, 0.0, 1.0),
		ColorRGBA<float>(1.0, 1.0, 1.0, 1.0)
	};
	table.setColors( colors );
	table.write( stream );

	std::stringstream expected;
	expected
		<< "LOOKUP_TABLE my_table 2" << std::endl
		<< "0 0 0 1" << std::endl
		<< "1 1 1 1" << std::endl;
	
	const std::string& actual = stream.str();
	EXPECT_EQ( expected.str(), actual );
}

TEST( VTKTensorsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "TENSORS tensors float" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 2 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 2 3" << std::endl;

	VTKTensors tensors;
	tensors.read( stream, 2 );

	EXPECT_EQ( "tensors", tensors.getName() );
	const std::vector<Matrix3d<float> >& actual = tensors.getTensors();
	EXPECT_EQ( 2, actual.size() );

	const Matrix3d<float> expected1
		(
		1.0, 0.0, 0.0,
		1.0, 1.0, 0.0,
		0.0, 2.0, 0.0
		);

	EXPECT_EQ( expected1, actual.front() );

	const Matrix3d<float> expected2
		(
		1.0, 0.0, 0.0,
		1.0, 1.0, 0.0,
		0.0, 2.0, 3.0
		);
	
	EXPECT_EQ( expected2, actual.back() );
}

TEST( VTKTexCoordsTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "TEXTURE_COORDINATES texCoords 3 float" << std::endl
		<< "0.0 0.0 0.0" << std::endl
		<< "1.0 0.0 0.0" << std::endl
		<< "1.0 1.0 0.0" << std::endl;

	VTKTexCoords tex;
	tex.read( stream, 3 );
	const std::vector< Vector3d >& values = tex.getValues();
	EXPECT_EQ( 3, values.size() );
	EXPECT_EQ( "texCoords", tex.getName() );
	EXPECT_EQ( "float", tex.getType().toString() );
	EXPECT_EQ( 3, tex.getDim() );
}

TEST( VTKTexCoordsTest, TestWrite )
{
	VTKTexCoords tex;
	tex.setName( "texCoords" );
	tex.setType( VTKType::FLOAT );
	tex.setDim( 3 );

	const std::vector< Vector3d > coords = {
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	tex.setCoords( coords );

	std::ostringstream stream;
	tex.write( stream );

	std::stringstream expected;
	expected
		<< "TEXTURE_COORDINATES texCoords 3 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl;

	const std::string& actual = stream.str();
	EXPECT_EQ( expected.str(), actual );
}

TEST( VTKFieldTest, TestReadSingle )
{
	std::stringstream stream;
	stream << "cellIds 1 6 int"		<< std::endl;
	stream << "0 1 2 3 4 5"			<< std::endl;
	VTKField field;
	field.read( stream );
	EXPECT_EQ( "cellIds", field.getName() );
	EXPECT_EQ( 1, field.getNumComponents() );
	EXPECT_EQ( 6, field.getNumTuples() );

	VTKAttributes* attr = field.toVTKAttributes();
	EXPECT_EQ( 1, attr->getDim() );
	delete attr;
}

TEST( VTKFieldTest, TestWriteSingle )
{
	VTKField field;
	field.setName( "cellIds" );
	field.setNumComponents( 1 );
	field.setNumTuples( 6 );

	std::ostringstream stream;
	field.write(stream);
}

TEST( VTKFieldTest, TestReadDouble )
{
	std::stringstream stream;
	stream
		<< "faceAttributes 2 6 float" << std::endl
		<< "0.0 1.0 1.0 2.0 2.0 3.0 3.0 4.0 4.0 5.0 5.0 6.0" << std::endl;
	VTKField field;
	field.read( stream );
	VTKAttributes* attr = field.toVTKAttributes();
	EXPECT_EQ( "faceAttributes", field.getName() );
	EXPECT_EQ( 2, attr->getDim() );
	EXPECT_EQ( 12, attr->getValues().size() );
	EXPECT_EQ( 0.0, attr->getValues().front() );
	EXPECT_EQ( 6.0, attr->getValues().back() );
	delete attr;
}

TEST( VTKFieldTest, TestReadMulti )
{
	std::stringstream stream;
	stream
		<< "FIELD FieldData 2" << std::endl
		<< "cellIds 1 6 int" << std::endl
		<< "0 1 2 3 4 5" << std::endl
		<< "faceAttributes 2 6 float" << std::endl
		<< "0.0 1.0 1.0 2.0 2.0 3.0 3.0 4.0 4.0 5.0 5.0 6.0" << std::endl;

	const VTKFieldVector& fields = VTKField::readFields( stream );
	EXPECT_EQ( 2, fields.size() );

	EXPECT_EQ( "cellIds", fields.front().getName() );
	EXPECT_EQ( 1, fields.front().getNumComponents() );
	EXPECT_EQ( 6, fields.front().getNumTuples() );

	EXPECT_EQ( "faceAttributes", fields.back().getName() );
	EXPECT_EQ( 2, fields.back().getNumComponents() );
	EXPECT_EQ( 6, fields.back().getNumTuples() );
}

TEST( VTKAttributePartTest, TestReadScalars )
{
	std::stringstream stream;
	stream
		<< "CELL_DATA 50000" << std::endl
		<< "POINT_DATA 6" << std::endl
		<< "SCALARS cell_scalars int 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0 1 2 3 4 5" << std::endl;

	VTKAttributePart file;
	file.read( stream );
	EXPECT_EQ( 1, file.getPointAttribute().getScalars().size() );
}


TEST(VTKAttributePartTest, TestReadMultiScalars)
{
	std::stringstream stream;
	stream
		<< "4" << std::endl
		<< "SCALARS pressure float" << std::endl
		<< "LOOKUP_TABLE custom_table" << std::endl
		<< "0.0" << std::endl
		<< "1.0" << std::endl
		<< "2.0" << std::endl
		<< "3.0" << std::endl
		<< "SCALARS temperature float" << std::endl
		<< "LOOKUP_TABLE cumstom_table" << std::endl
		<< "10.0" << std::endl
		<< "20.0" << std::endl
		<< "30.0" << std::endl
		<< "40.0" << std::endl;

	VTKAttributePart_ attr;
	attr.read(stream);

	EXPECT_EQ(2, attr.getScalars().size());
	EXPECT_EQ("pressure", attr.getScalars().front().getName());
	EXPECT_EQ("temperature", attr.getScalars().back().getName());
}


TEST( VTKAttributePartTest, TestWriteScalars )
{
	VTKAttributePart_ attr;
	VTKScalars s;
	const std::vector<float> values = { 0, 1 };
	s.setType( VTKType::FLOAT );
	s.setValues( values );
	VTKScalarsVector scalars = { s };
	attr.setScalars( scalars );

	std::ostringstream stream;
	attr.write( stream );
}

TEST( VTKAttributePartTest, TestReadPointData )
{
	std::stringstream stream;
	stream
		<< "4" << std::endl
		<< "SCALARS my_scalars float" << std::endl
		<< "LOOKUP_TABLE custom_table" << std::endl
		<< "0.0" << std::endl
		<< "1.0" << std::endl
		<< "2.0" << std::endl
		<< "3.0" << std::endl
		<< "LOOKUP_TABLE custom_table 4" << std::endl
		<< "0.0 0.0 0.0 1.0" << std::endl
		<< "1.0 0.0 0.0 1.0" << std::endl
		<< "0.0 1.0 0.0 1.0" << std::endl
		<< "1.0 1.0 0.0 1.0" << std::endl;

	VTKAttributePart_ attr;
	attr.read( stream );

	const VTKScalars scalars = attr.getScalars().front();
	const std::vector< float > expected = { 0.0, 1.0, 2.0, 3.0 };
	EXPECT_EQ( expected, scalars.getValues() );

	const VTKLookupTable table = attr.getLookupTables().front();
	EXPECT_EQ( "custom_table", table.getName() );
	EXPECT_EQ( ColorRGBA<float>( 0.0, 0.0, 0.0, 1.0 ), table.getColors().front() );
	EXPECT_EQ( ColorRGBA<float>( 1.0, 1.0, 0.0, 1.0 ), table.getColors().back() );
}

TEST( VTKAttributePartTest, TestWrite )
{
	VTKAttributePart attr;
	//attr.set
}