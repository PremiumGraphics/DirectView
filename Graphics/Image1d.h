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

	bool equals(const Image2d<N1,N2>& rhs) const {
		return colors == rhs.colors;
	}


	bool operator==(const Image2d<N1,N2>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Image2d<N1,N2>& rhs) const {
		return !equals(rhs);
	}

private:
	std::array< Image1d<N1>, N2 > colors;
};


template< size_t N1, size_t N2, size_t N3 >
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

	Image2d<N1,N2>& operator[](size_t i) {
		return colors[i];
	}

	Image2d<N1,N2> operator[](size_t i) const {
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
	std::array< Image2d<N1,N2>, N3 > colors;
};

	}
}

#endif