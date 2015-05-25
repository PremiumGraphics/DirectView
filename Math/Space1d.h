#ifndef __CRYSTAL_MATH_SPACE_1D_H__
#define __CRYSTAL_MATH_SPACE_1D_H__

#include <vector>

#include "Bitmap1d.h"
#include "Line1d.h"
#include "Position1d.h"

namespace Crystal {
	namespace Math {

template< size_t N, typename T >
class Space1d final {
public:
	Space1d() :
		start({ 0 }),
		length(1.0f)
	{}

	Space1d(const Bitmap1d<N>& bmp) :
		start({ 0 }),
		length(1.0f),
		bmp( bmp )
	{}


	Space1d(const Position1d<T>& start, const T length) :
		start(start),
		length(length)
	{}

	Space1d(const Position1d<T>& start, const T length, const Bitmap1d<N>& bmp) :
		start(start),
		length(length),
		bmp(bmp)
	{}

	Space1d<N, T>& setBmp(const Bitmap1d<N>& bmp) {
		this->bmp = bmp;
		return *(this);
	}

	Position1d<T> getStart() const { return start; }

	T getEnd() const { return start.getX() + length; }

	T getLength() const { return length; }

	T getTotalLength() const { return length * bmp.count(); }

	unsigned int getRes() const { return N; }

	T getSize() const { return length / static_cast<T>(N); }

	Position1dVector<T> toPositions() const {
		Position1dVector<T> positions;
		for (size_t i = 0; i < bmp.size(); ++i) {
			if (bmp[i]) {
				const Position1d<T> pos({ getStart().getX() + getSize() * i + getSize() * 0.5f });
				positions.push_back(pos);
			}
		}
		return positions;
	}

	Position1dVector<T> toBoundaryPositions() const {
		Position1dVector<T> positions;
		for (size_t i = 1; i < bmp.size(); ++i) {
			if ( bmp[i-1] != bmp[i]) {
				const Position1d<T> pos({ getStart().getX() + getSize() * i });
				positions.push_back(pos);
			}
		}
		return positions;
	}

	Line1d<T> getBoundingLine() const {
		return Line1d<T>(getStart(), getLength());
	}

	bool hasIntersection(const Space1d<N,T>& rhs) {
		const auto& line1 = getBoundingLine();
		const auto& line2 = rhs.getBoundingLine();
		return line1.hasInersection(line2);
	}

	/*
	unsigned float getDiff( const Space1d& rhs) const {
		return start.get() - rhs.getStart();
	}
	*/

private:
	Position1d<T> start;
	T length;
	Bitmap1d<N> bmp;
};

	}
}

#endif