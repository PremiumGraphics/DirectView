#ifndef __CRYSTAL_MATH_SPACE_3D_H__
#define __CRYSTAL_MATH_SPACE_3D_H__

#include "../Math/Vector3d.h"
#include "../Math/Bitmap3d.h"
#include "../Math/Box.h"

namespace Crystal {
	namespace Math {

template<size_t N1, size_t N2, size_t N3>
class Space3d final
{
public:
	Space3d() : Space3d(Vector3d::Zero()){}

	explicit Space3d(const Vector3d& start ) :
		start( start ),
		sizes(Vector3d(1.0f, 1.0f, 1.0f))
	{}

	Vector3d getSizes() const { return sizes; }

	Vector3d getStart() const {
		return start;
	}

	Vector3d getEnd() const {
		const auto x = start.getX() + getResX() * sizes.getX();
		const auto y = start.getY() + getResY() * sizes.getY();
		const auto z = start.getZ() + getResZ() * sizes.getZ();
		return Vector3d(x, y, z);
	}

	unsigned int getResX() const { return N1; }

	unsigned int getResY() const { return N2; }

	unsigned int getResZ() const { return N3; }

	Box getBoundingBox() const {
		return Box(start, getEnd());
	}

	std::vector<int> getHashedIndex(const Vector3d& point) {
		const auto gridx = static_cast<int>(point.getX() / sizes.getX());
		const auto gridy = static_cast<int>(point.getY() / sizes.getY());
		const auto gridz = static_cast<int>(point.getZ() / sizes.getZ());
		return std::vector < int > {gridx, gridy, gridz};
	}

	std::vector<Math::Box> toBoxes(const Bitmap3d<N1, N2, N3>& bmp) {
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
};

	}
}

#endif