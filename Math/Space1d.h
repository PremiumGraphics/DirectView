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

	Space1d(const Bitmap1d<N>& bmp) :
		start(0.0f),
		length(1.0f),
		bmp( bmp )
	{}


	Space1d(const float start, const float length) :
		start(start),
		length(length)
	{}

	Space1d(const float start, const float length, const Bitmap1d<N>& bmp) :
		start(start),
		length(length),
		bmp(bmp)
	{}

	Space1d<N>& setBmp(const Bitmap1d<N>& bmp) {
		this->bmp = bmp;
		return *(this);
	}

	float getStart() const { return start; }

	float getEnd() const { return start + length; }

	float getLength() const { return length; }

	unsigned int getRes() const { return N; }

	float getSize() const { return length / static_cast<float>(N); }

	std::vector< float > toPositions() const {
		std::vector< float > positions;
		for (size_t i = 0; i < bmp.size(); ++i) {
			if (bmp[i]) {
				const auto pos = start + getSize() * i + getSize() * 0.5f;
				positions.push_back(pos);
			}
		}
		return positions;
	}

private:
	float start;
	float length;
	Bitmap1d<N> bmp;
};

	}
}

#endif