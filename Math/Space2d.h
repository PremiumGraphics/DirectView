#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Quad.h"
#include "../Math/Vector.h"
#include "../Math/Bitmap2d.h"
#include "../Math/Space1d.h"

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2, typename T>
class Space2d final {
public:

	Space2d() {}

	explicit Space2d(const Quad<T>& quad) :
		quad(quad)
	{}

	Space2d(const Quad<T>& quad, const Bitmap2d<N1,N2>& bmp) :
		quad(quad),
		bmp( bmp )
	{}


	Position2d<T> getStart() const { return quad.getStart(); }

	Position2d<T> getCenter() const { return quad.getCenter(); }

	Position2d<T> getEnd() const { return quad.getEnd(); }

	Vector2d<T> getSizes() const { return quad.getLength(); }

	unsigned int getResX() const { return N1; }

	unsigned int getResY() const { return N2; }

	/*
	Space2d<N1, N2>& move(const Vector2d<float>& v) {
		start += v;
		return (*this);
	}
	*/

	Quad<T> getBoundingQuad() const {
		return quad;
	}

	Bitmap2d<N1, N2> getBitmap() const {
		return bmp;
	}

	std::vector<Quad<T> > toDividedQuads() {
		std::vector<Quad<T> > quads;
		const auto sizex = getSizes().get<0>();
		const auto sizey = getSizes().get_(1);
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				if (bmp.get(x, y)) {
					const Position2d<T> v1({ x * sizex, y * sizey });
					const Position2d<T> v2({ (x + 1) * sizex, (y + 1) * sizey });
					Quad<T> q(v1, v2);
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

	Position2dVector<T> toBoundaryPositions() const {
		Position2dVector<T> positions;
		for (size_t i = 1; i < bmp.sizex(); ++i) {
			for (size_t j = 1; j < bmp.sizey(); ++j) {
				if (bmp.get(i - 1,j) != bmp.get(i,j) ) {
					const auto posx = getStart().get<0>() + getSizes().get<0>() * i;
					const auto posy = getStart().get<1>() + getSizes().get<1>() * j;
					positions.push_back(Position2d<T>({ posx, posy }));
				}
				if (bmp.get(i,j - 1) != bmp.get(i,j)) {
					const auto posx = getStart().get<0>() + getSizes().get<0>() * i;
					const auto posy = getStart().get<1>() + getSizes().get<1>() * j;
					positions.push_back(Position2d<T>({ posx, posy }));
				}
			}
		}
		return positions;
	}

	bool equals(const Space2d<N1, N2, T>& rhs) const {
		return
			(getBoundingQuad() == rhs.getBoundingQuad()) &&
			(bmp == rhs.bmp );
	}

	bool operator==(const Space2d<N1, N2, T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Space2d<N1, N2, T>& rhs) const {
		return !equals(rhs);
	}

	bool hasIntersection(const Space2d<N1, N2, T>& rhs) const {
		const auto& q1 = this->getBoundingQuad();
		const auto& q2 = rhs.getBoundingQuad();
		return q1.hasIntersection( q2 );
	}

private:
	Quad<T> quad;
	Bitmap2d<N1, N2> bmp;
};

template<typename T>
using Space1x1 = Space2d < 1, 1, T >;
template<typename T>
using Space2x1 = Space2d < 2, 1, T >;
template<typename T>
using Space2x2 = Space2d < 2, 2, T >;
template<typename T>
using Space2x4 = Space2d < 2, 4, T >;
template<typename T>
using Space4x2 = Space2d < 4, 2, T >;

/*
using Space128x128 = Space2d < 256, 256, float >;
using Space256x256 = Space2d < 256, 256, float >;
using Space512x512 = Space2d < 512, 512, float >;
using Space1024x1024 = Space2d < 1024, 1024, float >;
*/
	}
}

#endif