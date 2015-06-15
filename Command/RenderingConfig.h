#ifndef __CRYSTAL_COMMAND_RENDERING_CONFIG_H__
#define __CRYSTAL_COMMAND_RENDERING_CONFIG_H__

#include <memory>

namespace Crystal {
	namespace Command {

template<typename T>
class WireframeConfig {
public:
	WireframeConfig()
	{
		setDefault();
	}

	WireframeConfig(const T pointSize, const T lineWidth, const bool drawBB_) :
		pointSize(pointSize),
		lineWidth(lineWidth),
		drawBB_(drawBB_)
	{
	}

	void setDefault() {
		pointSize = 10;
		lineWidth = 1;
		drawBB_ = true;
	}

	T getPointSize() const { return pointSize; }

	T getLineWidth() const { return lineWidth; }

	bool drawBB() const { return drawBB_; }

private:
	T pointSize;
	T lineWidth;
	bool drawBB_;
};

template<typename T>
using WireframeConfigSPtr = std::shared_ptr < WireframeConfig<T> >;

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
using NormalConfigSPtr = std::shared_ptr < NormalConfig<T> > ;

template<typename T>
class RenderingConfig {
public:
	RenderingConfig() :
		wfConfig( std::make_shared< WireframeConfig<T> >() ),
		nConfig(std::make_shared < NormalConfig<T> >()  )
	{}

	WireframeConfigSPtr<T> getWireframeConfig() const { return wfConfig; }

	NormalConfigSPtr<T> getNormalConfig() const { return nConfig; }

	void init() {
		wfConfig.init();
		nConfig.init();
	}

private:
	WireframeConfigSPtr<T> wfConfig;
	NormalConfigSPtr<T> nConfig;
};

template<typename T>
using RenderingConfigSPtr = std::shared_ptr < RenderingConfig<T> >;
	}
}

#endif