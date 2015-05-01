#ifndef __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__
#define __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__

#include "Box.h"
#include "Bitmap3d.h"

namespace Crystal {
	namespace Math {

class Bitmap3dConverter {
public:
	Bitmap3dConverter() :
		size(1.0f)
	{}

	Bitmap3dConverter(const float size) :
		size(size)
	{}

	template<size_t N>
	std::vector<Math::Box> toBoxes(const Bitmap3d<N>& bmp);
	
private:
	const float size;
};
	}
}

#endif