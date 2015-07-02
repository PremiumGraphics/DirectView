#ifndef __CRYSTAL_GRAPHICS_SCREEN_COORD_H__
#define __CRYSTAL_GRAPHICS_SCREEN_COORD_H__

namespace Crystal {
	namespace Graphics {

class ScreenCoord
{
public:
	ScreenCoord() :
		x(0), y(0)
	{}

	ScreenCoord(int x, int y) :
		x(x), y(y)
	{}


	~ScreenCoord() = default;


public:
	int x;
	int y;
};
	}
}

#endif