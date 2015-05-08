#ifndef __CRYSTAL_GRAPHICS_IMAGE_2D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_2D_H__

namespace Crystal {
	namespace Graphics {

template< size_t N1, size_t N2 >
class Image2d final
{
public:
	Image2d() = default;

	~Image2d() = default;

	size_t size() const { return N1 * N2; }

	size_t sizex() const { return N1; }

	size_t sizey() const { return N2; }

	ColorRGBA<float> get(size_t i, size_t j) const {
		return colors[i][j];
	}

	ColorRGBA<float> get(size_t i) const {
		return colors[i];
	}

	void set(const size_t i, const size_t j, const ColorRGBA<float>& c) {
		colors[i].set(j, c);
	}

	void set(const size_t i, const Image1d<N1>& image1d) {
		colors[i] = image1d;
	}

	Image1d<N1> operator[](size_t i) const {
		return colors[i];
	}

	Image1d<N1>& operator[](const size_t i) {
		return colors[i];
	}

	bool equals(const Image2d<N1, N2>& rhs) const {
		return colors == rhs.colors;
	}


	bool operator==(const Image2d<N1, N2>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Image2d<N1, N2>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< Image1d<N1>, N2 > colors;
};


	}
}

#endif