#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "BitSpaceTransformCommand.h"
#include "ScalarSpaceTransformCommand.h"
#include "RenderingCommand.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class MainCommand final : private UnCopyable
{
public:
	MainCommand() :
		bsTransformCommand(std::make_shared<BitSpaceTransformCommand>()),
		ssTransformCommand(std::make_shared<ScalarSpaceTransformCommand<float> >()),
		renderingCommand(std::make_shared<RenderingBuffer<float>>() )
	{}

	BitSpaceTransformCommandSPtr getBitSpaceTransformCommand() const { return bsTransformCommand; }

	ScalarSpaceTransformCommandSPtr<float> getScalarSpaceTransformCommand() const { return ssTransformCommand; }

	RenderingBufferSPtr<float> getRenderingCommand() const { return renderingCommand; }

private:
	BitSpaceTransformCommandSPtr bsTransformCommand;
	ScalarSpaceTransformCommandSPtr<float> ssTransformCommand;
	RenderingBufferSPtr<float> renderingCommand;
};

	}
}

#endif