#ifndef __CRYSTAL_MATH_SPACE_3D_H__
#define __CRYSTAL_MATH_SPACE_3D_H__

#include "../Math/Vector3d.h"
#include "../Math/Bitmap3d.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Math {

class Space3d final
{
public:
	Space3d(const Vector3d& start, unsigned int resx, unsigned int resy, unsigned int resz ) :
		start( start ),
		resx( resx ),
		resy( resy ),
		resz( resz ),
		sizes(Vector3d(1.0f, 1.0f, 1.0f))
	{}

	Space3d(unsigned int resx, unsigned int resy, unsigned int resz) : Space3d(Vector3d::Zero(), resx, resy, resz){}

	Vector3d getSizes() const { return sizes; }

	Vector3d getStart() const;

	Vector3d getEnd() const;

	unsigned int getResX() const { return resx; }

	unsigned int getResY() const { return resy; }

	unsigned int getResZ() const { return resz; }

	Box getBoundingBox() const;

	std::vector<int> getHashedIndex(const Vector3d& point) {
		const auto gridx = static_cast<int>(point.getX() / sizes.getX());
		const auto gridy = static_cast<int>(point.getY() / sizes.getY());
		const auto gridz = static_cast<int>(point.getZ() / sizes.getZ());
		return std::vector < int > {gridx, gridy, gridz};
	}

	template<size_t N, size_t N2, size_t N3>
	std::vector<Math::Box> toBoxes(const Bitmap3d<N, N2, N3>& bmp) {
		const auto start = getStart();
		const auto sizex = getSizes().getX();
		const auto sizey = getSizes().getY();
		const auto sizez = getSizes().getZ();
		std::vector<Box> boxes;
		for (size_t x = 0; x < bmp.sizex(); ++x) {
			for (size_t y = 0; y < bmp.sizey(); ++y) {
				for (size_t z = 0; z < bmp.sizez(); ++z) {
					if (bmp.get(x, y, z)) {
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


private:
	Vector3dVector positions;
	
	Vector3d start;
	Vector3d sizes;
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
};

	}
}

#endif