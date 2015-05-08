#ifndef __CRYSTAL_GRAPHICS_IMAGE_2D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_2D_H__

#include "Image1d.h"

namespace Crystal {
	namespace Graphics {

template< size_t N1, size_t N2, class T = ColorRGBA<float> >
class Image2d final
{
public:
	Image2d() = default;

	~Image2d() = default;

	size_t size() const { return N1 * N2; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	T get(size_t i, size_t j) const {
		return colors[i][j];
	}

	Image1d<N1,T> get(size_t i) const {
		return colors[i];
	}

	void set(const size_t i, const size_t j, const T& c) {
		colors[i].set(j, c);
	}

	void set(const size_t i, const Image1d<N1,T>& image1d) {
		colors[i] = image1d;
	}

	Image1d<N1,T> operator[](size_t i) const {
		return colors[i];
	}

	Image1d<N1,T>& operator[](const size_t i) {
		return colors[i];
	}

	bool equals(const Image2d<N1, N2, T>& rhs) const {
		return colors == rhs.colors;
	}

	bool operator==(const Image2d<N1, N2, T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Image2d<N1, N2, T>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< Image1d<N1,T>, N2 > colors;
};


	}
}

#endif