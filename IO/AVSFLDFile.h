#ifndef __CRYSTAL_IO_FLD_FILE_H__
#define __CRYSTAL_IO_FLD_FILE_H__

//#include "../Math/Vector3d.h"
#include "../Math/Box.h"

#include "Helper.h"

#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <string>
#include <sstream>


namespace {

std::string trim(const std::string& string, const char* trimCharacterList = " \t\v\r\n")
{
	std::string result;
	
	std::string::size_type left = string.find_first_not_of(trimCharacterList);
	
	if (left != std::string::npos) {
		std::string::size_type right = string.find_last_not_of(trimCharacterList);		
		result = string.substr(left, right - left + 1);
	}

	return result;
}

std::pair< std::string, std::string > getSplit(const std::string &s, char delim) {
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
	if (!item.empty()) {
			elems.push_back(item);
		}
	}
	std::pair< std::string, std::string > pair;
	if( elems.empty() ) {
		return pair;
	}
	pair.first = trim( elems.front() );
	pair.second = trim( elems.back() );
	return pair;
}

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


namespace Crystal {
	namespace IO {

class AVSDataType {
public:
	enum Type{
		Byte,
		Integer,
		Float,
		Double,
		None,
	};

	static Type toType( const std::string& str ) {
		if( str == "byte" ) {
			return Type::Byte;
		}
		else if( str == "integer" ) {
			return Type::Integer;
		}
		else if( str == "float" ) {
			return Type::Float;
		}
		else if( str == "double" ) {
			return Type::Double;
		}
		else {
			assert( false );
			return Type::None;
		}
	}

private:
	
};

class AVSFieldType {
public:
	enum Type {
		Uniform,
		Rectilinear,
		Irregular,
		None,
	};

	static Type toType( const std::string& str ) {
		if( str == "uniform" ) {
			return Type::Uniform;
		}
		else if( str == "rectilinear" ) {
			return Type::Rectilinear;
		}
		else if( str == "irregular" ) {
			return Type::Irregular;
		}
		else {
			assert( false );
			return Type::None;
		}
	}

	static std::string toStr(const Type& type ) {
		switch( type ) {
		case Uniform :
			return "uniform";
		case Rectilinear :
			return "rectilinear";
		case Irregular :
			return "irregular";
		default :
			assert( false );
			return "";
		}
	}
};


class AVSFLDDataFile {
public:
	AVSFLDDataFile() :
		skip( 0 ),
		offset( 0 ),
		stride( 1 )
	{}

	void read( const std::string& str );

	void setFileName( const std::string& filename ) { this->filename = filename; }

	std::string getFileName() const { return filename; }

	void setFileType( const std::string& fileType) { this->fileType = fileType; }

	std::string getFileType() const { return fileType; }

	void setSkip( const int skip ) { this->skip = skip; }

	int getSkip() const { return skip; }

	void setOffset( const int offset ) { this->offset = offset; }

	int getOffset() const { return offset; }

	void setStride( const int stride ) { this->stride = stride; }

	int getStride() const { return stride; }

	bool operator==( const AVSFLDDataFile& rhs ) const {
		return
			filename == rhs.filename &&
			fileType == rhs.fileType &&
			skip == rhs.skip &&
			offset == rhs.offset &&
			stride == rhs.stride;
	}

	std::vector<float> readData( std::istream& stream );

	void setValues( const std::vector< float >& values ) { this->values = values; }

	std::vector<float> getValues() const { return values; }

	static std::vector<float> read(std::istream& stream, const int skip, const int offset, const int stride);

private:
	std::string filename;
	std::string fileType;
	int skip;
	int offset;
	int stride;
	std::vector< float > values;
};

class AVSFLDFile
{
public:
	AVSFLDFile(){};

	bool read( const std::string& pathname, const std::string& filename );

	bool read( std::istream& stream );

	std::vector<float> getValues() const { return values; }

	std::vector< AVSFLDDataFile > getGeoFiles() const { return geoFiles; }

	void setGeoFiles( const std::vector< AVSFLDDataFile>& geoFiles ) { this->geoFiles = geoFiles; }

	std::vector< AVSFLDDataFile > setDatFiles( const std::vector< AVSFLDDataFile>& datFiles ) { return this->datFiles = datFiles; }

	std::vector< AVSFLDDataFile > getDatFiles() const { return datFiles; }

	void setDim( const int dim ) { this->dim = dim; }

	int getDim() const { return dim; }

	void setVecLength( const int length ) { this->vecLength = length; }

	int getVecLength() const { return vecLength; }

	void setDataType(const AVSDataType::Type& type) { this->dataType = type; }

	AVSDataType::Type getDataType() const { return dataType; }

	void setNSpace(const int nSpace) { this->nSpace = nSpace; }

	void setFiledType(const AVSFieldType::Type& type) { this->fieldType = type; }

	int getNSpace() const { return nSpace; }

	void setDimensions( const std::vector<int>& dimensions ) { this->dimensions = dimensions; }

	std::vector< int > getDimensions() const { return dimensions; }

	std::vector< std::string > getLabels() const { return labels; }

	std::vector< std::string > getUnits() const { return units; }

	std::vector< float > getMinExts() const { return minExts; }

	std::vector< float > getMaxExts() const { return maxExts; }

	std::vector< Math::Vector3d > toPositions() const;

	std::vector< float > toScalarValues() const;

	std::vector< Math::Vector3d > toVector3dValues() const;

	bool operator==(const AVSFLDFile& rhs) const {
		return
			dim == rhs.dim &&
			vecLength == rhs.vecLength &&
			nSpace == rhs.nSpace &&
			dataType == rhs.dataType &&
			fieldType == rhs.fieldType &&
			geoFiles == rhs.geoFiles &&
			datFiles == rhs.datFiles &&
			dimensions == rhs.dimensions &&
			values == rhs.values &&
			labels == rhs.labels &&
			units == rhs.units &&
			minExts == rhs.minExts &&
			maxExts == rhs.maxExts;
	}


private:
	int dim;
	int vecLength;
	int nSpace;
	AVSDataType::Type dataType;
	AVSFieldType::Type fieldType;

	std::vector< AVSFLDDataFile > geoFiles;
	std::vector< AVSFLDDataFile > datFiles;

	std::vector< int > dimensions;
	std::vector< float > values;
	std::vector< std::string > labels;
	std::vector< std::string > units;

	std::vector< float > minExts;
	std::vector< float > maxExts;
};

	}
}

#endif
