#ifndef __CRYSTAL_IO_AVS_UCD_FILE_H__
#define __CRYSTAL_IO_AVS_UCD_FILE_H__

#include <istream>
#include "Helper.h"

#include "../Math/Vector3d.h"

#include <string>

#include <fstream>

#include "AVSCell.h"

#include "Helper.h"
#include "VTKAttribute.h"

namespace Crystal {
	namespace IO {

class AVSIndexedValue
{
public:
	AVSIndexedValue()
	{}

	AVSIndexedValue(const int index, const std::vector<float>& values) :
		index(index),
		values(values)
	{}

	void read( std::istream& s, const std::vector<int> vectorLengths );

	std::vector< std::vector<float> > toVectors(const std::vector<int>& vectorLengths) const;

	void setIndex( const int index ) { this->index = index; }

	void setValues( const std::vector<float>& values) { this->values = values; }

	int getIndex() const { return index; }

	std::vector< float > getValues() const { return values; }

	bool operator==(const AVSIndexedValue& rhs ) const {
		return
			index == rhs.index &&
			values == rhs.values;
	}

private:
	int index;
	std::vector< float > values;
};

typedef std::vector< AVSIndexedValue > AVSIndexedValueVector;


class AVSNameUnit
{
public:
	AVSNameUnit()
	{}

	AVSNameUnit(const std::string& name, const std::string& unit) :
		name( name ),
		unit( unit )
	{
	}
	void read(std::istream& s);

	void setName( const std::string& name ) { this->name = name; }

	void setUnit( const std::string& unit ) { this->unit = unit; }

	std::string getName() const { return name; }

	std::string getUnit() const { return unit; }

	bool operator==( const AVSNameUnit& rhs ) const {
		return
			name == rhs.name &&
			unit == rhs.unit;
	}

private:
	std::string name;
	std::string unit;

	std::vector<std::string> split(const std::string& input,  char delim )
	{
		std::istringstream stream(input);
		std::vector<std::string> result;
		std::string field;
		while (std::getline(stream, field, delim)) {
			result.push_back(field);
		}
		if( result.size() == 1 ) {
			result.push_back("");
		}
		return result;
	}	
};

typedef std::vector< AVSNameUnit > AVSNameUnitVector;


class AVSComponent
{
public:
	AVSComponent()
	{}

	AVSComponent(const std::vector<int>& vectorLengths, const AVSNameUnitVector& nameUnits, const AVSIndexedValueVector& iValues) :
		vectorLengths(vectorLengths),
		nameUnits(nameUnits),
		iValues(iValues)
	{}

	void read(std::istream& stream, const int componentCount, const int howMany);

	std::vector<int> getVectorLengths() const { return vectorLengths; }

	AVSNameUnitVector getNameUnits() const { return nameUnits; }

	AVSIndexedValueVector getIndexedValues() const{ return iValues; }

	VTKAttributeVector toVTKAttributes() const;

	bool operator==( const AVSComponent& rhs ) const {
		return
			vectorLengths == rhs.vectorLengths &&
			nameUnits == rhs.nameUnits &&
			iValues == rhs.iValues;
	}

private:	
	std::vector<int> vectorLengths;
	AVSNameUnitVector nameUnits;
	AVSIndexedValueVector iValues;

	std::vector<std::string> split(const std::string& input,  char delim )
	{
		std::istringstream stream(input);
		std::vector<std::string> result;
		std::string field;
		while (std::getline(stream, field, delim)) {
			result.push_back(field);
		}
		return result;
	}
};

typedef std::vector< AVSComponent > AVSComponentVector;


class AVSUCDComponentBlock {
public:
	void read( std::istream& s, const int nodesCount, const int elementsCount );

	void readLegacy( std::istream& s, const int nodes, const int elements, const int nodeDataCount, const int cellDataCount );

	AVSComponentVector getNodeComponents() const { return nodeComponents; }

	AVSComponentVector getElementComponents() const { return elementComponents; }

private:
	AVSComponentVector nodeComponents;
	AVSComponentVector elementComponents;
};


class AVSCycleType{
public:
	enum Type{
		DATA,
		GEOM,
		DATA_GEOM,
		NONE,
	};

	static Type toType( const std::string& str );

	static std::string toStr( const Type& type );
};


class AVSUCDHeaderBlock {
public:
	AVSUCDHeaderBlock() :
		type( AVSCycleType::DATA ),
		totalSteps( 1 )
	{
	}

	void setComment( const std::string& comment) { this->comment = comment; }

	std::string getComment() const { return comment; }

	void setTotalSteps( const int steps ) { this->totalSteps = steps; }

	int getTotalSteps() const { return totalSteps; }

	void setCycleType( const AVSCycleType::Type& type ) { this->type = type; }

	AVSCycleType::Type getCycleType() const { return type; }

	void read( std::istream& stream );

	void write( std::ostream& stream ) const;

private:
	std::string comment;
	int totalSteps;
	AVSCycleType::Type type;

};

typedef std::pair< unsigned int, Math::Vector3d > AVSUCDNodePair;


class AVSUCDNode {
public:

	void read( std::istream& s, const int howMany ) {
		for( int i = 0; i < howMany; ++i ) {
			AVSUCDNodePair pair;
			pair.first = Helper::read< int >(s);
			pair.second = Helper::readVector(s);
			pairs.push_back( pair );
		}
	}

	void write( std::ostream& s ) {
		for( const AVSUCDNodePair& pair : pairs ) {
			const Math::Vector3d& pos = pair.second ;
			s << pair.first << " ";
			s << pos.getX() << " " << pos.getY() << " " << pos.getZ() << std::endl;
		}
	}

	//void setPositions( const Math::VectorVector& positions ) { this->positions = positions; }

	static bool compare( const AVSUCDNodePair& lhs, const AVSUCDNodePair& rhs ) {
		return lhs.first < rhs.first; 
	}

	Math::Vector3dVector getPositions() {
		std::sort( pairs.begin(), pairs.end(), compare );
		Math::Vector3dVector positions;
		for( const AVSUCDNodePair& pair : pairs ) {
			positions.push_back( pair.second );
		}
		return positions;
	}

	void setPairs( const std::vector< AVSUCDNodePair >& pairs ) { this->pairs = pairs; }

	std::vector< AVSUCDNodePair > getPairs() const { return pairs; }

private:
	std::vector< AVSUCDNodePair > pairs;
};

class AVSElement_ {
public:
	void read( std::istream& s );

	void write( std::ostream& s );

	int getIndex() const { return index; }

	int getMaterialIndex() const { return materialIndex; }

	std::string getType() const { return type; }

	std::vector<unsigned int> getIndices() const { return indices; }

	AVSCell* toCell() const;

private:
	int index;
	int materialIndex;
	std::string type;
	std::vector< unsigned int > indices;
};

class AVSUCDElement {
public:
	void read(std::istream& s, const int howMany);

	void write( std::ostream& s );

	std::vector< AVSElement_ > getCells() const { return cells; }

	AVSCellVector toCells() const;

private:
	std::vector< AVSElement_ > cells;
};


class AVSUCDGeomBlock {
public:
	void read( std::istream& s, int nodesCount, int elementsCount ) {
		node.read( s, nodesCount );
		elem.read( s, elementsCount );
	}

	void write( std::ostream& s ) {
		//node.write( s );
		//elem.write( s );
	}

	void setNode( const AVSUCDNode& node ) { this->node = node; }

	AVSUCDNode getNode() const { return node; }

	void setElement( const AVSUCDElement& elem ) { this->elem = elem; }

	AVSUCDElement getElement() const { return elem; }

private:
	AVSUCDNode node;
	AVSUCDElement elem;

};


class AVSUCDFile
{
public:
	AVSUCDFile()
	{};

	bool read( const std::string& filename );

	bool read( std::istream& stream );

	void write( std::ostream& stream ) const;

	bool readLegacy( std::istream& stream );

	void setGeom( const AVSUCDGeomBlock& geom ) { this->geom = geom; }

	AVSUCDGeomBlock getGeom() const { return geom; }

	void setComponent( const AVSUCDComponentBlock& component ) { this->component = component; }

	AVSUCDComponentBlock getComponent() const { return component; }

	void setHeader( const AVSUCDHeaderBlock& header ) { this->header = header; }

	AVSUCDHeaderBlock getHeader() const { return header; }

private:
	AVSUCDHeaderBlock header;
	AVSUCDGeomBlock geom;
	AVSUCDComponentBlock component;
};

class AVSUCDFileLegacy
{
public:
	AVSUCDFileLegacy()
	{}

private:
	AVSUCDHeaderBlock header;
	AVSUCDGeomBlock geom;
	AVSUCDComponentBlock component;

};

	}
}

#endif
