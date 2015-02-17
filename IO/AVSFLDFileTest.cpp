#include "gtest/gtest.h"
 
#include "AVSFLDFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;



TEST( AVSDataType, TestToType )
{
	EXPECT_EQ( AVSDataType::Byte,		AVSDataType::toType( "byte" ) );
	EXPECT_EQ( AVSDataType::Integer,	AVSDataType::toType( "integer" ) );
	EXPECT_EQ( AVSDataType::Float,		AVSDataType::toType( "float" ) );
	EXPECT_EQ( AVSDataType::Double,		AVSDataType::toType( "double" ) );
}

TEST( AVSFieldTypeTest, TestToType )
{
	EXPECT_EQ( AVSFieldType::Uniform,		AVSFieldType::toType( "uniform" ) );
	EXPECT_EQ( AVSFieldType::Rectilinear,	AVSFieldType::toType( "rectilinear" ) );
	EXPECT_EQ( AVSFieldType::Irregular,		AVSFieldType::toType( "irregular" ) );
}

TEST( AVSFieldTypeTest, TestToStr )
{
	EXPECT_EQ( "uniform",		AVSFieldType::toStr( AVSFieldType::Uniform ) );
	EXPECT_EQ( "rectilinear",	AVSFieldType::toStr( AVSFieldType::Rectilinear ) );
	EXPECT_EQ( "irregular",		AVSFieldType::toStr( AVSFieldType::Irregular ) );
}

TEST( AVSFLDDataFileTest, TestReadStride )
{
	std::stringstream stream;
	stream << "1.0 2.0 3.0 4.0";

	const std::vector< float >& actual = AVSFLDDataFile::read( stream, 0, 0, 1);
	const std::vector< float > expected = { 1.0, 2.0, 3.0, 4.0 };
	EXPECT_EQ( expected, actual );
}


TEST( AVSFLDDataFileTest, TestReadSkip )
{
	std::stringstream stream;
	stream
		<< "1.0 2.0" << std::endl
		<< "10.0. 20.0 " << std::endl;

	const std::vector<float>& actual = AVSFLDDataFile::read(stream, 1, 0, 1);
	const std::vector< float > expected = { 10.0, 20.0 };
	EXPECT_EQ( expected, actual );
}

TEST( AVSFLDDataFileTest, TestReadOffsetAndStride )
{
	{
		std::stringstream stream;
		stream
			<< "X Y Z A B" << std::endl
			<< "1 1 1 11 101" << std::endl
			<< "2 2 2 12 102" << std::endl
			<< "3 3 3 13 103" << std::endl
			<< "4 4 4 14 104" << std::endl
			<< "5 5 5 15 105" << std::endl;

		const std::vector< float >& values = AVSFLDDataFile::read(stream, 1, 3, 5);
		const std::vector< float > expected = { 11, 12, 13, 14, 15 };
		EXPECT_EQ(expected, values);
	}

	{
		std::stringstream stream;
		stream
			<< "X Y Z A B" << std::endl
			<< "1 1 1 11 101" << std::endl
			<< "2 2 2 12 102" << std::endl
			<< "3 3 3 13 103" << std::endl
			<< "4 4 4 14 104" << std::endl
			<< "5 5 5 15 105" << std::endl;

		const std::vector< float >& values = AVSFLDDataFile::read(stream, 1, 4, 5);
		const std::vector< float > expected = { 101, 102, 103, 104, 105 };
		EXPECT_EQ(expected, values);
	}
}

TEST(AVSFLDDataFileTest, TestSample2A)
{
	{
		std::stringstream stream;
		stream
			<< "11 12 13" << std::endl
			<< "21 22 23" << std::endl
			<< "301 302" << std::endl
			<< "401 402" << std::endl;

		const std::vector< float >& values = AVSFLDDataFile::read(stream, 0, 0, 1);
		const std::vector< float > expected{ 11, 12, 13, 21, 22, 23, 301, 302, 401, 402 };
		EXPECT_EQ(expected, values);
	}

	{
		std::stringstream stream;
		stream
			<< "11 12 13" << std::endl
			<< "21 22 23" << std::endl
			<< "301 302" << std::endl
			<< "401 402" << std::endl;

		const std::vector< float >& actual = AVSFLDDataFile::read(stream, 2, 0, 1);
		const std::vector< float > expected{ 301, 302, 401, 402 };
		EXPECT_EQ(expected, actual);
	}
}


TEST(AVSFLDDataFileTest, TestRead)
{
	const std::string str = "file=/Termite/loc.dat filetype=ascii offset=3 stride=7";
	AVSFLDDataFile data;
	data.read(str);

	AVSFLDDataFile expected;
	expected.setFileName("/Termite/loc.dat");
	expected.setFileType("ascii");
	expected.setSkip(0);
	expected.setOffset(3);
	expected.setStride(7);

	EXPECT_EQ(expected, data);
}


TEST( AVSFLDFileTest, ContructTest )
{
	AVSFLDFile file;

	std::stringstream stream;
	stream
		<< "#AVS" << std::endl
		<< "ndim=2" << std::endl
		<< "dim1=4" << std::endl
		<< "dim2=3" << std::endl
		<< "nspace=2" << std::endl
		<< "veclen=1" << std::endl
		<< "data=float" << std::endl
		<< "field=irregular" << std::endl
		<< "coord 1 file=scalar.geo filetype=ascii skip=0 offset=0" << std::endl
		<< "coord 2 file=scalar.geo filetype=ascii skip=1 offset=0" << std::endl
		<< "variable 1 file=scalar.dat filetype=ascii skip=0 offset=0" << std::endl;

	file.read( stream );

	/*
	AVSFLDFile expected;
	expected.setDim(2);
	expected.setDimensions(std::vector < int > {4, 3});
	*/

	AVSFLDDataFile expected;
	expected.setFileName("scalar.geo");
	expected.setFileType("ascii");
	expected.setSkip(0);
	expected.setOffset(0);

	EXPECT_EQ( 1, file.getVecLength() );
	EXPECT_EQ( 2, file.getDim() );
	EXPECT_EQ( AVSDataType::Float, file.getDataType() );
	EXPECT_EQ( 2, file.getGeoFiles().size() );
	EXPECT_EQ( expected, file.getGeoFiles().front() );
	EXPECT_EQ( "scalar.dat", file.getDatFiles().front().getFileName() );
}



TEST( AVSFLDFileTest, TestReadWithComments )
{
	std::stringstream stream;
	stream
		<< "# AVS field file" << std::endl
		<< "ndim=3 # number of dimensions in the field" << std::endl
		<< "dim1=64 # dimension of axis 1" << std::endl
		<< "dim2=64 # dimension of axis 2" << std::endl
		<< "dim3=64 # dimension of axis 3" << std::endl
		<< "nspace=3 # number of physical coordinates per point" <<std::endl
		<< "veclen=1 # number of components at each point" << std::endl
		<< "data=byte # data type (byte, integer, float, double)" << std::endl
		<< "field=uniform # field type (uniform, rectilinear, irregular)" <<std::endl;

	AVSFLDFile file;
	file.read( stream );
	EXPECT_EQ( 3, file.getDim() );
	EXPECT_EQ( 3, file.getNSpace() );
	//EXPECT_EQ( AVSDataType::Float, file.getDataType() );
}

TEST( AVSFLDFileTest, TestReadWithOptions )
{
	std::stringstream stream;
	stream
		<< "# AVS field file" << std::endl
		<< "ndim=3" << std::endl
		<< "dim1=64" << std::endl
		<< "dim2=64" << std::endl
		<< "dim3=64" << std::endl
		<< "nspace=3" <<std::endl
		<< "veclen=1" << std::endl
		<< "data=byte" << std::endl
		<< "field=uniform" <<std::endl
		<< "min_ext=-1.0 -1.0 -1.0" << std::endl
		<< "max_ext=1.0 1.0 1.0" << std::endl
		<< "label=vel_x" << std::endl
		<< "label=vel_y" << std::endl
		<< "label=vel_z" << std::endl
		<< "unit=m/s" << std::endl
		<< "unit=m/s" << std::endl
		<< "unit=m/s" << std::endl;

	AVSFLDFile file;
	file.read( stream );
	EXPECT_EQ( 3, file.getDim() );
	EXPECT_EQ( 3, file.getNSpace() );
	EXPECT_EQ( 1, file.getVecLength() );

	const std::vector<int> dims{ 64, 64, 64 };
	EXPECT_EQ( dims, file.getDimensions());

	const std::vector< std::string > labels = { "vel_x", "vel_y", "vel_z" };
	EXPECT_EQ( labels, file.getLabels() );

	const std::vector< std::string > units{ "m/s", "m/s", "m/s" };
	EXPECT_EQ( units, file.getUnits() );

	const std::vector<float> mins{ -1.0, -1.0, -1.0 };
	EXPECT_EQ( mins, file.getMinExts() );

	const std::vector<float> maxs{ 1.0, 1.0, 1.0 };
	EXPECT_EQ(maxs, file.getMaxExts());
	//EXPECT_EQ( AVSDataType::Float, file.getDataType() );
}

TEST( AVSFLDFileTest, TestReadWithSpaces )
{
	std::stringstream stream;
	stream
		<< "# AVS field file" << std::endl
		<< "ndim = 1" << std::endl
		<< "dim1 = 10 " << std::endl
		<< "nspace = 3" << std::endl
		<< "veclen = 1" << std::endl
		<< "data = float" << std::endl
		<< "field = irregular" << std::endl;

	AVSFLDFile file;
	file.read( stream );
	
	AVSFLDFile expected;
	expected.setDim(1);
	expected.setDimensions({ 10 });
	expected.setNSpace(3);
	expected.setVecLength(1);
	expected.setDataType(AVSDataType::Float);
	expected.setFiledType(AVSFieldType::Irregular);
	EXPECT_EQ( expected, file );
}

TEST( AVSFLDFileTest, TestToPositions )
{
	AVSFLDFile file;

	AVSFLDDataFile dataFile;
	dataFile.setValues( { 0.0f, 1.0f } );
	std::vector<AVSFLDDataFile> dataFiles({ dataFile } );
	file.setGeoFiles( dataFiles );
	file.setDim( 1 );
	file.setDimensions({ 2 });
	const std::vector<Vector3d>& positions = file.toPositions();
	EXPECT_EQ( 2, positions.size() );

	const std::vector< Vector3d > expected = {
		Vector3d(0.0f, 0.0f, 0.0f),
		Vector3d(1.0f, 0.0f, 0.0f)
	};

	EXPECT_EQ( expected, positions );
}

TEST( AVSFLDFileTest, TestToScalars )
{
	AVSFLDFile file;

	AVSFLDDataFile dataFile;
	dataFile.setValues({ 0.0f, 1.0f });
	std::vector<AVSFLDDataFile> dataFiles = { dataFile };
	file.setDatFiles( dataFiles );
	file.setVecLength( 1 );
	const std::vector<float>& actual = file.toScalarValues();
	EXPECT_EQ( 2, actual.size() );
}

TEST( AVSFLDFileTest, TestToVectors )
{
	AVSFLDFile file;

	AVSFLDDataFile dataFile;
	dataFile.setValues({ 0.0f, 1.0f });
	AVSFLDDataFile dataFile2;
	dataFile2.setValues({ 10.0f, 11.0f });

	const std::vector<AVSFLDDataFile> dataFiles{ dataFile, dataFile2 };
	file.setDatFiles( dataFiles );
	const std::vector< int > dimensions{ 1, 2 };
	file.setDimensions( dimensions );
	file.setVecLength( 2 );
	const VectorVector& actual = file.toVector3dValues();
	EXPECT_EQ( 2, actual.size() );
}