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

	size_t size() const { return N; }

	ColorRGBA<float> operator[](size_t i) const {
		return colors[i];
	}

private:
	std::array< ColorRGBA<float>, N > colors;
};


template< size_t N1, size_t N2 >
class Image2d final
{
public:
	Image2d() = default;

	size_t size() const { return N1 * N2; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	ColorRGBA<float> get(size_t i, size_t j) const {
		return colors[i][j];
	}

private:
	std::array< Image1d<N1>, N2 > colors;
};

	}
}

#endif