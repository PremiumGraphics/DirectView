#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "BitSpaceTransformCommand.h"
#include "RenderingBuffer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class MainCommand final : private UnCopyable
{
public:
	MainCommand() :
		bsTransformCommand(std::make_shared<BitSpaceTransformCommand>()),
		renderingBuffer(std::make_shared<RenderingBuffer<float>>() )
	{}

	void clear() {
		renderingBuffer->clear();
	}

	BitSpaceTransformCommandSPtr getBitSpaceTransformCommand() const { return bsTransformCommand; }

	RenderingBufferSPtr<float> getRenderingBuffer() const { return renderingBuffer; }

private:
	BitSpaceTransformCommandSPtr bsTransformCommand;
	RenderingBufferSPtr<float> renderingBuffer;
};

	}
}

#endif