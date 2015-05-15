#ifndef __CRYSTAL_MATH_SPACE_BOOLEAN_ALGO_H__
#define __CRYSTAL_MATH_SPACE_BOOLEAN_ALGO_H__

#include "Space1d.h"
#include "Space3d.h"

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2, size_t N3>
class SpaceBooleanAlgo final
{
public:
	SpaceBooleanAlgo() = default;

	~SpaceBooleanAlgo() = default;

	bool isValidPair(const Space1d<N1>& lhs, const Space1d<N1>& rhs) const
	{
		return (lhs.getRes() == rhs.getRes()); //&&
			//lhs.get
			//;
	}

	/*
	bool isValidPair(const Space3d<N1, N2, N3>& lhs, const Space3d<N1, N2, N3>& rhs) const
	{
		return
			(lhs.getSizes() == rhs.getSizes());
//			(lhs.getBoundingBox().)
			;
	}

	Space3d<N1,N2,N3> createUnion(const Space3d<N1, N2, N3>& lhs, const Space3d<N1, N2, N3>& rhs) {
		if ( !isValidPair() ) {
			return Space3d<N1, N2, N3>();
		}
		const auto diff = lhs.getStart() - rhs.getStart();
		const auto diffx = diff.getX() * lhs.getResX();
		const auto diffy = diff.getY() + lhs.getResX();
	}
	*/
};

	}
}

#endif