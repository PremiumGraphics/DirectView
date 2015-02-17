#include "gtest/gtest.h"

#include "ColorRGBAMapIO.h"
#include <string>

using namespace Crystal::Graphics;
using namespace Crystal::IO;

std::stringstream getSample()
{
	std::stringstream stream;
	stream
		<< "2" << std::endl
		<< "0 0 0 0" << std::endl
		<< "1 0 1 0" << std::endl;
	return stream;
}

TEST( ColorRGBAMapIOTest, TestSave )
{
	std::vector< ColorRGBA<float> > colors;
	colors.push_back( ColorRGBA<float>( 0.0, 0.0, 0.0, 0.0 ) );
	colors.push_back( ColorRGBA<float>( 1.0, 0.0, 1.0, 0.0 ) );
	ColorRGBAMap<float> map( colors );
	std::ostringstream stream;
	ColorRGBAMapIO::save( map, stream );
	const std::string& str = stream.str();
	EXPECT_EQ( getSample().str(), str );
}

TEST( ColorRGBAMapIOTest, TestLoad )
{
	ColorRGBAMap<float> map;
	ColorRGBAMapIO::load( map, getSample() );
	EXPECT_EQ( 2, map.getResolution() );
	EXPECT_EQ( ColorRGBA<float>( 0.0, 0.0, 0.0, 0.0), map.getColorFromIndex(0) );
	EXPECT_EQ( ColorRGBA<float>( 1.0, 0.0, 1.0, 0.0), map.getColorFromIndex(1) );
}
