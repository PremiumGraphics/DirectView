#ifndef __CRYSTAL_MATH_SPACE_1D_H__
#define __CRYSTAL_MATH_SPACE_1D_H__

#include <vector>

#include "Bitmap1d.h"
#include "Line.h"
#include "Vector.h"
#include "Position.h"

namespace Crystal {
	namespace Math {

template< size_t N, typename T >
class Space1d final {
public:
	Space1d() :
		origin({ 0 }),
		vector({ 1 } )
	{}

	Space1d(const Bitmap1d<N>& bmp) :
		origin({ 0 }),
		vector({ 1 }),
		bmp( bmp )
	{}


	Space1d(const Position1d<T>& start, const Vector<T,1>& length) :
		origin(start),
		vector(length)
	{}

	Space1d(const Position1d<T>& start, const T length, const Bitmap1d<N>& bmp) :
		origin(start),
		vector(length),
		bmp(bmp)
	{}

	Space1d<N, T>& setBmp(const Bitmap1d<N>& bmp) {
		this->bmp = bmp;
		return *(this);
	}

	Position1d<T> getStart() const { return origin; }

	T getEnd() const { return origin.get(0) + vector.get(0); }

	Vector<T,1> getLength() const { return vector; }

	T getTotalLength() const { return vector.get(0) * bmp.count(); }

	unsigned int getRes() const { return N; }

	T getSize() const { return vector.get(0) / static_cast<T>(N); }

	Position1dVector<T> toPositions() const {
		Position1dVector<T> positions;
		for (size_t i = 0; i < bmp.size(); ++i) {
			if (bmp[i]) {
				const Position1d<T> pos({ getStart().get(0) + getSize() * i + getSize() * 0.5f });
				positions.push_back(pos);
			}
		}
		return positions;
	}

	Position1dVector<T> toBoundaryPositions() const {
		Position1dVector<T> positions;
		for (size_t i = 1; i < bmp.size(); ++i) {
			if ( bmp[i-1] != bmp[i]) {
				const Position1d<T> pos({ getStart().get(0) + getSize() * i });
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
	Position1d<T> origin;
	Vector<T,1> vector;
	Bitmap1d<N> bmp;
};

	}
}

#endif