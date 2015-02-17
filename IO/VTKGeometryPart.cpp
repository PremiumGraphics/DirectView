#include "VTKGeometryPart.h"

using namespace Crystal::Math;
using namespace Crystal::IO;


void VTKGeometryPart::read(std::istream& stream )
{
	const std::string& dataSetStr = Helper::read< std::string >(stream);
	assert( dataSetStr == "DATASET" );

	const std::string& nextStr = Helper::readNextString(stream);

	VTKGeometryBase* geom = nullptr;
	if( nextStr == "STRUCTURED_POINTS" ) {
		geom = new VTKStructuredPoints();
	}
	else if( nextStr == "STRUCTURED_GRID" ) {
		geom = new VTKStructuredGrid();
	}
	else if( nextStr == "RECTILINEAR_GRID" ) {
		geom = new VTKRectlinearGrid();
	}
	else if( nextStr == "POLYDATA" ) {
		geom = new VTKPolygonalData();
	}
	else if( nextStr == "UNSTRUCTURED_GRID" ) {
		geom = new VTKUnstructuredGrid();
	}
	else if( nextStr == "FIELD" ) {
		return;
	}
	else {
		assert( false );
	}
	geom->read( stream );
	this->points = geom->getPositions();
	this->cells = geom->getCells();
	delete geom;
}

void VTKGeometryPart::write(std::ostream& stream ) const
{
	if( geom == nullptr ) {
		return;
	}
	stream << "DATASET ";
	geom->write( stream );
}

void VTKStructuredPoints::read( std::istream& s )
{
	std::string str = Helper::read<std::string>(s);
	assert( str == "STRUCTURED_POINTS" );

	str = Helper::read<std::string>(s);
	assert( str == "DIMENSIONS" );
	dimX = Helper::read<int>(s);
	dimY = Helper::read<int>(s);
	dimZ = Helper::read<int>(s);
	assert( 1 <= dimX );
	assert( 1 <= dimY );
	assert( 1 <= dimZ );

	str = Helper::read<std::string>(s);
	if( str == "ASPECT_RATIO" ) {
		aspect = Helper::readVector(s);
		str = Helper::read<std::string>(s);
		assert( str == "ORIGIN" );
		origin = Helper::readVector(s);
	}
	else if( str == "ORIGIN") {
		origin = Helper::readVector(s);
		str = Helper::read<std::string>(s);
		assert( str == "SPACING" );
		aspect = Helper::readVector(s);	
	}
	else {
		assert( false );
	}
	toPoints();
}

void VTKStructuredPoints::toPoints() {
	std::vector< Vector3d > positions;
	for( int i = 0; i < dimX; ++i ) {
		for( int j = 0; j < dimY; ++j ) {
			for( int k = 0; k < dimZ; ++k ) {
				const float x = origin.getX() + aspect.getX() * i;
				const float y = origin.getY() + aspect.getY() * j;
				const float z = origin.getZ() + aspect.getZ() * k;
				positions.push_back( Math::Vector3d( x, y, z ) );
			}
		}
	}
	this->positions.setPoints( positions );
}

void VTKStructuredPoints::write( std::ostream& s ) const
{
	s << "STRUCTURED_POINTS" << std::endl;
	s << "DIMENSIONS " << dimX << " " << dimY << " " << dimZ << std::endl;
	s << "ORIGIN "<< origin.getX() << " " << origin.getY() << " " << origin.getZ() << std::endl;
	s << "SPACING " << aspect.getX() << " " << aspect.getY() << " " << aspect.getZ() << std::endl;
}


void VTKStructuredGrid::read(std::istream& stream )
{
	std::string str = Helper::read<std::string>(stream);
	assert( str == "STRUCTURED_GRID" );
	str = Helper::read<std::string>(stream);
	assert( str == "DIMENSIONS" );
	dimX = Helper::read<int>(stream);
	dimY = Helper::read<int>(stream);
	dimZ = Helper::read<int>(stream);
	assert( 1 <= dimX );
	assert( 1 <= dimY );
	assert( 1 <= dimZ );

	str = Helper::read<std::string>(stream);
	assert( str == "POINTS" );
	const int howMany = Helper::read<int>(stream);
	type = VTKType( Helper::read<std::string>(stream) );
	std::vector< Vector3d > positions;
	for( int i = 0; i < howMany; ++i ) {
		const Math::Vector3d& v = Helper::readVector(stream);
		positions.push_back( v );
	}
	this->positions.setPoints( positions );
}


void VTKStructuredGrid::write(std::ostream& stream ) const
{
	stream << "STRUCTURED_GRID" << std::endl;
	stream << "DIMENSIONS ";
	stream << dimX << " " << dimY << " " << dimZ << std::endl;
	stream << "POINTS ";
	stream << positions.getPoints().size() << " ";
	stream << type.toString() << std::endl;
	for( const Vector3d& v : positions.getPoints() ) {
		stream << v.getX() << " " << v.getY() << " " << v.getZ() << std::endl;
	}
}

void VTKUnstructuredGrid::read( std::istream& s )
{
	std::string str = Helper::read< std::string >(s);
	assert( str == "UNSTRUCTURED_GRID" );

	positions.read( s ); 

	str = Helper::read<std::string>(s);
	assert( str == "CELLS" );
		
	cells = readCells( s, VTKCellType::NONE );

	const std::string& cellType = Helper::read< std::string >(s);		
	assert( cellType == "CELL_TYPES" );

	const int typesNumber = Helper::read< int >(s);

	for( int i = 0; i < typesNumber; ++i ) {
		const int type = Helper::read< int >(s);
		types.push_back( type );
		cells[i].setType( (VTKCellType)type );
	}
}

void VTKUnstructuredGrid::write( std::ostream& stream ) const
{
	stream << "UNSTRUCTURED_GRID" << std::endl;
	
	positions.write( stream, positions );

	stream << "CELLS ";

	writeCells( stream );

	stream << "CELL_TYPES " << cells.size() << std::endl;

	for( const VTKCell_& c : cells ) {
		stream << c.getType() << std::endl;
	}
}

std::vector< VTKCell_ >  VTKUnstructuredGrid::readCells(std::istream& stream, const VTKCellType& type)
{
	std::vector<VTKCell_> cells;

	const int number = Helper::read<int>(stream);
	const int total = Helper::read<int>(stream);

	for( int i = 0; i < number; ++i )  {	
		VTKCell_ cell;
		const int howMany = Helper::read<int>(stream);
		std::vector< unsigned int > indices;
		for( int j = 0; j < howMany; j++ ) {
			indices.push_back( Helper::read<int>(stream) );
		}
		cell.setIndices( indices );
		cells.push_back( cell );
	};
	return cells;
}

void VTKUnstructuredGrid::writeCells( std::ostream& stream ) const
{
	const int total = 4; // todo.
	stream << cells.size() << " " << total << std::endl;

	for( VTKCell_ c : cells ) {
		stream << c.getIndices().size();
		std::vector< unsigned int > indices = c.getIndices();
		for( const int i : indices ) {
			stream << " " << i;
		}
		stream << std::endl;
	}
}

void VTKRectlinearGrid::read( std::istream& stream ) {
	std::string str;
	str = Helper::read<std::string>(stream);
	assert( str == "RECTILINEAR_GRID" );
	str = Helper::read< std::string >(stream);

	assert( str == "DIMENSIONS" );
	dimX = Helper::read< int >(stream);
	dimY = Helper::read< int >(stream);
	dimZ = Helper::read< int >(stream);

	str  = Helper::read< std::string >(stream);
	assert( str == "X_COORDINATES" );
		
	const int howManyX = Helper::read< int >(stream);
	str = Helper::read< std::string >(stream);
	xType = VTKType( str );

	xCoords.resize( howManyX );
	for( int i = 0; i < howManyX; ++i ) {
		xCoords[i] = Helper::read<float>(stream);
	}

	str  = Helper::read< std::string >(stream);
	assert( str == "Y_COORDINATES" );

	const int howManyY = Helper::read< int >(stream);
	str = Helper::read< std::string >(stream);
	yType = VTKType( str );

	yCoords.resize( howManyY );
	for( int i = 0; i < howManyY; ++i ) {
		yCoords[i] = Helper::read<float>(stream);
	}

	str  = Helper::read< std::string >(stream);
	assert( str == "Z_COORDINATES" );

	const int howManyZ = Helper::read< int >(stream);
	str = Helper::read< std::string >(stream);
	zType = VTKType( str );

	zCoords.resize( howManyZ );
	for( int i = 0; i < howManyZ; ++i ) {
		zCoords[i] = Helper::read<float>(stream);
	}

	std::vector< Vector3d > positions;
	for( const float x : xCoords ) {
		for( const float y : yCoords ) {
			for( const float z : zCoords ) {
				positions.push_back( Vector3d( x, y, z ) );
			}
		}
	}
	this->positions.setPoints( positions );
}

void VTKRectlinearGrid::write( std::ostream& stream ) const
{
	stream << "RECTILINEAR_GRID" << std::endl;
	stream << "DIMENSIONS ";
	stream << dimX << " " << dimY << " " << dimZ << std::endl;
	stream << "X_COORDINATES ";
	stream << xCoords.size() << " ";
	stream << xType.toString() << std::endl;
	for( const float x : xCoords ) {
		stream << x << " ";
	}
	stream << std::endl;
	stream << "Y_COORDINATES ";
	stream << yCoords.size() << " ";
	stream << yType.toString() << std::endl;
	for( const float y : yCoords ) {
		stream << y << " ";
	}
	stream << std::endl;
	stream << "Z_COORDINATES ";
	stream << zCoords.size() << " ";
	stream << zType.toString() << std::endl;
	for( const float z : zCoords ) {
		stream << z << " ";
	}
	stream << std::endl;
}


void VTKPolygonalData::read(std::istream& stream) {
	std::string str = Helper::read<std::string>(stream);
	assert( str == "POLYDATA" );

	positions.read( stream );
			
	const std::string& ptype = Helper::read<std::string>(stream);
	
	VTKCellType type;
	if( ptype == "POLYGONS" ) {
		type = VTKCellType::POLYGON;
	}
	else if( ptype == "VERTICES" ) {
		type = VTKCellType::VERTEX;
	}
	else if( ptype == "LINES" ) {
		type = VTKCellType::POLY_LINE;
	}
	else if( ptype == "TRIANGLE_STRIPS" ) {
		type = VTKCellType::TRIANGLE_STRIP;
	}
	else {
		assert( false );
	}
	cells = readCells( stream, type );
}

void VTKPolygonalData::write(std::ostream& stream) const
{
	stream << "POLYDATA" << std::endl;

	positions.write(stream, positions);

	stream << "POLYGONS ";

	writeCells( stream );
}

std::vector< VTKCell_ > VTKPolygonalData::readCells(std::istream& stream, const VTKCellType& type)
{
	std::vector<VTKCell_> cells;

	const int number = Helper::read<int>(stream);
	const int total = Helper::read<int>(stream);

	for( int i = 0; i < number; ++i )  {	
		VTKCell_ cell;
		const int howMany = Helper::read<int>(stream);
		std::vector< unsigned int > indices;
		for( int j = 0; j < howMany; j++ ) {
			indices.push_back( Helper::read<int>(stream) );
		}
		cell.setIndices( indices );
		cell.setType( type );
		cells.push_back( cell );
	};
	return cells;
}

void VTKPolygonalData::writeCells( std::ostream& stream ) const
{
	int total = 0; // todo.
	for( VTKCell_ c : cells ) {
		total++;
		total += c.getIndices().size();
	}

	stream << cells.size() << " " << total << std::endl;

	for( VTKCell_ c : cells ) {
		stream << c.getIndices().size();
		std::vector< unsigned int > indices = c.getIndices();
		for( const int i : indices ) {
			stream << " " << i;
		}
		stream << std::endl;
	}
}
