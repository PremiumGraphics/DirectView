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
			lines.push_back( Line2d<T>( Position2d<T>( 0.5f, 0.0f ), Position2d<T>( 0.0f, 0.5f ) ) );
		}
		else if (bmp == table[2]) {
			lines.push_back( Line2d<T>(Position2d<float>(0.0f, 0.5f), Position2d<T>(1.0f, 0.5f)));
		}
		/*if (bmp.get(0, 0)) {

		}*/
	}

	std::vector<Line2d<T> > getLines() const { return lines;  }

	std::array< Bitmap2x2, 16 > getTables() const { return table; }

	void buildTable() {
		for (size_t i = 0; i < 16; ++i) {
			table[i] = Bitmap2x2(i);
		}
	}

private:
	std::vector<Line2d<T> > lines;

	std::array< Bitmap2x2, 16 > table;
};
	}
}

#endif