#include "gtest/gtest.h"
 
#include "VTKFile.h"

#include "VTKObject.h"

#include "Volume.h"

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::Graphics;

TEST( NextStringTest, Test )
{
	std::stringstream stream;
	stream
		<< "scalars float 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl;

	const std::string& str = Helper::readNextString( stream );
	EXPECT_EQ( str, "scalars" );
	const std::string& str2 = Helper::readNextString( stream );
	EXPECT_EQ( str2, "scalars" );
}


TEST( VTKVersionTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl;
	VTKVersion version;
	version.read( stream );
	EXPECT_EQ( 2, version.getMajor() );
	EXPECT_EQ( 0, version.getMinor() );
}

TEST( VTKVersionTest, TestToString )
{
	VTKVersion version;
	version.setMajor( 3 );
	version.setMinor( 0 );
	EXPECT_EQ( "3.0", version.toStr() );
}

TEST( VTKVersionTest, TestWrite )
{
	VTKVersion version;
	version.setMajor( 3 );
	version.setMinor( 0 );

	std::ostringstream stream;
	version.write( stream );
	EXPECT_EQ( "# vtk DataFile Version 3.0\n", stream.str() );
}

TEST( VTKHeaderPartTest, TestRead )
{
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl
		<< "Title Example" << std::endl
		<< "ASCII" << std::endl;

	VTKHeaderPart header;
	header.read( stream );

	EXPECT_EQ( "Title Example", header.getTitle() );
	EXPECT_TRUE( VTKFileType::Type::ASCII == header.getFileType().getType() );
}

TEST( VTKHeaderPartTest, TestWrite )
{
	VTKHeaderPart header;
	header.setTitle( "Title Example" );
}

TEST( VTKFileTest, TestReadPolyData )
{
	// from the VTK file format specification (http://www.vtk.org/VTK/img/file-formats.pdf).
	std::stringstream stream;
		stream
			<< "# vtk DataFile Version 2.0" << std::endl
			<< "Cube example" << std::endl
			<< "ASCII" << std::endl
			<< "DATASET POLYDATA" << std::endl
			<< "POINTS 8 float" << std::endl
			<< "0.0 0.0 0.0" << std::endl
			<< "1.0 0.0 0.0" << std::endl
			<< "1.0 1.0 0.0" << std::endl
			<< "0.0 1.0 0.0" << std::endl
			<< "0.0 0.0 1.0" << std::endl
			<< "1.0 0.0 1.0" << std::endl
			<< "1.0 1.0 1.0" << std::endl
			<< "0.0 1.0 1.0" << std::endl
			<< "POLYGONS 6 30" << std::endl
			<< "4 0 1 2 3" << std::endl
			<< "4 4 5 6 7" << std::endl
			<< "4 0 1 5 4" << std::endl
			<< "4 2 3 7 6" << std::endl
			<< "4 0 4 7 3" << std::endl
			<< "4 1 2 6 5" << std::endl
			<< "CELL_DATA 6" << std::endl
			<< "SCALARS cell_scalars int 1" << std::endl
			<< "LOOKUP_TABLE default" << std::endl
			<< "0" << std::endl
			<< "1" << std::endl
			<< "2" << std::endl
			<< "3" << std::endl
			<< "4" << std::endl
			<< "5" << std::endl
			<< "NORMALS cell_normals float" << std::endl
			<< "0 0 -1" << std::endl
			<< "0 0 1" << std::endl
			<< "0 -1 0" << std::endl
			<< "0 1 0" << std::endl
			<< "-1 0 0" << std::endl
			<< "1 0 0" << std::endl
			<< "FIELD FieldData 2" << std::endl
			<< "cellIds 1 6 int" << std::endl
			<< "0 1 2 3 4 5" << std::endl
			<< "faceAttributes 2 6 float" << std::endl
			<< "0.0 1.0 1.0 2.0 2.0 3.0 3.0 4.0 4.0 5.0 5.0 6.0" << std::endl
			<< "POINT_DATA 8" << std::endl
			<< "SCALARS sample_scalars float 1" << std::endl
			<< "LOOKUP_TABLE my_table" << std::endl
			<< "0.0" << std::endl
			<< "1.0" << std::endl
			<< "2.0" << std::endl
			<< "3.0" << std::endl
			<< "4.0" << std::endl
			<< "5.0" << std::endl
			<< "6.0" << std::endl
			<< "7.0" << std::endl
			<< "LOOKUP_TABLE my_table 8" << std::endl
			<< "0.0 0.0 0.0 1.0" << std::endl
			<< "1.0 0.0 0.0 1.0" << std::endl
			<< "0.0 1.0 0.0 1.0" << std::endl
			<< "1.0 1.0 0.0 1.0" << std::endl
			<< "0.0 0.0 1.0 1.0" << std::endl
			<< "1.0 0.0 1.0 1.0" << std::endl
			<< "0.0 1.0 1.0 1.0" << std::endl
			<< "1.0 1.0 1.0 1.0" << std::endl;

	VTKFile file;
	const bool isOpen = file.read( stream );
	EXPECT_TRUE( isOpen );
	const VTKPoints& positions = file.getGeometryPart().getPoints();
	EXPECT_EQ( 8, positions.getPoints().size() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 0.0 ), positions.getPoints()[0] );
	EXPECT_EQ( Vector3d( 1.0, 0.0, 0.0 ), positions.getPoints()[1] );
	EXPECT_EQ( Vector3d( 1.0, 1.0, 0.0 ), positions.getPoints()[2] );
	EXPECT_EQ( 6, file.getGeometryPart().getCells().size() );

	const VTKAttributePart_& cellData = file.getAttributePart().getCellAttribute();
	EXPECT_EQ( 6, cellData.getScalars().front().getValues().size() );
	EXPECT_EQ( 6, cellData.getNormals().front().getValues().size() );
	EXPECT_EQ( 2, cellData.getFields().size() );
	EXPECT_EQ( 6, cellData.getFields().front().getValues().size() );
	EXPECT_EQ( 12, cellData.getFields().back().getValues().size() );

	const VTKLookupTable table = file.getAttributePart().getPointAttribute().getLookupTables().front();
	EXPECT_EQ( 8, table.getColors().size() );
}


TEST( VTKFileTest, TestReadStructuredPoints )
{
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl
		<< "Volume example" << std::endl
		<< "ASCII" << std::endl
		<< "DATASET STRUCTURED_POINTS" << std::endl
		<< "DIMENSIONS 2 2 2" << std::endl
		<< "ASPECT_RATIO 1 1 1" << std::endl
		<< "ORIGIN 0 0 0" << std::endl
		<< "POINT_DATA 8" << std::endl
		<< "SCALARS volume_scalars char 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "1 2 3 4 5 6 7 8" << std::endl;

	VTKFile file;
	const bool isOpen = file.read( stream );
	EXPECT_TRUE( isOpen );
	const VTKPoints& points = file.getGeometryPart().getPoints();
	EXPECT_EQ( 8, points.getPoints().size() );

	const VTKScalars scalars = file.getAttributePart().getPointAttribute().getScalars().front();
	EXPECT_EQ( 8, scalars.getValues().size() );
}

TEST( VTKFileTest, TestWrite )
{
	std::ostringstream stream;

	VTKFile file;
	file.write( stream );
	const std::string& actual = stream.str();
}

// from the VTK file format specification (http://www.vtk.org/VTK/img/file-formats.pdf).
static std::stringstream getUnstructuredGrid() {
	std::stringstream stream;
	stream
		<< "# vtk DataFile Version 2.0" << std::endl
		<< "Unstructured Grid Example" << std::endl
		<< "ASCII" << std::endl
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 27 float" << std::endl
		<< "0 0 0 1 0 0 2 0 0 0 1 0 1 1 0 2 1 0" << std::endl
		<< "0 0 1 1 0 1 2 0 1 0 1 1 1 1 1 2 1 1" << std::endl
		<< "0 1 2 1 1 2 2 1 2 0 1 3 1 1 3 2 1 3" << std::endl
		<< "0 1 4 1 1 4 2 1 4 0 1 5 1 1 5 2 1 5" << std::endl
		<< "0 1 6 1 1 6 2 1 6" << std::endl
		<< "CELLS 11 60" << std::endl
		<< "8 0 1 4 3 6 7 10 9" << std::endl
		<< "8 1 2 5 4 7 8 11 10" << std::endl
		<< "4 6 10 9 12" << std::endl
		<< "4 5 11 10 14" << std::endl
		<< "6 15 16 17 14 13 12" << std::endl
		<< "6 18 15 19 16 20 17" << std::endl
		<< "4 22 23 20 19" << std::endl
		<< "3 21 22 18" << std::endl
		<< "3 22 19 18" << std::endl
		<< "2 26 25" << std::endl
		<< "1 24" << std::endl
		<< "CELL_TYPES 11" << std::endl
		<< "12" << std::endl
		<< "12" << std::endl
		<< "10" << std::endl
		<< "10" << std::endl
		<< "7" << std::endl
		<< "6" << std::endl
		<< "9" << std::endl
		<< "5" << std::endl
		<< "5" << std::endl
		<< "3" << std::endl
		<< "1" << std::endl
		<< "POINT_DATA 27" << std::endl
		<< "SCALARS scalars float 1" << std::endl
		<< "LOOKUP_TABLE default" << std::endl
		<< "0.0 1.0 2.0 3.0 4.0 5.0" << std::endl
		<< "6.0 7.0 8.0 9.0 10.0 11.0" << std::endl
		<< "12.0 13.0 14.0 15.0 16.0 17.0" << std::endl
		<< "18.0 19.0 20.0 21.0 22.0 23.0" << std::endl
		<< "24.0 25.0 26.0" << std::endl
		<< "VECTORS vectors float" << std::endl
		<< "1 0 0 1 1 0 0 2 0 1 0 0 1 1 0 0 2 0" << std::endl
		<< "1 0 0 1 1 0 0 2 0 1 0 0 1 1 0 0 2 0" << std::endl
		<< "0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1" << std::endl
		<< "0 0 1 0 0 1 0 0 1 0 0 1 0 0 1 0 0 1" << std::endl
		<< "0 0 1 0 0 1 0 0 1" << std::endl;
	return stream;
}

TEST( VTKFileTest, TestUnstructuredGrid )
{
	std::stringstream stream = ::getUnstructuredGrid();

	VTKFile file;
	const bool isOpen = file.read( stream );
	const VTKPoints& points = file.getGeometryPart().getPoints();
	EXPECT_EQ( 27, points.getPoints().size() );
	EXPECT_EQ( 11, file.getGeometryPart().getCells().size() );

	EXPECT_EQ( 27, file.getAttributePart().getPointAttribute().getScalars().front().getValues().size() );
	EXPECT_EQ( 27, file.getAttributePart().getPointAttribute().getVectors().front().getValues().size() );

	EXPECT_EQ( Vector3d( 1.0, 0.0, 0.0 ), file.getAttributePart().getPointAttribute().getVectors().front().getValues().front() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 1.0 ), file.getAttributePart().getPointAttribute().getVectors().front().getValues().back() );
}

/*
std::vector< Vector3d > createTornado2d( const Vector3d& center )
{
	std::vector< Vector3d > vectors;
	for( float angle = 0; angle < 360.0; angle += 10.0 ) {
		const float x = ::sin( angle * Tolerances::getPI() / 180.0f );
		const float y = ::cos( angle * Tolerances::getPI() / 180.0f );
		Vector3d vector( x, y, 0.0 );
		vector += center;
		vectors.push_back( vector );
	}
}
*/



TEST( VTKFileTest, TestStructuredVolumeData )
{
	VTKFile file;
	VTKStructuredPoints data;
	data.setDimensions( 10, 10, 10 );
	data.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	data.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );

	VTKAttributePart_ attr;
	std::vector< float > values;

	const Vector3d center( 0.5, 0.5, 0.5 );
	for( int z = 0 ; z < data.getDimZ() ; ++z ) {
		for ( int y = 0 ; y < data.getDimY() ; ++y ) {
			for ( int x = 0 ; x < data.getDimZ() ; ++x ) {
				const Vector3d pos( x * 0.1f, y * 0.1f, z * 0.1f);
				const float dist = center.getDistance( pos );
				values.push_back( dist );
			}
		}
	}

	VTKScalars s;
	s.setLookupTableName( "default" );
	s.setName( "values" );
	s.setType( VTKType::FLOAT );
	s.setValues( values );
	VTKScalarsVector ss;
	ss.push_back( s );
	attr.setScalars( ss );

	VTKGeometryPart geom;
	geom.setGeometry( &data );
	file.setGeometryPart( geom );

	VTKAttributePart attrPart;
	attrPart.setPointAttribute( attr ); 
	file.setAttributePart( attrPart );

	std::stringstream stream;
	file.write(stream);
	file.read(stream);

	const VTKPoints& points = file.getGeometryPart().getPoints();
	EXPECT_EQ( 1000, points.getPoints().size() );

	EXPECT_EQ( 1000, file.getAttributePart().getPointAttribute().getScalars().front().getValues().size() );
	//std::ofstream stream("./StructuredVolume.vtk");
	//stream << VTKSampleSource::create( data, attr ).str();
}

TEST( VTKFileTest, TestStructuredGridData )
{
	VTKFile file;
	VTKStructuredGrid grid;
	grid.setDimensions( 10, 10, 10 );
	grid.setType( VTKType::FLOAT );
	std::vector< Vector3d > positions;
	for( int i = 0; i < 10; ++i ) {
		for( int j = 0; j < 10; ++j ) {
			for( int k = 0; k < 10; ++k ) {
				positions.push_back( Vector3d( i* 1.0f, j * 1.0f, k * 1.0f ) );
			}
		}
	}
	grid.setPositions(positions);

	VTKAttributePart_ attr;
	std::vector< float > values;
	for( int z = 0 ; z < grid.getDimZ() ; ++z ) {
		for ( int y = 0 ; y < grid.getDimY() ; ++y ) {
			for ( int x = 0 ; x < grid.getDimZ() ; ++x ) {
				values.push_back(x  + 2.0f*y + 3.0f*z);
			}
		}
	}

	VTKScalars s;
	s.setLookupTableName( "default" );
	s.setName( "values" );
	s.setType( VTKType::FLOAT );
	s.setValues( values );
	VTKScalarsVector ss;
	ss.push_back( s );
	attr.setScalars( ss );

	VTKGeometryPart geom;
	geom.setGeometry( &grid );

	file.setGeometryPart( geom );

	VTKAttributePart attrPart;
	attrPart.setPointAttribute( attr );
	file.setAttributePart( attrPart );


	std::stringstream stream;
	file.write(stream);
	file.read( stream );

	EXPECT_EQ( 1000, file.getGeometryPart().getPoints().size() );
}

TEST( VTKFileTest, TestRectilinearData )
{
	VTKFile file;
	VTKRectlinearGrid grid;
	grid.setDimensions( 2, 2, 2 );
	const std::vector< float > xCoords = { 0.0f, 10.0f };
	grid.setXCoords( xCoords );
	const std::vector< float > yCoords = { 0.1f, 1.1f };
	grid.setYCoords( yCoords );
	std::vector< float > zCoords;
	zCoords.push_back( 10.0f );
	zCoords.push_back( 100.0f );
	grid.setZCoords( zCoords );
	grid.setTypes( VTKType::FLOAT, VTKType::FLOAT, VTKType::FLOAT );

	VTKGeometryPart geom;
	geom.setGeometry( &grid );
	file.setGeometryPart( geom );

	/*
	stream
		<< "SCALARS scalars float" << std::endl
		<< "LOOKUP_TABLE default" << std::endl;

	for( int z = 0 ; z < data.getDimZ() ; ++z ) {
		for ( int y = 0 ; y < data.getDimY() ; ++y ) {
			for ( int x = 0 ; x < data.getDimZ() ; ++x ) {
				stream << (x + 2*y + 3*z) << " ";
			}
		}
	}
	*/

	std::stringstream stream;
	file.write(stream);

	file.read( stream );
	EXPECT_EQ( 8, file.getGeometryPart().getPoints().size() );
}

TEST( VTKFileTest, TestCreateVolume )
{
	Volume volume( 10, 10, 10 );
	VTKStructuredPoints points;
	volume.createHydrogenVolume();
	points.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	points.setDimensions( 10, 10, 10 );
	points.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	VTKFile file;
}

TEST( VTKFileTest, TestCreateHydrogen )
{
	VTKAttributePart attr;
	VTKAttributePart_ pointAttr;
	VTKScalarsVector scalars;
	
	const int size = 8;
	Volume volume( size, size, size );
	const std::vector< float >& values = volume.createHydrogenVolume();
	VTKScalars s;
	s.setLookupTableName( "default" );
	s.setValues( values );
	s.setName( "density" );
	scalars.push_back( s );
	pointAttr.setSize( size * size * size );
	pointAttr.setScalars( scalars );
	attr.setPointAttribute( pointAttr );
	VTKGeometryPart geom;
	VTKStructuredPoints points;
	points.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	points.setDimensions( size, size, size );
	points.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	points.toPoints();
	geom.setGeometry( &points );

	VTKHeaderPart header;
	header.setTitle( "Hydrogen" );
	VTKFile file;
	file.setHeaderPart( header );
	file.setGeometryPart( geom );
	file.setAttributePart( attr );
	EXPECT_EQ( size*size*size, file.getGeometryPart().getPoints().size() );

	//std::ofstream stream("./Hydrogen.vtk");
	//file.write( stream );
}

TEST( VTKFileTest, TestCreateTornado )
{
	const int size = 8;
	Volume volume( size, size, size );
	const std::vector< Vector3d >& values = volume.createTornadoVolume( 0.1f );
	VTKVectors v;
	v.setName( "velocity" );
	v.setValues( values );
	VTKVectorsVector vs;
	vs.push_back( v );

	VTKAttributePart_ pointAttr;
	pointAttr.setVectors( vs );
	pointAttr.setSize( size * size * size );

	VTKAttributePart attr;
	attr.setPointAttribute( pointAttr );

	VTKGeometryPart geom;
	VTKStructuredPoints points;
	points.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	points.setDimensions( size, size, size );
	points.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	points.toPoints();
	geom.setGeometry( &points );

	VTKHeaderPart header;
	header.setTitle("Tornado");

	VTKFile file;
	file.setHeaderPart( header );
	file.setGeometryPart( geom );
	file.setAttributePart( attr );
	//std::ofstream stream("./Tornado.vtk");
	//file.write( stream );
}

