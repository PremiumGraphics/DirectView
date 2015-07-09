#ifndef __CRYSTAL_MODEL_RENDERING_MODEL_H_
#define __CRYSTAL_MODEL_RENDERING_MODEL_H_

#include "../Shader/PointRenderer.h"
#include "../Shader/WireframeRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/VolumeRenderer.h"

#include "../Util/UnCopyable.h"
#include "DisplayList.h"

namespace Crystal{
	namespace Command {


template<typename T>
struct RenderingConfig {
public:
	RenderingConfig()
	{
		setDefault();
	}

	void setDefault() {
		normalScale = 1;
		lineWidth = 1;
		pointSize = 5;
		drawPoint = true;
		drawWire = true;
		drawSmooth = true;
		drawVolume = true;
		drawCells = false;
		drawNormal = false;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawPoint;
	bool drawWire;
	bool drawSmooth;
	bool drawVolume;
	bool drawCells;
	bool drawNormal;
};


class RenderingCommand final : UnCopyable
{

public:
	RenderingCommand();

	~RenderingCommand() = default;

	void build();

	void clear();


	void set(const UI::DisplayList& list);

	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

	void changePoint() {
		config.drawPoint = !config.drawPoint;
	}

	void changeVolume() {
		config.drawVolume = !config.drawVolume;
	}

	void changeSmooth() {
		config.drawSmooth = !config.drawSmooth;
	}

	void changeNormal() {
		config.drawNormal = !config.drawNormal;
	}

	void changeWire() {
		config.drawWire = !config.drawWire;
	}

	void render(const int width, const int height, const Graphics::Camera<float>& camera);

private:
	RenderingConfig<float> config;

	std::shared_ptr< Shader::NullRenderer > nullRenderer;
	std::shared_ptr< Shader::WireframeRenderer > wireframeRenderer;
	Shader::NormalRenderer normalRenderer;
	std::shared_ptr< Shader::PointRenderer > pointRenderer;
	//Shader::WireframeRenderer wireframeRenderer;
	Shader::SmoothRenderer smoothRenderer;
	Shader::VolumeRenderer volumeRenderer;


	void add(const Math::Particle3d<float>& particle);

	void add(const Graphics::Surface<float>& surface);

	void add(const Math::Volume3d<float>& volume);

	void add(const Math::Line3d<float>& line);


	//Shader::RendererBaseSPtrList activeRenderers;
};

	}
}

#endif