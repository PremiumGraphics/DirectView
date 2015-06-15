#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "RenderingBuffer.h"

#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Command {

class MainCommand final : private UnCopyable
{
public:
	MainCommand() :
		renderingBuffer(std::make_shared<RenderingBuffer<float>>() )
	{}

	void clear() {
		renderingBuffer->clear();
	}

	RenderingBufferSPtr<float> getRenderingBuffer() const { return renderingBuffer; }

private:
	RenderingBufferSPtr<float> renderingBuffer;
};

	}
}

#endif