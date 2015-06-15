#ifndef __CRYSTAL_COMMAND_RENDERING_CONFIG_H__
#define __CRYSTAL_COMMAND_RENDERING_CONFIG_H__

namespace Crystal {
	namespace Command {

template<typename T>
class WireframeConfig {
public:
	WireframeConfig()
	{
		setDefault();
	}

	WireframeConfig( const T lineWidth, const bool drawBB_) :
		lineWidth(lineWidth),
		drawBB_(drawBB_)
	{
	}

	void setDefault() {
		lineWidth = 1;
		drawBB_ = true;
	}

	T getLineWidth() const { return lineWidth; }

	bool drawBB() const { return drawBB_; }

private:
	T lineWidth;
	bool drawBB_;
};

template<typename T>
class NormalConfig {
public:
	NormalConfig()
	{
		setDefault();
	}

	NormalConfig(const T normalScale, const T lineWidth) :
		normalScale(normalScale),
		lineWidth(lineWidth)
	{}

	void setDefault() {
		normalScale = 1;
		lineWidth = 1;
	}

	T getNormalScale() const { return normalScale; }

	T getLineWidth() const { return lineWidth; }

private:
	T normalScale;
	T lineWidth;
};


template<typename T>
class PointConfig
{
public:
	PointConfig()
	{
		setDefault();
	}

	explicit PointConfig(const T pointSize) :
		pointSize( pointSize )
	{}

	void setDefault() {
		pointSize = 10;
	}

	T getPointSize() const { return pointSize; }

private:
	T pointSize;
};


template<typename T>
class RenderingConfig {
public:
	RenderingConfig()
	{}

	WireframeConfig<T> getWireframeConfig() const { return wfConfig; }

	void setWireframeConfig(const WireframeConfig<T>& config) { wfConfig = config; }

	NormalConfig<T> getNormalConfig() const { return nConfig; }

	void setNormalConfig(const NormalConfig<T>& config) { nConfig = config; }

	PointConfig<T> getPointConfig() const { return pConfig; }

	void setPointConfig(const PointConfig<T>& config) { pConfig = config; }

	void init() {
		wfConfig->init();
		nConfig->init();
		pConfig.init();
	}

private:
	WireframeConfig<T> wfConfig;
	NormalConfig<T> nConfig;
	PointConfig<T> pConfig;
};
	}
}

#endif