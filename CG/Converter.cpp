#include <stdafx.h>

#include "Converter.h"

#include "../Graphics/ColorRGBA.h"
#include "../Graphics/ImageRGBA.h"

using namespace Crystal::Graphics;
using namespace Crystal::CGS;

wxColour Converter::toWxColor( const ColorRGB<float>& c )
{
	return wxColour( c.getRed() * 255, c.getGreen() * 255, c.getBlue() * 255, 255 );
}

wxColour Converter::toWxColor( const ColorRGBA<float>& c )
{
	return wxColour( c.getRed() * 255, c.getGreen() * 255, c.getBlue() * 255, c.getAlpha() * 255 );
}

ColorRGBA<float> Converter::toColorRGBA( const wxColour& c )
{
	return ColorRGBA<float>( c.Red() / 255.0f, c.Green() / 255.0f, c.Blue() / 255.0f, c.Alpha() / 255.0f );
}

ColorRGB<float> Converter::toColorRGB( const wxColour& c )
{
	return ColorRGB<float>( c.Red() / 255.0f, c.Green() / 255.0f, c.Blue() / 255.0f );
}

ImageRGBA<unsigned char> Converter::toImageRGBA( const wxImage& image )
{
	std::vector< ColorRGBA< unsigned char > > values;

	const int width = image.GetWidth();
	const int height = image.GetHeight();

	for( int y = 0; y < height; y++ ) {
		for( int x = 0; x < width; x++ ) {
			const unsigned char r = image.GetRed( x, y );
			const unsigned char g = image.GetGreen( x, y );
			const unsigned char b = image.GetBlue( x, y );
			const unsigned char a = 0;//image.GetAlpha( i, j );
			ColorRGBA< unsigned char > color( r, g, b, a );
			values.push_back( color );
		}
	}
	return ImageRGBA<unsigned char>( width, height, values );
}

wxImage Converter::toWxImage( const ImageRGBA<unsigned char>& image )
{
	std::vector< unsigned char > values;
	return wxImage( image.getWidth(), image.getHeight(), &( values.front() ) );
}