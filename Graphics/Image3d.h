#ifndef __CRYSTAL_GRAPHICS_IMAGE_3D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_3D_H__

#include "../Math/Grid3d.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

template< size_t N1, size_t N2, size_t N3 >
using Image3d = Math::Grid3d < N1, N2, N3, ColorRGBA<float> > ;
/*
class Image3d final
{
public:
	Image3d() = default;

	~Image3d() = default;

	size_t size() const { return N1 * N2 * N3; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	size_t sizez() const { return N3; }

	ColorRGBA<float> get(size_t i, size_t j, size_t k) const {
		return colors[i][j][k];
	}

	void set(const size_t i, const size_t j, const size_t k, const ColorRGBA<float>& c) {
		colors[i][j].set(k, c);
	}

	Image2d<N1, N2>& operator[](size_t i) {
		return colors[i];
	}

	Image2d<N1, N2> operator[](size_t i) const {
		return colors[i];
	}

	bool equals(const Image3d<N1, N2, N3>& rhs) const {
		return colors == rhs.colors;
	}

	bool operator==(const Image3d<N1, N2, N3>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Image3d<N1, N2, N3>& rhs) const {
		return !equals(rhs);
	}


private:
	std::array< Image2d<N1, N2>, N3 > colors;
};
*/
	}
}

#endif