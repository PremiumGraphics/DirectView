#include "gtest/gtest.h"

#include "VTKGeometryPart.h"

using namespace Crystal::Math;
using namespace Crystal::IO;


TEST( VTKGeometryPartTest, TestReadStructuredPoints )
{
	std::stringstream stream;
	stream
		<< "DATASET STRUCTURED_POINTS" << std::endl
		<< "DIMENSIONS 3 4 6" << std::endl
		<< "ASPECT_RATIO 1 1 1" << std::endl
		<< "ORIGIN 0 0 0" << std::endl;
	//	<< "POINT_DATA 72" << std::endl;

	VTKGeometryPart dataSet;
	dataSet.read( stream );
	const VTKPoints& points = dataSet.getPoints();
	EXPECT_EQ( 72, points.size() );
	EXPECT_TRUE( dataSet.getCells().empty() );
}

TEST( VTKGeometryPartTest, TestWriteStructuredPoints )
{
	VTKGeometryPart geom;
	VTKStructuredPoints structured;
	structured.setDimensions( 3, 4, 6 );
	structured.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	structured.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	geom.setGeometry( &structured );

	std::ostringstream stream;
	geom.write( stream );

	const std::string& actual = stream.str();
	//structured.set
	//geom.setGeometry( 
}

TEST( VTKGeometryPartTest, TestQuad )
{
	std::stringstream stream;
	stream
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 4 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 1 0" << std::endl
		<< "CELLS 1 5" << std::endl
		<< "4 0 1 2 3" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "9" << std::endl;
	//file.read( stream );
	VTKGeometryPart dataSet;
	dataSet.read( stream );
	EXPECT_EQ( 4, dataSet.getPoints().size() );
	EXPECT_EQ( 1, dataSet.getCells().size() );
	EXPECT_EQ( VTKCellType::QUAD, dataSet.getCells().front().getType() );
}

TEST( VTKGeometryPartTest, TestHexahedron )
{
	std::stringstream stream;
	stream
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 8 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 1 0" << std::endl
		<< "0 0 1" << std::endl
		<< "1 0 1" << std::endl
		<< "1 1 1" << std::endl
		<< "0 1 1" << std::endl
		<< "CELLS 1 9" << std::endl
		<< "8 0 1 2 3 4 5 6 7" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "12" << std::endl;

	VTKGeometryPart dataSet;
	dataSet.read( stream );
	EXPECT_EQ( 8, dataSet.getPoints().getPoints().size() );
	EXPECT_EQ( 1, dataSet.getCells().size() );
	EXPECT_EQ( VTKCellType::HEXAHEDRON, dataSet.getCells().front().getType() );
}

TEST( VTKGeometryPartTest, TestPyramid )
{
	std::stringstream stream;
	stream
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 5 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 1 0" << std::endl
		<< "0.5 0.5 1" << std::endl
		<< "CELLS 1 6" << std::endl
		<< "5 0 1 2 3 4" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "14" << std::endl;

	VTKGeometryPart dataSet;
	dataSet.read( stream );
	
	EXPECT_EQ( 5, dataSet.getPoints().getPoints().size() );
	EXPECT_EQ( Vector3d( 0.0, 0.0, 0.0), dataSet.getPoints().getPoints().front() );
	EXPECT_EQ( Vector3d( 0.5, 0.5, 1.0), dataSet.getPoints().getPoints().back() );
	const std::vector< VTKCell_ >& cells = dataSet.getCells();
	EXPECT_EQ( 1, cells.size() );
	EXPECT_EQ( 0, cells.front().getIndices().front() );
	EXPECT_EQ( 4, cells.front().getIndices().back() );
	EXPECT_EQ(VTKCellType::PYRAMID, cells.front().getType() );
}

TEST( VTKGeometryPartTest, TestTetra )
{
	std::stringstream stream;
	stream
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 4 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0.8 0.2 1" << std::endl
		<< "CELLS 1 5" << std::endl
		<< "4 0 1 2 3" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "10" << std::endl;

	VTKGeometryPart dataSet;
	dataSet.read( stream );
	EXPECT_EQ( 4, dataSet.getPoints().getPoints().size() );
	const std::vector< VTKCell_ >& cells = dataSet.getCells();
	EXPECT_EQ( 1, cells.size() );
	EXPECT_EQ( VTKCellType::TETRA, cells.front().getType() );
}

TEST( VTKGeometryPartTest, TestWedge )
{
	std::stringstream stream;
	stream
		<< "DATASET UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 6 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 0 1" << std::endl
		<< "1 0 1" << std::endl
		<< "1 1 1" << std::endl
		<< "CELLS 1 7" << std::endl
		<< "6 0 1 2 3 4 5" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "13" << std::endl;

	VTKGeometryPart dataSet;
	dataSet.read( stream );
	EXPECT_EQ( 6, dataSet.getPoints().getPoints().size() );
	EXPECT_EQ( 1, dataSet.getCells().size() );
	EXPECT_EQ( VTKCellType::WEDGE, dataSet.getCells().front().getType() );
}

std::stringstream getStructuredGridSample()
{
	std::stringstream stream;
	stream
		<< "STRUCTURED_GRID" << std::endl
		<< "DIMENSIONS 1 1 1" << std::endl
		<< "POINTS 3 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl;
	return stream;
}

TEST( VTKGeometryPartDetailTest, TestStructuredGridRead )
{
	VTKStructuredGrid grid;
	grid.read( getStructuredGridSample() );
	EXPECT_EQ( 1, grid.getDimX() );
	EXPECT_EQ( 1, grid.getDimY() );
	EXPECT_EQ( 1, grid.getDimZ() );

	EXPECT_EQ( "float", grid.getType().toString() );
}

TEST( VTKGeometryPartDetailTest, TestStructuredGridWrite )
{
	VTKStructuredGrid grid;
	grid.setDimensions( 1, 1, 1 );

	grid.setType( VTKType::Type::FLOAT );
	const std::vector< Vector3d > positions = {
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	grid.setPositions( positions );

	std::ostringstream stream;
	grid.write( stream );
	
	const std::string& actual = stream.str();
	const std::string& expected = getStructuredGridSample().str();
	EXPECT_EQ( expected, actual );
}

std::stringstream getStructuredPointsVersion1()
{
	std::stringstream stream;
	stream
		<< "STRUCTURED_POINTS" << std::endl
		<< "DIMENSIONS 3 4 6" << std::endl
		<< "ASPECT_RATIO 1 1 1" << std::endl
		<< "ORIGIN 0 0 0" << std::endl;
	return stream;
}

TEST( VTKStructuredPointsTest, TestVersion1 )
{
	VTKStructuredPoints actual;
	actual.read( getStructuredPointsVersion1() );

	VTKStructuredPoints expected;
	expected.setDimensions( 3, 4, 6 );
	expected.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	expected.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );

	EXPECT_EQ( expected, actual );
}

TEST( VTKStructuredPointsTest, TestVersion3 )
{
	std::stringstream stream;
	stream
		<< "STRUCTURED_POINTS" << std::endl
		<< "DIMENSIONS 3 4 6" << std::endl
		<< "ORIGIN 0 0 0" << std::endl
		<< "SPACING 1 1 1" << std::endl;

	VTKStructuredPoints actual;
	actual.read( stream );

	VTKStructuredPoints expected;
	expected.setDimensions( 3, 4, 6 );
	expected.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	expected.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );

	EXPECT_EQ( expected, actual );
}

std::stringstream getSampleRectilinear()
{
	std::stringstream stream;
	stream
		<< "RECTILINEAR_GRID" << std::endl
		<< "DIMENSIONS 1 1 1" << std::endl
		<< "X_COORDINATES 3 float" << std::endl
		<< "0 1 2 " << std::endl
		<< "Y_COORDINATES 3 int" << std::endl
		<< "0 1 2 " << std::endl
		<< "Z_COORDINATES 2 float" << std::endl
		<< "0 1 " << std::endl;
	return stream;
}

TEST( VTKRectlinearGridTest, TestRead )
{
	VTKRectlinearGrid grid;
	grid.read( getSampleRectilinear() );
	EXPECT_EQ( 1, grid.getDimX() );

	EXPECT_EQ( "float", grid.getTypeX().toString() );
	EXPECT_EQ( "int", grid.getTypeY().toString() );
	EXPECT_EQ( "float", grid.getTypeZ().toString() );

	EXPECT_EQ( 3, grid.getXCoords().size() );
	EXPECT_EQ( 3, grid.getYCoords().size() );
	EXPECT_EQ( 2, grid.getZCoords().size() );

	const std::vector< Vector3d >& points = grid.getPositions().getPoints();
	EXPECT_EQ( 18, points.size() );
}

TEST( VTKRectlinearGridTest, TestWrite )
{
	VTKRectlinearGrid grid;
	grid.setDimensions( 1, 1, 1 );
	grid.setXCoords( std::vector< float > { 0.0f, 1.0f, 2.0f });
	grid.setYCoords( std::vector< float > { 0.0f, 1.0f, 2.0f });
	const std::vector< float > zCoords = { 0.0f, 1.0f };
	grid.setZCoords( zCoords );
	grid.setTypes( VTKType::FLOAT, VTKType::INT, VTKType::FLOAT );

	std::ostringstream stream;
	grid.write( stream );
	const std::string& actual = stream.str();
	const std::string& expected = getSampleRectilinear().str();
	EXPECT_EQ( expected, actual );
}

std::stringstream getUnstructuredGridSample()
{
	std::stringstream stream;
	stream
		<< "UNSTRUCTURED_GRID" << std::endl
		<< "POINTS 3 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "CELLS 1 4" << std::endl
		<< "3 0 1 2" << std::endl
		<< "CELL_TYPES 1" << std::endl
		<< "5" << std::endl;
	return stream;
}

TEST( VTKUnstructuredGridTest, TestTriangleRead )
{
	VTKUnstructuredGrid grid;
	grid.read( getUnstructuredGridSample() );
	//EXPECT_EQ( 3, file.getPoints().points.size() );
	EXPECT_EQ( 3, grid.getPositions().getPoints().size() );
	EXPECT_EQ( 1, grid.getCells().size() );
	EXPECT_EQ( VTKCellType::TRIANGLE, grid.getCells().front().getType() );
}

TEST( VTKUnstructuredGridTest, TestTriangleWrite )
{
	VTKUnstructuredGrid grid;
	const std::vector< Vector3d > positions{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0)
	};
	grid.setPositions( positions );
	grid.setType( VTKType::FLOAT );

	std::vector< VTKCell_ > cells;
	VTKCell_ cell;
	const std::vector< unsigned int > indices = { 0, 1, 2 };
	cell.setIndices( indices );
	cell.setType( VTKCellType::TRIANGLE );
	cells.push_back( cell );
	grid.setCells( cells );

	std::ostringstream stream;
	grid.write( stream );
	const std::string& actual = stream.str();

	const std::string& expected = getUnstructuredGridSample().str();
	EXPECT_EQ( expected, actual );
}

std::stringstream getPolygonalDataSample()
{
	std::stringstream stream;
	stream
		<< "POLYDATA" << std::endl
		<< "POINTS 4 float" << std::endl
		<< "0 0 0" << std::endl
		<< "1 0 0" << std::endl
		<< "1 1 0" << std::endl
		<< "0 1 0" << std::endl
		<< "POLYGONS 1 5" << std::endl
		<< "4 0 1 2 3" << std::endl;
	return stream;
}

TEST( VTKPolygonalDataTest, TestRead )
{
	VTKPolygonalData data;
	data.read( getPolygonalDataSample() );

	const Vector3dVector expected = {
		Vector3d(0.0f, 0.0f, 0.0f),
		Vector3d(1.0f, 0.0f, 0.0f),
		Vector3d(1.0f, 1.0f, 0.0f),
		Vector3d(0.0f, 1.0f, 0.0f)
	};
	EXPECT_EQ( 4, data.getPositions().size() );
}

TEST( VTKPolygonalDataTest, TestWrite )
{
	std::ostringstream stream;
	VTKPolygonalData data;
	VTKPoints points;
	points.setType( VTKType::FLOAT );
	const std::vector< Vector3d > point{
		Vector3d(0.0, 0.0, 0.0),
		Vector3d(1.0, 0.0, 0.0),
		Vector3d(1.0, 1.0, 0.0),
		Vector3d(0.0, 1.0, 0.0)
	};
	points.setPoints( point );
	data.setPositions( points );
	std::vector< VTKCell_ > cells;
	VTKCell_ cell;
	const std::vector< unsigned int > indices = { 0, 1, 2, 3 };
	cell.setIndices( indices );
	cell.setType( VTKCellType::POLYGON );
	cells.push_back( cell );
	data.setCells( cells );
	data.write( stream );
	
	const std::string& expected = getPolygonalDataSample().str();
	const std::string& actual = stream.str();

	EXPECT_EQ( expected, actual );
}