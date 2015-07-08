#ifndef __CRYSTAL_MATH_LINE_H__
#define __CRYSTAL_MATH_LINE_H__

#include "Vector.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d final
{
public:
	Line3d(const Vector3d<T>& start, const Vector3d<T>& end) :
		start( start ),
		vector( end - start )
	{
	}

	Vector3d<T> getStart() const { return start; }

	Vector3d<T> getCenter() const { return start + vector * T(0.5); }

	Vector3d<T> getEnd() const { return start + vector; }

	Vector3d<T> getPosition(const T param) const { return start + vector * param; }

	T getLength() const { return vector.getLength(); }

	Vector3dVector<T> toPositionsByLength(const T divideLength) const{
		Vector3dVector<T> positions;
		const unsigned int howMany = getLength() / divideLength;
		return toPositionsByNumber(howMany);
	}

	Vector3dVector<T> toPositionsByNumber(const unsigned int howMany) const {
		Vector3dVector<T> positions;
		const auto dt = T(1) / static_cast<T>(howMany);
		for (size_t i = 0; i < howMany; ++i) {
			const auto param = dt * i;
			positions.emplace_back(getPosition(param));
		}
		return std::move(positions);
	}

	bool equals(const Line3d<T>& rhs) const {
		return
			this->start == rhs.start &&
			this->vector == rhs.vector;
	}

	bool operator==(const Line3d<T>& rhs) const {
		return equals(rhs);
	}

	bool operator!=(const Line3d<T>& rhs) const {
		return !equals(rhs);
	}

private:
	Vector3d<T> start;
	Vector3d<T> vector;
};

template<typename T>
using Line3dVector = std::vector < Line3d<T> > ;
	}
}

#endif