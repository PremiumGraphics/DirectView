#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "BitSpaceTransformCommand.h"
#include "ScalarSpaceTransformCommand.h"
#include "RenderingBuffer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class MainCommand final : private UnCopyable
{
public:
	MainCommand() :
		bsTransformCommand(std::make_shared<BitSpaceTransformCommand>()),
		ssTransformCommand(std::make_shared<ScalarSpaceTransformCommand<float> >()),
		renderingBuffer(std::make_shared<RenderingBuffer<float>>() )
	{}

	void clear() {
		renderingBuffer->clear();
	}

	BitSpaceTransformCommandSPtr getBitSpaceTransformCommand() const { return bsTransformCommand; }

	ScalarSpaceTransformCommandSPtr<float> getScalarSpaceTransformCommand() const { return ssTransformCommand; }

	RenderingBufferSPtr<float> getRenderingBuffer() const { return renderingBuffer; }

private:
	BitSpaceTransformCommandSPtr bsTransformCommand;
	ScalarSpaceTransformCommandSPtr<float> ssTransformCommand;
	RenderingBufferSPtr<float> renderingBuffer;
};

	}
}

#endif