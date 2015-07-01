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

	T getLength() const { vector.getLength(); }

	/*
	Vector3dVector<T> toPositions(const T divideLength) const{
		Vector3dVector<T> positions;
		const auto dt = divideLength / getLength();
		for (auto x = 0; i < divideLength; ) {
			const auto p = divParam * i;
		}
	}
	*/

	Vector3dVector<T> toPositions(const unsigned int howMany) const {
		Vector3dVector<T> positions;
		const auto dt = T(1) / static_cast<T>(howMany);
		for (size_t i = 0; i < howMany; ++i) {
			const auto param = dt * i;
			positions.emplace_back(getPosition(param));
		}
		return std::move(positions);
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