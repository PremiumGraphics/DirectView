#ifndef __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__
#define __CRYSTAL_MATH_BITMAP_3D_CONVERTER_H__

#include "Box.h"
#include "Bitmap3d.h"
#include "Vector2d.h"

namespace Crystal {
	namespace Math {

class BitmapConverter {
public:
	BitmapConverter() :
		size(1.0f)
	{}

	BitmapConverter(const float size) :
		size(size)
	{}

	/*
	template<size_t N>
	std::vector<Line> Bitmap3dConverter::toQuads(const Bitmap2d<N>& bmp)
	*/

	template<size_t N>
	std::vector<Quad> toQuads(const Bitmap2d<N>& bmp) {
		std::vector<Quad> quads;
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				if (bmp[x][y]) {
					const Vector2d<float> v1(x * size, y * size);
					const Vector2d<float> v2((x + 1) * size, (y + 1) * size);
					Quad q(v1, v2);
					quads.push_back(q);
				}
			}
		}
		return quads;
	}

	template<size_t N>
	std::vector<Math::Box> toBoxes(const Bitmap3d<N>& bmp) {
		std::vector<Box> boxes;
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				for (size_t z = 0; z < bmp.sizez(); ++z) {
					if (bmp[x][y][z]) {
						const Vector3d v1(x * size, y * size, z * size);
						const Vector3d v2((x + 1)*size, (y + 1)*size, (z + 1)*size);
						Box box(v1, v2);
						boxes.push_back(box);
					}
				}
			}
		}
		return boxes;
	}
	
private:
	const float size;
};
	}
}

#endif