#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include <tuple>

#include "../Math/Vector.h"
#include "../Math/Space.h"

namespace Crystal {
	namespace Command {

enum RenderingConfigFields{ PointSize, LineWidth, DrawBB };

template<typename T>
using RenderingConfig = std::tuple < T, T, bool >;

enum MetaballConfigFields{ Center, Radius, Charge };

template<typename T>
using MetaballConfig = std::tuple < Math::Vector3d<T>, T, T >;

enum GridConfigFields{ Resx, Resy, Resz, Space };
using GridConfig = std::tuple < unsigned int, unsigned int, unsigned int, Math::Space3d<float> > ;

class MainConfig{
public:
	MainConfig() :
		metaballConfig(std::make_tuple(Math::Vector3d<float>(0.0f,0.0f,0.0f),1.0f, 1.0f)),
		gridConfig( std::make_tuple(20, 20, 20, Math::Space3d<float>::Unit()) )
	{

	}

	GridConfig getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig& config) { this->gridConfig = config; }

	MetaballConfig<float> getMetaballConfig() const { return metaballConfig; }

	void setMetaballConfig(const MetaballConfig<float>& config) { this->metaballConfig = config; }

	RenderingConfig<float> getRenderingConfig() const { return renderingConfig; }

	void setRenderingConfig(const RenderingConfig<float>& config) { this->renderingConfig = config; }

private:
	GridConfig gridConfig;
	MetaballConfig<float> metaballConfig;
	RenderingConfig<float> renderingConfig;
};
	}
}

#endif