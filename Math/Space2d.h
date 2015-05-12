#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Quad.h"
#include "../Math/Vector2d.h"
#include "../Math/Bitmap2d.h"

namespace Crystal {
	namespace Math {

class Space2d final {
public:
	Space2d(const Vector2d<float>& start, unsigned int resx, unsigned int resy ) :
		start(start),
		resx(resx),
		resy(resy),
		sizes(Vector2d<float>(1.0f, 1.0f ))
	{}

	Space2d(unsigned int resx, unsigned int resy) : Space2d(Vector2d<float>::Zero(), resx, resy){}

	Vector2d<float> getSizes() const { return sizes; }

	Vector2d<float> getStart() const;

	Vector2d<float> getEnd() const;

	unsigned int getResX() const { return resx; }

	unsigned int getResY() const { return resy; }

	Quad getBoundingQuad() const;

	template<size_t N, size_t N2>
	std::vector<Quad> toQuads(const Bitmap2d<N, N2>& bmp ) {
		std::vector<Quad> quads;
		const auto sizex = sizes.getX();
		const auto sizey = sizes.getY();
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				if (bmp.get(x, y)) {
					const Vector2d<float> v1(x * sizex, y * sizey);
					const Vector2d<float> v2((x + 1) * sizex, (y + 1) * sizey);
					Quad q(v1, v2);
					quads.push_back(q);
				}
			}
		}
		return quads;
	}


private:

	Vector2d<float> start;
	Vector2d<float> sizes;
	unsigned int resx;
	unsigned int resy;
};

	}
}

#endif