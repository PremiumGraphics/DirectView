#ifndef __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__
#define __CRYSTAL_GRAPHICS_COLOR_CONVERTER_H__

#include <algorithm>


#include "ColorHSV.h"
#include "ColorRGB.h"

namespace Crystal {
	namespace Graphics {

class ColorConverter {
public:
	static ColorRGB<float> toRGB(const ColorHSV<float>& hsv) {
		const float h = hsv.getH();
		const float s = hsv.getS();
		const float v = hsv.getV();

		const float max = v;
		const float min = max - (s / 1.0f) * max;

		if (0 <= h && h <= 60) {
			const float g = h / 60.0f * (max - min) + min;
			return ColorRGB<float>(max, g, min);
		}
		else if (h <= 120.0f) {
			const float r = (120.0f - h) / 60.0f * (max - min) + min;
			return ColorRGB<float>(r, max, min);
		}
		else if (h <= 180.0f) {
			const float b = (h - 120.0f) / 60.0f * (max - min) + min;
			return ColorRGB<float>(min, max, b);
		}
		else if (h <= 240.0f) {
			const float g = (240.0f - h) / 60.0f * (max - min) + min;
			return ColorRGB<float>(min, g, max);
		}
		else if (h <= 300.0f) {
			const float r = (h - 240.0f) / 60.0f * (max - min) + min;
			return ColorRGB<float>(r, min, max);
		}
		else if (h <= 360.0f) {
			const float b = (360.0f - h) / 60.0f * (max - min) + min;
			return ColorRGB<float>(max, min, b);
		}
		else {
			assert(false);
			return ColorRGB<float>::Black();
		}
	}

	static ColorHSV<float> toHSV(const ColorRGB<float>& rgb) {
		const float r = rgb.getRed();
		const float g = rgb.getGreen();
		const float b = rgb.getBlue();

		const float min = std::min<float>(r, std::min<float>(g, b));
		const float max = std::max<float>(r, std::max<float>(g, b));

		const float v = max;
		const float s = max - min;

		if (min == max) {
			const float h = 0.0;
			return ColorHSV<float>(h, s, v);
		}
		else if (min == b) {
			const float h = 60.0f * (g - r) / (max - min) + 60.0f;
			return ColorHSV<float>(h, s, v);
		}
		else if (min == r) {
			const float h = 60.0f * (b - g) / (max - min) + 180.0f;
			return ColorHSV<float>(h, s, v);
		}
		else if (min == g) {
			const float h = 60.0f * (r - b) / (max - min) + 300.0f;
			return ColorHSV<float>(h, s, v);
		}
		else {
			assert(false);
			return ColorHSV<float>();
		}

	}
};
	}
}

#endif