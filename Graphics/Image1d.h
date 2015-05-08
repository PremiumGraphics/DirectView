#ifndef __CRYSTAL_GRAPHICS_IMAGE_1D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_1D_H__

#include <array>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

template< size_t N >
class Image1d final
{
public:
	Image1d() = default;

	Image1d(const ColorRGBA<float>& c) {
		colors.fill(c);
	}

	~Image1d() = default;

	size_t size() const { return N; }

	ColorRGBA<float> operator[](size_t i) const {
		return colors[i];
	}

	ColorRGBA<float>& operator[](size_t i) {
		return colors[i];
	}

	ColorRGBA<float> get(const size_t i) {
		return colors[i];
	}

	void set(const size_t i, const ColorRGBA<float>& c) {
		colors[i] = c;
	}

	bool equals( const Image1d<N>& rhs) const {
		return colors == rhs.colors;
	}

	bool operator==(const Image1d<N>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Image1d<N>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< ColorRGBA<float>, N > colors;
};

	}
}

#endif