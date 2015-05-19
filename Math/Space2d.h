#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Quad.h"
#include "../Math/Vector2d.h"
#include "../Math/Bitmap2d.h"
#include "../Math/Space1d.h"

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2>
class Space2d final {
public:

	Space2d() : Space2d(Position2d<float>(0.0f, 0.0f))
	{}

	explicit Space2d(const Position2d<float>& start) : Space2d(start, Vector2d<float>(1.0f, 1.0f)) {}

	Space2d(const Position2d<float>& start, const Vector2d<float>& sizes) :
		quad(Quad<float>(start, sizes) )
	{}

	Space2d(const Quad<float>& quad) :
		quad(quad)
	{}

	Space2d(const Quad<float>& quad, const Bitmap2d<N1,N2>& bmp) :
		quad(quad),
		bmp( bmp )
	{}


	Position2d<float> getStart() const { return quad.getStart(); }

	Position2d<float> getCenter() const { return quad.getCenter(); }

	Position2d<float> getEnd() const { return quad.getEnd(); }

	Vector2d<float> getSizes() const { return quad.getLength(); }

	unsigned int getResX() const { return N1; }

	unsigned int getResY() const { return N2; }

	/*
	Space2d<N1, N2>& move(const Vector2d<float>& v) {
		start += v;
		return (*this);
	}
	*/

	Quad<float> getBoundingQuad() const {
		return quad;
	}

	std::vector<Quad<float> > toQuads() {
		std::vector<Quad<float> > quads;
		const auto sizex = getSizes().getX();
		const auto sizey = getSizes().getY();
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

	/*
	Space1d<float> toSpace1ds() const {
		Space1d<float> space1ds;
		for ( size_t i )
	}
	*/

	Position2dVector<float> toBoundaryPositions() const {
		Position2dVector<float> positions;
		for (size_t i = 1; i < bmp.sizex(); ++i) {
			for (size_t j = 1; j < bmp.sizey(); ++j) {
				if (bmp.get(i - 1,j) != bmp.get(i,j) ) {
					const auto posx = getStart().getX() + getSizes().getX() * i;
					const auto posy = getStart().getY() + getSizes().getY() * j;
					positions.push_back( Position2d<float>(posx, posy ) );
				}
				if (bmp.get(i,j - 1) != bmp.get(i,j)) {
					const auto posx = getStart().getX() + getSizes().getX() * i;
					const auto posy = getStart().getY() + getSizes().getY() * j;
					positions.push_back(Position2d<float>(posx, posy));
				}
			}
		}
		return positions;
	}

	bool equals(const Space2d<N1, N2>& rhs) const {
		return
			(getBoundingQuad() == rhs.getBoundingQuad()) &&
			(bmp == rhs.bmp );
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
	Quad<float> quad;
	Bitmap2d<N1, N2> bmp;
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