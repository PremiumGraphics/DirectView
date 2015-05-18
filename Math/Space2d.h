#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Quad.h"
#include "../Math/Vector2d.h"
#include "../Math/Bitmap2d.h"

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2>
class Space2d final {
public:

	Space2d() : Space2d(Vector2d<float>::Zero()) {}

	explicit Space2d(const Vector2d<float>& start) : Space2d(start, Vector2d<float>(1.0f, 1.0f)) {}

	Space2d(const Vector2d<float>& start, const Vector2d<float>& sizes) :
		start(start),
		sizes(sizes)
	{}

	Position2d<float> getStart() const { return start; }

	Position2d<float> getEnd() const {
		const auto x = start.getX() + getResX() * sizes.getX();
		const auto y = start.getY() + getResY() * sizes.getY();
		return Position2d<float>(x, y);
	}

	Vector2d<float> getSizes() const { return sizes; }

	unsigned int getResX() const { return N1; }

	unsigned int getResY() const { return N2; }

	Space2d<N1, N2>& move(const Vector2d<float>& v) {
		start += v;
		return (*this);
	}

	Quad<float> getBoundingQuad() const {
		return Quad<float>(getStart(), getEnd());
	}

	std::vector<Quad<float> > toQuads(const Bitmap2d<N1, N2>& bmp ) {
		std::vector<Quad<float> > quads;
		const auto sizex = sizes.getX();
		const auto sizey = sizes.getY();
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				if (bmp.get(x, y)) {
					const Position2d<float> v1(x * sizex, y * sizey);
					const Position2d<float> v2((x + 1) * sizex, (y + 1) * sizey);
					Quad<float> q(v1, v2);
					quads.push_back(q);
				}
			}
		}
		return quads;
	}

	bool equals(const Space2d<N1, N2>& rhs) const {
		return
			(start == rhs.start) &&
			(sizes == rhs.sizes);
	}

	bool operator==(const Space2d<N1, N2>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Space2d<N1, N2>& rhs) const {
		return !equals(rhs);
	}

	bool hasIntersection(const Space2d<N1, N2>& rhs) const {
		const auto& q1 = this->getBoundingQuad();
		const auto& q2 = rhs.getBoundingQuad();
		return q1.hasIntersection( q2 );
	}

private:
	Position2d<float> start;
	Vector2d<float> sizes;
};

using Space1x1 = Space2d < 1, 1 >;
using Space2x1 = Space2d < 2, 1 >;
using Space2x2 = Space2d < 2, 2 >;
using Space2x4 = Space2d < 2, 4 >;
using Space4x2 = Space2d < 4, 2 >;

using Space128x128 = Space2d < 256, 256 >;
using Space256x256 = Space2d < 256, 256 >;
using Space512x512 = Space2d < 512, 512 >;
using Space1024x1024 = Space2d < 1024, 1024 >;

	}
}

#endif