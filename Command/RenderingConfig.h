#ifndef __CRYSTAL_COMMAND_RENDERING_CONFIG_H__
#define __CRYSTAL_COMMAND_RENDERING_CONFIG_H__

namespace Crystal {
	namespace Command {

template<typename T>
class RenderingConfig
{
public:
	RenderingConfig() :
		pointSize(10),
		lineWidth(10)
	{}

	RenderingConfig(const T pointSize, const T lineWidth) :
		pointSize( pointSize),
		lineWidth( lineWidth)
	{
	}

	T getPointSize() const { return pointSize; }

	T getLineWidth() const { return lineWidth; }

private:
	T pointSize;
	T lineWidth;
};
	}
}

#endif