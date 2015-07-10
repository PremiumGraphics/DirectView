#ifndef __CRYSTAL_MODEL_RENDERING_MODEL_H_
#define __CRYSTAL_MODEL_RENDERING_MODEL_H_

#include "../Shader/PointRenderer.h"
#include "../Shader/WireframeRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/VolumeRenderer.h"

#include "../Util/UnCopyable.h"
#include "../Graphics/DisplayList.h"

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
	RenderingCommand() :
		wireframeRenderer(std::make_shared<Shader::WireframeRenderer>()),
		pointRenderer(std::make_shared<Shader::PointRenderer>())
	{}

	~RenderingCommand() = default;

	void build() {
		normalRenderer.build();
		wireframeRenderer->build();
		smoothRenderer.build();
		volumeRenderer.build();
		pointRenderer->build();
	}

	void clear() {
		normalRenderer.clear();
		pointRenderer->clear();
		wireframeRenderer->clear();
		smoothRenderer.clear();
		volumeRenderer.clear();
	}


	void set(const Graphics::DisplayList& list) {
		clear();
		for (const auto& l : list.getLines()) {
			add(l);
		}
		for (const auto& b : list.getBrushes()) {
			add(b);
		}
		for (const auto& v : list.getVolumes()) {
			add(*v);
		}
		for (const auto& s : list.getSurfaces()) {
			add(*s);
		}
	}

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

	void render(const int width, const int height, const Graphics::Camera<float>& camera) {
		{
			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			glClear(GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);

			glPointSize(20.0);
			glLineWidth(getConfig().lineWidth);

			if (config.drawPoint) {
				pointRenderer->render(width, height, camera);
			}

			if (config.drawWire) {
				wireframeRenderer->render(width, height, camera);
			}

			if (config.drawNormal) {
				normalRenderer.render(width, height, camera);
			}

			if (config.drawSmooth) {
				smoothRenderer.render(width, height, camera);
			}

			if (config.drawVolume) {
				glPointSize(getConfig().pointSize);
				volumeRenderer.render(width, height, camera);
			}
		}

	}

private:
	RenderingConfig<float> config;

	std::shared_ptr< Shader::NullRenderer > nullRenderer;
	std::shared_ptr< Shader::WireframeRenderer > wireframeRenderer;
	Shader::NormalRenderer normalRenderer;
	std::shared_ptr< Shader::PointRenderer > pointRenderer;
	//Shader::WireframeRenderer wireframeRenderer;
	Shader::SmoothRenderer smoothRenderer;
	Shader::VolumeRenderer volumeRenderer;


	void add(const Graphics::BlendBrush<float>& b) {
		if (config.drawPoint) {
			pointRenderer->add(b);
		}
		if (config.drawWire) {
			wireframeRenderer->add(b);
		}
	}

	void add(const Graphics::Surface<float>& surface) {
		if (config.drawWire) {
			wireframeRenderer->add(surface);
		}
		if (config.drawNormal) {
			normalRenderer.add(surface);
		}
		if (config.drawSmooth) {
			smoothRenderer.add(surface);
		}
	}

	void add(const Math::Volume3d<float>& volume) {
		if (config.drawWire) {
			wireframeRenderer->add(volume);
		}
		/*
		if (config.drawCells) {
		addCells(volume);
		}
		*/
		if (config.drawVolume) {
			volumeRenderer.add(volume);
		}
	}

	void add(const Math::Line3d<float>& line) {
		if (config.drawWire) {
			wireframeRenderer->add(line);
		}
	}


	//Shader::RendererBaseSPtrList activeRenderers;
};

	}
}

#endif