#ifndef __CRYSTAL_MATH_MARCHING_3D_H__
#define __CRYSTAL_MATH_MARCHING_3D_H__

#include "Space3d.h"
#include "Triangle.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Marching3d final
{
public:
	Marching3d()
	{
		buildTable();
	}

	void march(const Space3d<2, 2, 2, T>& space) {
		const auto& bmp = space.getBitmap();
		if (bmp == table[0]) {
		}
		else if (bmp == table[1]) {
		}
		else if (bmp == table[2]) {
		}
		/*if (bmp.get(0, 0)) {

		}*/
	}

	std::array< Bitmap2x2x2, 16 > getTables() const { return table; }

	//std::array< std::vector< Line2d<T> >, 16 > getLineTable() const { return lineTable; }

	/*
	void buildTable() {
		for (size_t i = 0; i < 16; ++i) {
			table[i] = Bitmap2x2x2(i);
		}

		const Position2d<T> left(0.0, 0.5f);
		const Position2d<T> right(1.0f, 0.5f);

		const Position2d<T> bottom(0.5, 0.0f);
		const Position2d<T> top(0.5, 1.0f);

		lineTable[0] = {};
		lineTable[1] = { Line2d<T>(left, bottom) };
		lineTable[2] = { Line2d<T>(bottom, right) };
		lineTable[3] = { Line2d<T>(left, right) };
		lineTable[4] = { Line2d<T>(top, right) };
		lineTable[5] = { Line2d<T>(left, top), Line2d<T>(bottom, right) };
		lineTable[6] = { Line2d<T>(bottom, top) };
		lineTable[7] = { Line2d<T>(left, top) };
		lineTable[8] = lineTable[7];
		lineTable[9] = lineTable[6];
		lineTable[10] = { Line2d<T>(left, bottom), Line2d<T>(top, right) };
		lineTable[11] = lineTable[4];
		lineTable[12] = lineTable[3];
		lineTable[13] = lineTable[2];
		lineTable[14] = lineTable[1];
		lineTable[15] = lineTable[0];
	}
	*/

private:
	//std::vector<Line2d<T> > lines;

	std::array< Bitmap2x2, 16 > table;

	std::array< std::vector< Triangle<T> >, 16 > triTable;
};
	}
}

#endif