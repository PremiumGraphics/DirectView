#include "ColorRGBAMapIO.h"

#include "Helper.h"

#include <fstream>

using namespace Crystal::Graphics;
using namespace Crystal::IO;

void ColorRGBAMapIO::save( const ColorRGBAMap<float>& map, const std::string& filename )
{
	std::ofstream stream( filename );
	save( map, stream );
}


void ColorRGBAMapIO::save( const ColorRGBAMap<float>& map, std::ostream& stream )
{
	stream << map.getResolution() << std::endl;
	for( int i = 0; i < map.getResolution(); ++i ) {
		const ColorRGBA<float>& color = map.getColorFromIndex( i );
		stream << color.getRed() << " " << color.getGreen() << " " << color.getBlue() << " " << color.getAlpha() << std::endl;
	}
}

void ColorRGBAMapIO::load( ColorRGBAMap<float>& map, const std::string& filename )
{
	std::ifstream stream( filename );
	load( map, stream );
}

void ColorRGBAMapIO::load( ColorRGBAMap<float>& map, std::istream& stream )
{
	const int resolution = Helper::read<int>(stream);
	std::vector< ColorRGBA<float> > colors;
	for( int i = 0; i < resolution; ++i ) {
		colors.push_back( Helper::readColorRGBA(stream) );
	}
	map.setColors( colors );
}