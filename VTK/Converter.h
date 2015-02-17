#ifndef __CRYSTAL_APP_CONVERTER_H__
#define __CRYSTAL_APP_CONVERTER_H__

#include <vector>

#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Graphics {
		class TextureObject;
	}
	namespace App {

class Converter {
public:
	static wxColour toWxColor(const Graphics::ColorRGBA<float>& original);

	static Graphics::ColorRGBA<float> toColor( const wxColour& color );

	static std::vector< unsigned char > toArrayRGBA( const wxBitmap& bmp );

	static std::vector< unsigned char > toArrayRGBA( const wxImage& image );
};

	}
}

#endif