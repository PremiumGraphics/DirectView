#include "AVSFLDFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

std::vector<float> AVSFLDDataFile::read(std::istream& stream, const int skip, const int offset, const int stride)
{
	std::vector<float> values;

	std::string str;
	for (int i = 0; i < skip; ++i) {
		std::getline(stream, str);
	}

	int j = 0;
	std::getline(stream, str);
	const std::vector<std::string>& strs = ::getSplitted(str, ' ');
	for (size_t i = offset; i < strs.size(); ++i) {
		if (j == 0) {
			values.push_back(static_cast<float>(::atof(strs[i].c_str())));
		}
		if (j < stride) {
			++j;
		}
		if (j == stride) {
			j = 0;
		}
	}

	while (!stream.eof()) {
		std::getline(stream, str);
		const std::vector<std::string>& strs = ::getSplitted(str, ' ');
		for (const std::string& str : strs) {
			if (j == 0) {
				values.push_back(static_cast<float>(::atof(str.c_str())));
			}
			if (j < stride) {
				++j;
			}
			if (j == stride) {
				j = 0;
			}
		}
	}

	return values;
}


std::vector<float> AVSFLDDataFile::readData( std::istream& stream )
{
	return read(stream, skip, offset, stride);
}

bool AVSFLDFile::read( const std::string& pathname, const std::string& filename )
{
	std::ifstream stream;
	stream.open(  pathname + "/" + filename );
	if( !stream.is_open() ) {
		assert( false );
		return false;
	}
	const bool b = read( stream );
	if( !b ) {
		return false;
	}
	for( AVSFLDDataFile& gfile : geoFiles ) {
		std::ifstream stream( pathname + "/" + gfile.getFileName() );
		gfile.readData( stream );
	}
	for( AVSFLDDataFile& dFile : datFiles ) {
		std::ifstream stream( pathname + "/" + dFile.getFileName() );
		dFile.readData( stream );
	}
	return true;
}

namespace {
	std::string trimComment(const std::string& str)
	{
		std::pair< std::string, std::string > strs = ::getSplit( str, '#' );
		return strs.first;
	}

	std::string getTrimmedLine( std::istream& s )
	{
		std::string str;
		std::getline( s, str );
		return trimComment( str );
	}
}

void AVSFLDDataFile::read( const std::string& str )
{
	const std::vector< std::string>& strs = ::getSplitted( str, ' ' );
	for( const std::string& s : strs ) {
		const std::pair< std::string, std::string>& pair = ::getSplit( s, '=' );
		if( pair.first == "file" ) {
			filename = pair.second;
		}
		else if( pair.first == "filetype") {
			fileType = pair.second;
		}
		else if( pair.first == "skip" ) {
			skip = ::atoi( pair.second.c_str() );
			continue;
		}
		else if( pair.first == "offset" ) {
			offset = ::atoi( pair.second.c_str() );
			continue;
		}
		else if( pair.first == "stride" ) {
			stride = ::atoi( pair.second.c_str() );
			continue;
		}
	}
}

bool AVSFLDFile::read( std::istream& s )
{
	std::string str;

	std::pair< std::string, std::string > strs;

	while( !s.eof() ) {
		std::getline(s, str);
		if (!str.empty() && str.front() == '#') {
			continue;
		}
		str = trimComment(str);
		std::vector<std::string> strs = ::getSplitted( str, ' ' );
		if( strs.empty() ) {
			continue;
		}
		if( strs.front() == "coord"  ) {
			AVSFLDDataFile dataFile;
			dataFile.read( str );
			geoFiles.push_back( dataFile );
			continue;
		}
		else if( strs.front() == "variable" ) {
			AVSFLDDataFile dataFile;
			dataFile.read( str );
			datFiles.push_back( dataFile );
			continue;
		}
		const std::vector< std::string > splitted = Helper::split(str, '='); //::getSplit( strs.front(), '=' );
		std::pair< std::string, std::string > pair( trim(splitted[0]), trim(splitted[1]));

		if (pair.first == "field") {
			fieldType = AVSFieldType::toType( pair.second );
		}
		else if ( pair.first == "data") {
			dataType = AVSDataType::toType( pair.second );
		}
		else if (pair.first == "ndim") {
			dim = atoi(pair.second.c_str());

			for (int i = 0; i < dim; ++i) {
				str = getTrimmedLine(s);
				const std::vector<std::string>& strs = ::getSplitted(str, '=');
				const int dim = atoi(strs[1].c_str());
				dimensions.push_back(dim);
			}
		}
		else if (pair.first == "veclen") {
			vecLength = atoi( pair.second.c_str() );
		}
		else if (pair.first == "nspace") {
			nSpace = atoi( pair.second.c_str() );
		}
		else if( pair.first == "min_ext" ) {
			std::vector<std::string> strs_ = ::getSplitted( pair.second, ' ' );
			for( const std::string& s : strs_ ) {
				char *ep;
				const double v = strtod( s.c_str(), &ep );
				if( *ep != '\0' ) {
					;
				}
				else {
					minExts.push_back( static_cast<float>(v) );
				}
			}
		}
		else if( pair.first == "max_ext" ) {
			std::vector<std::string>& strs_ = ::getSplitted( pair.second, ' ' );
			for( const std::string& s : strs_ ) {
				char *ep;
				const double v = strtod( s.c_str(), &ep );
				if( *ep != '\0' ) {
					;
				}
				else {
					maxExts.push_back( static_cast<float>(v) );
				}
			}
			continue;
		}
		else if( pair.first == "label" ) {
			labels.push_back( pair.second );
			continue;
		}
		else if( pair.first == "unit" ) {
			units.push_back( pair.second );
			continue;
		}
		else if( pair.first == "min_val") {
			continue;
		}
		else if( pair.first == "max_val") {
			continue;
		}
		else {
			break;
		}
	}


	return true;
}

#include <numeric>

std::vector< Vector3d > AVSFLDFile::toPositions() const
{
	assert( dimensions.size() == geoFiles.size() );

	if( dimensions.empty() ) {
		return Math::Vector3dVector();
	}

	//const int dims = std::accumulate( dimensions.begin(), dimensions.end(), 0 );
	size_t dims = 1;
	for( size_t i = 0; i < dimensions.size(); ++i ) {
		dims *= dimensions[i];
	}

	std::vector< Math::Vector3d > positions( dims );

	if( dimensions.size() >= 1 ) {
		const std::vector< float >& xValues = geoFiles[0].getValues();
		//assert( dimensions[0] == xValues.size() );
		for( size_t i = 0; i < dims; ++i ) {
			positions[i].setX( xValues[i] );
		}
	}
	if( geoFiles.size() >= 2 ) {
		const std::vector< float >& yValues = geoFiles[1].getValues();
		//assert( dimensions[1] == yValues.size() );
		for( size_t i = 0; i < dims; ++i ) {
			positions[i].setY( yValues[i] );
		}
	}
	if( geoFiles.size() >= 3 ) {
		const std::vector< float >& zValues = geoFiles[2].getValues();
		//assert( dimensions[2] == zValues.size() );
		for( size_t i = 0; i < dims; ++i ) {
			positions[i].setZ( zValues[i] );
		}
	}

	return positions;
}

std::vector< float > AVSFLDFile::toScalarValues() const
{
	std::vector< float > values;
	if( datFiles.size() >= 1 ) {
		values = datFiles[0].getValues();
	}
	if( datFiles.size() >= 2 ) {
		const std::vector<float>& v = datFiles[1].getValues();
		values.insert( values.end(), v.begin(), v.end() );
	}
	if( datFiles.size() >= 3 ) {
		const std::vector<float>& v = datFiles[2].getValues();
		values.insert( values.end(), v.begin(), v.end() );
	}
	return values;
}

std::vector< Vector3d > AVSFLDFile::toVector3dValues() const
{
	if( vecLength < 1 ) {
		return Vector3dVector();
	}

	//const int dims = std::multi( dimensions.begin(), dimensions.end(), 0 );
	size_t dims = 1;
	for( size_t i = 0; i < dimensions.size(); ++i ) {
		dims *= dimensions[i];
	}

	Vector3dVector vectors( dims );
	if( vecLength >= 1 ) {
		const std::vector< float >& xValues = datFiles[0].getValues();
		for( size_t i = 0; i < dims; ++i ) {
			vectors[i].setX( xValues[i] );
		}
	}
	if( vecLength >= 2 ) {
		const std::vector< float >& yValues = datFiles[1].getValues();
		for( size_t i = 0; i < dims; ++i ) {
			vectors[i].setY( yValues[i] );
		}
	}
	if( vecLength >= 3 ) {
		const std::vector< float >& zValues = datFiles[2].getValues();
		for( size_t i = 0; i < dims; ++i ) {
			vectors[i].setZ( zValues[i] );
		}
	}
	return vectors;
}
