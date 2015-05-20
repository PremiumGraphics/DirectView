#ifndef __CRYSTAL_MATH_MARCHING_2D_H__
#define __CRYSTAL_MATH_MARCHING_2D_H__

#include "Space2d.h"

namespace Crystal {
	namespace Math {

class Line2d {
public:
	Position2d<float> start;
	Position2d<float> end;
};

class Marching2d final
{
public:
	Marching2d()
	{
		buildTable();
	}

	void march(const Space2d<2, 2, float>& space) {
		const auto& bmp = space.getBitmap();
		if (bmp == table[0]) {
			;
		}
		/*if (bmp.get(0, 0)) {

		}*/
	}

	std::vector<Line2d> getLines() const { return lines;  }

	std::array< Bitmap2x2, 16 > getTables() const { return table; }

	void buildTable() {
		for (size_t i = 0; i < 16; ++i) {
			table[i] = Bitmap2x2(i);
		}
	}

private:
	std::vector<Line2d> lines;

	std::array< Bitmap2x2, 16 > table;
};
	}
}

#endif