#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "BitSpaceTransformCommand.h"
#include "ScalarSpaceTransfomCommand.h"
#include "RenderingCommand.h"

namespace Crystal {
	namespace Command {

class MainCommand
{
	BitSpaceTransformCommand bsTransformCommand;
	ScalarSpaceTransformCommand ssTransformCommand;
	RenderingCommand renderingCommand;
};

	}
}

#endif