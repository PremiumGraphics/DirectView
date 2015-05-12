#ifndef __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__
#define __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__

#include "Box.h"
#include "Bitmap3d.h"
#include "Vector2d.h"

#include "Space2d.h"
#include "Space3d.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Math {

class BitmapConverter final : private UnCopyable
{
public:
	BitmapConverter() = default;

	~BitmapConverter() = default;
	/*
	template<size_t N>
	std::vector<Line> Bitmap3dConverter::toQuads(const Bitmap2d<N>& bmp)
	*/


	template<size_t N, size_t N2, size_t N3>
	std::vector<Math::Box> toBoxes(const Bitmap3d<N, N2, N3>& bmp, const Space3d& space) {
		const auto start = space.getStart();
		const auto sizex = space.getSizes().getX();
		const auto sizey = space.getSizes().getY();
		const auto sizez = space.getSizes().getZ();
		std::vector<Box> boxes;
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				for (size_t z = 0; z < bmp.sizez(); ++z) {
					if (bmp.get(x,y,z) ) {
						const Vector3d v1(x * sizex, y * sizey, z * sizez);
						const Vector3d v2((x + 1)*sizex, (y + 1)*sizey, (z + 1)*sizez);
						Box box(start + v1, start + v2);
						boxes.push_back(box);
					}
				}
			}
		}
		return boxes;
	}
	
};
	}
}

#endif