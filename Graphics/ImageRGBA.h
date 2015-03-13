#ifndef __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__
#define __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__

#include <vector>
#include <cassert>

#include <memory>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

template< typename T >
class ImageRGBA {
public:
	ImageRGBA() :
		width( 0 ),
		height( 0 )
	{}

	ImageRGBA( const int width, const int height ) :
		width( width ),
		height( height ),
		values( width * height )
	{}

	ImageRGBA( const int width, const int height, const std::vector< Graphics::ColorRGBA< T > >& values ) :
		width( width ),
		height( height ),
		values( values )
	{
		assert( isValid() );
	}

	//Image( const int width, const int height, const std::vector< ColorRGBA >& values );

	/*
	Image::Image( const int width, const int height, const std::vector< ColorRGBA >& colors ) :
		width( width ),
		height( height )
	{
		for( const ColorRGBA& c : colors ) {
			const std::vector< unsigned char >& v = c.toArray4();
			values.insert( values.end(), v.begin(), v.end() );
		}
	}
	*/

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	//std::vector< T > getValues() const { return values; }

	bool isValid() const {
		return ( ( width * height ) == values.size() );
	}

	void setColor( const int i, const int j, const ColorRGBA<T>& c ) { values[ i*width+j ] = c; }

	ColorRGBA<T> getColor(const int i, const int j) const { return values[ i*width+j] ;}

	std::vector< T > getReds() const {
		std::vector< T > reds;
		for( ColorRGBA<T> v : values ) {
			reds.push_back( v.getRed() );
		}
		return reds;
	}

	std::vector< T > getGreens() const {
		std::vector< T > greens;
		for( ColorRGBA<T> v : values ) {
			greens.push_back( v.getGreen() );
		}
		return greens;
	}

	std::vector< T > getBlues() const {
		std::vector< T > blues;
		for( ColorRGBA<T> v : values ) {
			blues.push_back( v.getBlue() );
		}
		return blues;
	}

	std::vector< T > getAlphas() const {
		std::vector< T > alphas;
		for( ColorRGBA<T> v : values ) {
			alphas.push_back( v.getAlpha() );
		}
		return alphas;
	}


private:
	const int width;
	const int height;
	std::vector< ColorRGBA< T > > values;
};


typedef std::shared_ptr< ImageRGBA<float> > ImageRGBASPtr;


	}
}

#endif