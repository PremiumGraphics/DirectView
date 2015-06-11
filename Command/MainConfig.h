#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include <tuple>

#include "../Math/Vector.h"

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
		space(space)
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

enum RenderingConfigFields{ PointSize, LineWidth, DrawBB };

template<typename T>
using RenderingConfig = std::tuple < T, T, bool >;

enum MetaballConfigFields{ Center, Radius, Charge };
using MetaballConfig = std::tuple < Math::Vector3d<float>, float, float >;


class MainConfig{
public:
	MainConfig() :
		metaballConfig(std::make_tuple(Math::Vector3d<float>(0,0,0),1, 1))
	{

	}

	GridConfig getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig& config) { this->gridConfig = config; }

	MetaballConfig getMetaballConfig() const { return metaballConfig; }

	void setMetaballConfig(const MetaballConfig& config) { this->metaballConfig = config; }

	RenderingConfig<float> getRenderingConfig() const { return renderingConfig; }

	void setRenderingConfig(const RenderingConfig<float>& config) { this->renderingConfig = config; }

private:
	GridConfig gridConfig;
	MetaballConfig metaballConfig;
	RenderingConfig<float> renderingConfig;
};
	}
}

#endif