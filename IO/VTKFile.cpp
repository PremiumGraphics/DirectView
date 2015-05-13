#include "VTKFile.h"

#include "VTKObject.h"

#include "VTKGeometryPart.h"

#include <sstream>

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

#include <cmath>

using namespace Crystal::Math;


void VTKVersion::read( std::istream& stream )
{
	std::string str;
	std::getline( stream, str);

	int pos = str.find_last_of(".");

	major = ::atoi( &str.at(pos-1) );
	minor = ::atoi( &str.at(pos+1) );
}

void VTKVersion::write( std::ostream& stream ) const
{
	stream << "# vtk DataFile Version " << toStr() << std::endl;
}

void VTKFileType::read( std::istream& stream )
{
	const std::string& str =Helper::read< std::string >( stream );
	if( str == "ASCII" ) {
		type = VTKFileType::ASCII;
	}
	else if( str == "BINARY" ) {
		type = VTKFileType::Binary;
	}
	else {
		type = VTKFileType::None;
	}
}

void VTKFileType::write( std::ostream& stream ) const
{
	if( type == VTKFileType::ASCII ) {
		stream << "ASCII";
	}
	else if( type == VTKFileType::Binary ) {
		stream << "BINARY";
	}
	else {
		assert( false );
	}
}

void VTKHeaderPart::read( std::istream& stream )
{
	std::string str;

	version.read( stream );
	
	std::getline( stream, str );
	title = str;

	fileType.read( stream );
}

void VTKHeaderPart::write( std::ostream& stream ) const
{
	version.write( stream );
	stream
		<< title << std::endl
		<< "ASCII"	<< std::endl;
}


float getGauss2d( const float _x, const float _y, const float centerX, const float centerY, const float tau )
{
	const float x = _x - centerX;
	const float y = _y - centerY;

	const float power = - ( x * x + y * y ) / ( 2.0f * tau * tau ) ;
	return 1.0f / ( 2.0f * Tolerancef::getPI() * tau * tau ) * ::exp( power );
}

void VTKFile::setDiffuseData()
{
	this->header.setTitle( "diffuseSample" );
	VTKGeometryPart geom;
	VTKPolygonalData* polygonal = new VTKPolygonalData();
	std::vector< VTKCell_ > cells;
	VTKPoints points;
	std::vector< Vector3d > positions;
	for( int i = 0 ; i < 10; ++i ) {
		for( int j = 0; j < 10; ++j ) {
			Vector3d pos( i * 1.0f, j * 1.0f, 0.0f );
			positions.push_back( pos );
		}
	}
	for( int i = 0; i < 9; ++i ) {
		for( int j = 0; j < 9; ++j ) {
			{
				VTKCell_ cell;
				std::vector< unsigned int > indices;
				indices.push_back( i + j * 10 );
				indices.push_back( (i+1) + j * 10  );
				indices.push_back( i + (j+1) * 10 );
				cell.setIndices( indices );
				cell.setType( VTKCellType::TRIANGLE );
				cells.push_back( cell );
			}
			{
				VTKCell_ cell;
				std::vector< unsigned int > indices;
				indices.push_back( i + (j+1) * 10 );
				indices.push_back( (i+1) + j * 10  );
				indices.push_back( (i+1) + (j+1) * 10 );
				cell.setIndices( indices );
				cell.setType( VTKCellType::TRIANGLE );
				cells.push_back( cell );
			}
		}
	}
	polygonal->setCells( cells );

	points.setPoints( positions );
	polygonal->setPositions( points );
	geom.setGeometry( polygonal );

	this->setGeometryPart( geom );

	VTKAttributePart_ pointAttr;
	
	VTKScalarsVector sv;
	for( int k = 1; k <= 5; ++k ) 
	{
		std::vector< float > values;
		for( int i = 0 ; i < 10; ++i ) {
			for( int j = 0; j < 10; ++j ) {
				const float value1 = getGauss2d( i * 1.0f, j * 1.0f, 0, 0, k * 1.0f );
				const float value2 = -getGauss2d( i * 1.0f, j * 1.0f, 9, 9, k * 1.0f );
				//values.push_back( std::sqrt( i * j ) );
				values.push_back( value1+ value2 );
			}
		}
		VTKScalars s;
		s.setLookupTableName( "default" );
		s.setName( "temperature" + ::std::to_string(k) );
		s.setValues( values );
		sv.push_back( s );
	}

	/*
	{
		std::vector< float > values;
		for( int i = 0 ; i < 10; ++i ) {
			for( int j = 0; j < 10; ++j ) {
				values.push_back( std::sqrt( i * j ) );
			}
		}
		VTKScalars s;
		s.setLookupTableName( "default" );
		s.setName( "pressure" );
		s.setValues( values );
		sv.push_back( s );
	}
	*/


	pointAttr.setScalars( sv );
	pointAttr.setSize( 10 * 10 );
	VTKAttributePart attr;
	attr.setPointAttribute( pointAttr );
	this->setAttributePart( attr );
}

void VTKFile::setCylinderData()
{
	this->header.setTitle( "CylinderSample" );
	VTKGeometryPart geom;
	VTKPolygonalData* polygonal = new VTKPolygonalData();
	std::vector< VTKCell_ > cells;
	VTKPoints points;
	std::vector< Vector3d > positions;
	for( int i = 0 ; i < 10; ++i ) {
		for( int j = 0; j < 360; j += 36 ) {
			Vector3d pos( ::sin( j / 180.0f * Tolerancef::getPI() ), ::cos( j / 180.0f * Tolerancef::getPI() ), i );
			positions.push_back( pos );
		}
	}
	for( int i = 0; i < 9; ++i ) {
		for( int j = 0; j < 9; ++j ) {
			{
				VTKCell_ cell;
				std::vector< unsigned int > indices;
				indices.push_back( i + j * 10 );
				indices.push_back( (i+1) + j * 10  );
				indices.push_back( i + (j+1) * 10 );
				cell.setIndices( indices );
				cell.setType( VTKCellType::TRIANGLE );
				cells.push_back( cell );
			}
			{
				VTKCell_ cell;
				std::vector< unsigned int > indices;
				indices.push_back( i + (j+1) * 10 );
				indices.push_back( (i+1) + j * 10  );
				indices.push_back( (i+1) + (j+1) * 10 );
				cell.setIndices( indices );
				cell.setType( VTKCellType::TRIANGLE );
				cells.push_back( cell );
			}
		}
	}
	polygonal->setCells( cells );

	points.setPoints( positions );
	polygonal->setPositions( points );
	geom.setGeometry( polygonal );

	this->setGeometryPart( geom );

	VTKAttributePart_ pointAttr;
	
	VTKScalarsVector sv;
	for( int k = 1; k <= 5; ++k ) 
	{
		std::vector< float > values;
		for( int i = 0 ; i < 10; ++i ) {
			for( int j = 0; j < 10; ++j ) {
				const float value1 = getGauss2d( i * 1.0f, j* 1.0f, 0, 0, k * 1.0f );
				const float value2 = -getGauss2d( i, j, 9, 9, k );
				//values.push_back( std::sqrt( i * j ) );
				values.push_back( value1+ value2 );
			}
		}
		VTKScalars s;
		s.setLookupTableName( "default" );
		s.setName( "temperature" + ::std::to_string(k) );
		s.setValues( values );
		sv.push_back( s );
	}

	/*
	{
		std::vector< float > values;
		for( int i = 0 ; i < 10; ++i ) {
			for( int j = 0; j < 10; ++j ) {
				values.push_back( std::sqrt( i * j ) );
			}
		}
		VTKScalars s;
		s.setLookupTableName( "default" );
		s.setName( "pressure" );
		s.setValues( values );
		sv.push_back( s );
	}
	*/


	pointAttr.setScalars( sv );
	pointAttr.setSize( 10 * 10 );
	VTKAttributePart attr;
	attr.setPointAttribute( pointAttr );
	this->setAttributePart( attr );
}


bool VTKFile::read( const std::string& filename ) {
	std::ifstream stream;
	stream.open( filename.c_str() );

	std::stringstream ss;
	std::string str;
	while( std::getline( stream, str ) ) {
		ss << str << std::endl;
	}
		
	if( !stream.is_open() ) {
		return false;
	}
	return read( ss );
}

bool VTKFile::read( std::istream& stream ) {
	header.read( stream );
	if( header.getFileType() == VTKFileType::Type::None ) {
		return false;
	}
	
	geom.read( stream );
	
	attr.read( stream );

	return true;
}


