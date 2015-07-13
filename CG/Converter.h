#ifndef __CRYSTAL_UI_CONVERTER_H__
#define __CRYSTAL_UI_CONVERTER_H__

#include "../Graphics/ColorRGB.h"
#include "../Graphics/ColorRGBA.h"
#include "../Graphics/ImageRGBA.h"

namespace Crystal {
	namespace UI {

class Converter {
public:

	static wxColour Converter::toWxColor( const Graphics::ColorRGB<float>& c );

	static wxColour toWxColor( const Graphics::ColorRGBA<float>& original );

	static Graphics::ColorRGBA<float> toColorRGBA( const wxColour& color );

	static Graphics::ColorRGB<float> toColorRGB( const wxColour& color );

	static Graphics::ImageRGBA<unsigned char> toImageRGBA( const wxImage& image );

	static wxImage toWxImage( const Graphics::ImageRGBA<unsigned char>& image );

	static std::string toStdString(const wxString& src);
};

	}
}

#endif