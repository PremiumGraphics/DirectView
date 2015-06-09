#ifndef __CRSYTAL_COMMAND_GRID_CONFIG_H__
#define __CRSYTAL_COMMAND_GRID_CONFIG_H__

#include "../Math/Space.h"

namespace Crystal {
	namespace Command {

struct GridConfig{
public:
	enum LIMIT{
		MINX = 8,
		MINY = 8,
		MINZ = 8,
		MAXX = 255,
		MAXY = 255,
		MAXZ = 255,
	};

	GridConfig() :
		resx(20),
		resy(20),
		resz(20),
		space(Math::Space3d<float>::Unit())
	{}

	GridConfig(const unsigned int x, const unsigned int y, const unsigned int z, const Math::Space3d<float>& space) :
		resx(x),
		resy(y),
		resz(z),
		space( space )
	{
	}

	unsigned int getResx() const { return resx; }

	unsigned int getResy() const { return resy; }

	unsigned int getResz() const { return resz; }

	Math::Space3d<float> getSpace() const { return space; }

	//unsigned int getMaxLimitX() const { return MAXX; }


private:
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	Math::Space3d<float> space;

};

	}
}

#endif