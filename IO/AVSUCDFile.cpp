#include "AVSUCDFile.h"

#include "../Math/Vector3d.h"

#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

//#include <sstream>
#include <cassert>


void AVSIndexedValue::read( std::istream& s, const std::vector<int> vectorLengths )
{
	index = Helper::read< int >(s);
	for( int l : vectorLengths  ) {
		for( int i = 0; i < l; ++i ) {
			const float value = Helper::read< float >(s);
			values.push_back( value ); 
		}
	}
}

std::vector< std::vector<float> > AVSIndexedValue::toVectors(const std::vector<int>& vectorLengths) const
{
	std::vector< std::vector<float > > vv;
	int i = 0;

	for( const int l : vectorLengths ) {
		std::vector< float > vs;
		for( int j = 0; j < l; ++j ) {
			vs.push_back( values[i++] );
		}
		vv.push_back( vs );
	}
	return vv;
}

void AVSNameUnit::read(std::istream& s)
{
	std::string str;
	while( str.empty() ) {
		std::getline( s, str );
	}
	const std::vector<std::string>& strs = split( str, ',' );
	if( strs.size() == 2 ) {
		this->name = strs.front();
		this->unit = strs.back();
	}
	else if( strs.size() == 1 ) {
		this->name = strs.front();
	}
	else {
		assert( false );
	}
}



void AVSComponent::read( std::istream& s, const int componentCount, const int howMany )
{
	std::string str;
	std::getline( s, str );
	const std::vector<std::string>& strs = split( str, ' ' );
	for( const std::string& str : strs ) {
		const int length = ::atoi( str.c_str() );
		if( length != 0 ) {
			vectorLengths.push_back( length );
		}
	}
	for( int length : vectorLengths ) {
		AVSNameUnit nameUnit;
		nameUnit.read( s );
		nameUnits.push_back( nameUnit );
	}
	for( int i = 0; i < howMany; ++i ) {
		AVSIndexedValue iValue;
		iValue.read( s, vectorLengths );
		iValues.push_back( iValue );
	}
}

VTKAttributeVector AVSComponent::toVTKAttributes() const
{
	VTKAttributeVector attributes;
	for( const AVSNameUnit& nameUnit : nameUnits ) {
		VTKAttributes* attr = new VTKAttributes();
		attr->setName( nameUnit.getName() );
		attr->setUnit( nameUnit.getUnit() );
		attr->setLookupTableName( "default" );
		attributes.push_back( attr );
	}
	for( const AVSIndexedValue& iValue : iValues ) {
		std::vector< std::vector<float> > vv = iValue.toVectors( vectorLengths );
		for( size_t i = 0; i < attributes.size(); ++i ) {
			attributes[i]->setDim( vectorLengths[i] );
			attributes[i]->add( vv[i] );
		}
	}
	return attributes;
}


void AVSUCDComponentBlock::read( std::istream& s, const int nodesCount, const int elementsCount ) {
	const int nodeDataNumber = Helper::read<int>(s);
	const int elementDataNumber = Helper::read<int>(s);

	if( nodeDataNumber != 0 ) {
		const int howMany = Helper::read<int>(s);
		AVSComponent nodeComponent;
		nodeComponent.read( s, howMany, nodesCount );
		nodeComponents.push_back( nodeComponent );
	}

	if( elementDataNumber != 0 ) { 
		const int howMany = Helper::read<int>(s);
		AVSComponent elementComponent;
		elementComponent.read(s, howMany, elementsCount );
		elementComponents.push_back( elementComponent );
	}
}

void AVSUCDComponentBlock::readLegacy( std::istream& s, const int nodesCount, const int elementsCount, const int nodeDataCount, const int cellDataCount ) {
	if( nodeDataCount != 0 ) {
		const int howMany = Helper::read<int>(s);
		AVSComponent nodeComponent;
		nodeComponent.read( s, howMany, nodesCount );
		nodeComponents.push_back( nodeComponent );
	}

	if( cellDataCount != 0 ) { 
		const int howMany = Helper::read<int>(s);
		AVSComponent elementComponent;
		elementComponent.read(s, howMany, elementsCount );
		elementComponents.push_back( elementComponent );
	}
}


void AVSElement_::read(std::istream& s )
{
	index = Helper::read< int >(s);
	materialIndex = Helper::read< int >(s);
	this->type = Helper::read< std::string >(s);
		
	if( type == "pt" ) {
		indices.push_back( Helper::read<int>(s) -1 );
	}
	else if( type == "line" ) {
		indices.push_back( Helper::read<int>(s) -1 );
		indices.push_back( Helper::read<int>(s) -1 );
	}
	else if( type == "tri" ) {
		for( int i = 0; i < 3; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else if( type == "quad" ) {
		for( int i = 0; i < 4; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else if( type == "tet" ) {
		for( int i = 0; i < 4; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else if( type == "pyr" ) {
		for( int i = 0; i < 5; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else if( type == "prism" ) {
		for( int i = 0; i < 5; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else if( type == "hex" ) {
		for( int i = 0; i < 8; ++i ) {
			indices.push_back( Helper::read<int>(s)-1 );
		}
	}
	else {
		assert( false );
	}
}

void AVSElement_::write(std::ostream& stream )
{
	stream << index << " " << materialIndex << " " << type << " ";
	for( const int i : indices ) {
		stream << i << " ";
	}
	stream << std::endl;
}

AVSCell* AVSElement_::toCell() const
{
	const AVSCell::Type t = AVSCell::toAVSType( type );
	return AVSCell::create( t, indices );
}

void AVSUCDElement::read(std::istream& s, const int howMany)
{
	for( int i = 0; i < howMany; ++i ) {
		AVSElement_ e;
		e.read( s );
		cells.push_back( e );
	}
}

void AVSUCDElement::write( std::ostream& s )
{
	;
}


AVSCellVector AVSUCDElement::toCells() const
{
	AVSCellVector cellVector;
	for( const AVSElement_& cell : cells ) {
		cellVector.push_back( cell.toCell() );
	}
	return cellVector;
}

AVSCycleType::Type AVSCycleType::toType( const std::string& str ) 
{
	if( str == "data" ) {
		return DATA;
	}
	else if( str == "geom") {
		return GEOM;
	}
	else if( str == "data_geom" ) {
		return DATA_GEOM;
	}
	else {
		return NONE;
	}
}

std::string AVSCycleType::toStr( const Type& type )
{
	if( type == DATA ) {
		return "data";
	}
	else if( type == GEOM ) {
		return "geom";
	}
	else if( type == DATA_GEOM ) {
		return "data_geom";
	}
	else {
		assert( false );
		return "";
	}
}

void AVSUCDHeaderBlock::read( std::istream& stream )
{
	std::string str;
	std::getline( stream, str );	
	while( !str.empty() ) {
		if( str.front() == '#' ) {
			comment += str;
			std::getline( stream, str );	
		}
		else {
			totalSteps = ::atoi( str.c_str() );
			break;
		}
	}
	this->type = AVSCycleType::toType( Helper::read<std::string>(stream) );
}

void AVSUCDHeaderBlock::write( std::ostream& stream ) const
{
	stream << comment << std::endl;
	stream << totalSteps << std::endl;
	stream << AVSCycleType::toStr(type) << std::endl;
}

bool AVSUCDFile::read( const std::string& filename )
{
	std::ifstream stream;
	stream.open( filename );

	if( !stream.is_open() ) {
		return false;
	}

	const bool b = read(stream);

	if( b ) {
		return true;
	}
	
	stream.close();
	stream.clear();
	stream.open( filename );
	return readLegacy( stream );
}


bool AVSUCDFile::read( std::istream& s )
{
	header.read( s );

	const std::string str = Helper::read< std::string >(s);
	if( str != "step1" ) {
		return false;
	}
	const int nodesCount = Helper::read<int>(s);
	const int elementsCount = Helper::read<int>(s);

	geom.read( s, nodesCount, elementsCount );

	component.read( s, nodesCount, elementsCount );

	return true;
}

void AVSUCDFile::write( std::ostream& stream ) const
{
	header.write( stream );
	//geom.write( stream );
}


namespace {
std::vector< std::string > getSplitted(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
	if (!item.empty()) {
			elems.push_back(item);
		}
	}
	return elems;
}
}

bool AVSUCDFile::readLegacy( std::istream& s )
{
	std::string comment;
	std::string str;
	std::getline( s, str );
	int nodesCount;
	int elementsCount;
	int nodeDataCount;
	int cellDataCount;

	while( !str.empty() ) {
		if( str.front() == '#' ) {
			comment += str;
			std::getline( s, str );	
		}
		else {
			std::vector< std::string >& strs = getSplitted( str, ' ' );
			assert( strs.size() == 5 );
			nodesCount = ::atoi( strs[0].c_str() );
			elementsCount = ::atoi( strs[1].c_str() );
			nodeDataCount = ::atoi( strs[2].c_str() );
			cellDataCount = ::atof( strs[3].c_str() );
			break;
		}
	}


	//Helper::read<int>(s);

	geom.read( s, nodesCount, elementsCount );

	component.readLegacy( s, nodesCount, elementsCount, nodeDataCount, cellDataCount );

	return true;


}