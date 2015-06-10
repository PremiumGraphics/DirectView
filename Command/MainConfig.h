#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include "GridConfig.h"
#include "MetaballConfig.h"

namespace Crystal {
	namespace Command {

class MainConfig{
public:
	GridConfig getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig& config) { this->gridConfig = config; }

	MetaballConfig getMetaballConfig() const { return metaballConfig; }

	void setMetaballConfig(const MetaballConfig& config) { this->metaballConfig = config; }

private:
	GridConfig gridConfig;
	MetaballConfig metaballConfig;
};
	}
}

#endif