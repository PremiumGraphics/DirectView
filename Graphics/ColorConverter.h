#ifndef __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__
#define __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__

#include "ColorHSV.h"
#include "ColorRGB.h"

namespace Crystal {
	namespace Graphics {

class ColorConverter {
public:
	static ColorRGB<float> toRGB(const ColorHSV& hsv );

	static ColorHSV toHSV(const ColorRGB<float>& rgb );
};
	}
}

#endif