#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include <tuple>

#include "../Math/Vector.h"
#include "../Math/Space.h"

namespace Crystal {
	namespace Command {

template<typename T>
class RenderingConfig {
public:
	RenderingConfig()
	{
		setDefault();
	}

	RenderingConfig(const T pointSize, const T lineWidth, const bool drawBB_) :
		pointSize( pointSize ),
		lineWidth( lineWidth ),
		drawBB_( drawBB_ )
	{
	}

	void setDefault() {
		pointSize = 10;
		lineWidth = 1;
		drawBB_ = true;
	}

	T getPointSize() const { return pointSize; }

	T getLineWidth() const { return lineWidth; }

	bool drawBB() const { return drawBB_; }
	
private:
	T pointSize;
	T lineWidth;
	bool drawBB_;
};

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

enum GridConfigFields{ Resx, Resy, Resz, Space };
using GridConfig = std::tuple < unsigned int, unsigned int, unsigned int, Math::Space3d<float> > ;

template<typename T>
class MainConfig{
public:
	MainConfig() :
		gridConfig( std::make_tuple(20, 20, 20, Math::Space3d<float>::Unit()) )
	{

	}

	GridConfig getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig& config) { this->gridConfig = config; }

	MetaballConfig<T> getMetaballConfig() const { return metaballConfig; }

	void setMetaballConfig(const MetaballConfig<T>& config) { this->metaballConfig = config; }

	RenderingConfig<T> getRenderingConfig() const { return renderingConfig; }

	void setRenderingConfig(const RenderingConfig<T>& config) { this->renderingConfig = config; }

private:
	GridConfig gridConfig;
	MetaballConfig<T> metaballConfig;
	RenderingConfig<T> renderingConfig;
};
	}
}

#endif