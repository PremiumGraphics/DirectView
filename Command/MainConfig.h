#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include <tuple>

#include "../Math/Vector.h"
#include "../Math/Space.h"

#include "RenderingConfig.h"

namespace Crystal {
	namespace Command {


template<typename T>
class MetaballConfig {
public:
	MetaballConfig()
	{
		setDefault();
	}

	MetaballConfig(const Math::Vector3d<T>& center, const T radius, const T charge) :
		center(center),
		radius(radius),
		charge(charge)
	{}

	void setDefault() {
		center = Math::Vector3d<T>(0, 0, 0);
		radius = 1;
		charge = 1;
	}

	Math::Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	T getCharge() const { return charge; }

private:
	Math::Vector3d<T> center;
	T radius;
	T charge;
};

template<typename T>
class GridConfig {
public:
	GridConfig() {
		setDefault();
	}

	GridConfig(const unsigned int resx, const unsigned int resy, const unsigned int resz, const Math::Space3d<T>& space) :
		resx(resx),
		resy(resy),
		resz(resz),
		space(space)
	{}

	unsigned int getResx() const { return resx; }

	unsigned int getResy() const { return resy; }

	unsigned int getResz() const { return resz; }

	Math::Space3d<T> getSpace() const { return space; }

	void setDefault() {
		resx = 20;
		resy = 20;
		resz = 20;
		space = Math::Space3d<T>::Unit();
	}

private:
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	Math::Space3d<T> space;
};

template<typename T>
class MainConfig{
public:
	MainConfig() :
		renderingConfig(std::make_shared<RenderingConfig<T> >() )
	{
	}

	GridConfig<T> getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig<T>& config) { this->gridConfig = config; }

	MetaballConfig<T> getMetaballConfig() const { return metaballConfig; }

	void setMetaballConfig(const MetaballConfig<T>& config) { this->metaballConfig = config; }

	RenderingConfigSPtr<T> getRenderingConfig() const { return renderingConfig;}

private:
	GridConfig<T> gridConfig;
	MetaballConfig<T> metaballConfig;
	RenderingConfigSPtr<T> renderingConfig;
};
	}
}

#endif