#ifndef __CRSYTAL_COMMAND_GRID_CONFIG_H__
#define __CRSYTAL_COMMAND_GRID_CONFIG_H__

namespace Crystal {
	namespace Command {

struct GridConfig{
	GridConfig(const unsigned int x, const unsigned int y, const unsigned int z) :
		resx(x),
		resy(y),
		resz(z)
	{
	}
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
};

	}
}

#endif