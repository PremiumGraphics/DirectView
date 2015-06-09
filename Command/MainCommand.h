#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "BitSpaceTransformCommand.h"
#include "ScalarSpaceTransformCommand.h"
#include "RenderingCommand.h"

namespace Crystal {
	namespace Command {

class MainCommand
{
public:
	MainCommand() :
		bsTransformCommand(std::make_shared<BitSpaceTransformCommand>()),
		ssTransformCommand(std::make_shared<ScalarSpaceTransformCommand<float> >())
	{}

	RenderingCommand renderingCommand;

	BitSpaceTransformCommandSPtr getBitSpaceTransformCommand() const { return bsTransformCommand; }

	ScalarSpaceTransformCommandSPtr<float> getScalarSpaceTransformCommand() const { return ssTransformCommand; }

private:
	BitSpaceTransformCommandSPtr bsTransformCommand;
	ScalarSpaceTransformCommandSPtr<float> ssTransformCommand;

};

	}
}

#endif