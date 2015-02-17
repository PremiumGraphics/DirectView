#include <stdafx.h>

#include "Converter.h"

#include "../Graphics/ColorRGBA.h"
//#include "../Graphics/TextureObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::App;

wxColour Converter::toWxColor( const ColorRGBA<float>& c )
{
	return wxColour( c.getRed() * 255, c.getGreen() * 255, c.getBlue() * 255, c.getAlpha() * 255 );
}

ColorRGBA<float> Converter::toColor( const wxColour& c )
{
	return ColorRGBA<float>( c.Red() / 255.0f, c.Green() / 255.0f, c.Blue() / 255.0f, c.Alpha() / 255.0f );
}

std::vector< unsigned char > Converter::toArrayRGBA( const wxBitmap& bmp )
{
	std::vector< GLubyte > values;

	wxImage image = bmp.ConvertToImage();
	const int width = image.GetWidth();
	const int height = image.GetHeight();

	assert( image.GetWidth() == bmp.GetWidth() );
	assert( image.GetHeight() == bmp.GetHeight() );

	for( int y = 0; y < height; y++ ) {
		for( int x = 0; x < width; x++ ) {
			const unsigned char r = image.GetRed( x, y );
			values.push_back( r );
			const unsigned char g = image.GetGreen( x, y );
			values.push_back( g );
			const unsigned char b = image.GetBlue( x, y );
			values.push_back( b );
			const unsigned char a = 0;//image.GetAlpha( i, j );
			values.push_back( a );
		}
	}
	return values;
}

std::vector< unsigned char > Converter::toArrayRGBA( const wxImage& image )
{
	std::vector< GLubyte > values;

	const int width = image.GetWidth();
	const int height = image.GetHeight();

	for( int y = 0; y < height; y++ ) {
		for( int x = 0; x < width; x++ ) {
			const unsigned char r = image.GetRed( x, y );
			values.push_back( r );
			const unsigned char g = image.GetGreen( x, y );
			values.push_back( g );
			const unsigned char b = image.GetBlue( x, y );
			values.push_back( b );
			const unsigned char a = 0;//image.GetAlpha( i, j );
			values.push_back( a );
		}
	}
	return values;
}

