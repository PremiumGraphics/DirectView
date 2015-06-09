#ifndef __CRYSTAL_COMMAND_MAIN_CONFIG_H__
#define __CRYSTAL_COMMAND_MAIN_CONFIG_H__

#include "GridConfig.h"

namespace Crystal {
	namespace Command {

class MainConfig{
public:
	GridConfig getGridConfig() const { return gridConfig; }

	void setGridConfig(const GridConfig& config) { this->gridConfig = config; }

private:
	GridConfig gridConfig;
};
	}
}

#endif