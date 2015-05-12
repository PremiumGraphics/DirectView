#ifndef __CRYSTAL_MATH_SPACE_1D_H__
#define __CRYSTAL_MATH_SPACE_1D_H__

#include <vector>

#include "../Math/Bitmap1d.h"

namespace Crystal {
	namespace Math {

template< size_t N >
class Space1d final {
public:

	Space1d() :
		start(0.0f),
		length(1.0f)
	{}

	Space1d(const float start, const float length) :
		start(start),
		length(length),
	{}

	float getStart() const { return start; }

	float getEnd() const { return start + length; }

	float getLength() const { return length; }

	unsigned int getRes() const { return N; }

	float getResSize() const { return length / static_cast<float>(N); }

	std::vector< float > toPositions( const Bitmap1d<N>& bmp ) const {
		std::vector< float > positions;
		for (size_t i = 0; i < bmp.size(); ++i) {
			if (bmp[i]) {
				const auto pos = start + getResSize() * i + getResSize() * 0.5f;
				positions.push_back(pos);
			}
		}
		return positions;
	}

private:
	float start;
	float length;
};

	}
}

#endif