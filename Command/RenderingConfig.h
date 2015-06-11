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
		lineWidth(10),
		drawBoundingBox(false)
	{}

	RenderingConfig(const T pointSize, const T lineWidth, const T boundingBox) :
		pointSize( pointSize),
		lineWidth( lineWidth),
		boundingBox( boundingBox)
	{
	}

	T getPointSize() const { return pointSize; }

	T getLineWidth() const { return lineWidth; }

	bool isShowBoundingBox() const { return drawBoundingBox; }

	//bool isDrawBoundingBox() const { return }

private:
	T pointSize;
	T lineWidth;
	bool drawBoundingBox;
};
	}
}

#endif