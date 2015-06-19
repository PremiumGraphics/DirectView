#ifndef __CRYSTAL_COMMAND_RENDERING_CONFIG_H__
#define __CRYSTAL_COMMAND_RENDERING_CONFIG_H__

namespace Crystal {
	namespace Model {

template<typename T>
class WireframeConfig {
public:
	WireframeConfig()
	{
		setDefault();
	}

	WireframeConfig( const T pointSize, const T lineWidth, const bool drawBB_, const bool drawPlane_) :
		pointSize( pointSize ),
		lineWidth(lineWidth),
		drawBB_(drawBB_),
		drawPlane_(drawPlane_)
	{
	}

	void setDefault() {
		normalScale = 1;
		lineWidth = 10;
		drawBB_ = true;
		drawPlane_ = true;
		pointSize = 10;
	}

	T getPointSize() const { return pointSize; }

	T getLineWidth() const { return lineWidth; }

	T getNormalScale() const { return normalScale; }


	bool drawBB() const { return drawBB_; }

	bool drawPlane() const { return drawPlane_; }

private:
	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawBB_;
	bool drawPlane_;
};


template<typename T>
class RenderingConfig {
public:
	RenderingConfig()
	{}

	WireframeConfig<T> getWireframeConfig() const { return wfConfig; }

	void setWireframeConfig(const WireframeConfig<T>& config) { wfConfig = config; }

	void init() {
		wfConfig.init();
	}

private:
	WireframeConfig<T> wfConfig;
};
	}
}

#endif