#ifndef __CRYSTAL_MATH_EDGE_DETECTION_ALGO_H__
#define __CRYSTAL_MATH_EDGE_DETECTION_ALGO_H__

#include "Bitmap1d.h"
#include "Bitmap2d.h"

namespace Crystal {
	namespace Math {

class EdgeDetectionAlgo {
public:

	template< size_t N1, size_t N2 >
	Bitmap2d<N1, N2> detect(const Bitmap2d<N1, N2>& bmp) {
		Bitmap2d<N1, N2 > dest;
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 1; y < bmp.sizey(); ++y){
				if (!bmp[x][y-1] && bmp[x][y]) {
					dest.set(x,y);
				}
			}
		}
		return dest;

	}

};
	}
}

#endif