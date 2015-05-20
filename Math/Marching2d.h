#ifndef __CRYSTAL_MATH_MARCHING_2D_H__
#define __CRYSTAL_MATH_MARCHING_2D_H__

#include "Space2d.h"
#include "Line2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Marching2d final
{
public:
	Marching2d()
	{
		buildTable();
	}

	void march(const Space2d<2, 2, T>& space) {
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

	std::vector<Line2d<T> > getLines() const { return lines;  }

	std::array< Bitmap2x2, 16 > getTables() const { return table; }

	std::array< std::vector< Line2d<T> >, 16 > getLineTable() const { return lineTable; }

	void buildTable() {
		for (size_t i = 0; i < 16; ++i) {
			table[i] = Bitmap2x2(i);
		}

		const Position2d<T> left(0.0, 0.5f);
		const Position2d<T> right(1.0f, 0.5f);

		const Position2d<T> bottom(0.5, 0.0f);
		const Position2d<T> top(0.5, 1.0f);

		/*
		std::array <
			std::array < Position2d<T>, 2 >,
			2 >
		> positions;
		positions[0][0] = xminus;
		positions[1][0] = x;
		*/

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

private:
	std::vector<Line2d<T> > lines;

	std::array< Bitmap2x2, 16 > table;

	std::array< std::vector< Line2d<T> >, 16 > lineTable;
};
	}
}

#endif