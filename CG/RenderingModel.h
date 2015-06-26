#ifndef __CRYSTAL_MODEL_RENDERING_MODEL_H_
#define __CRYSTAL_MODEL_RENDERING_MODEL_H_

#include "../Graphics/Buffer.h"
#include "../Shader/PointRenderer.h"
#include "../Shader/WireframeRenderer.h"
#include "../Shader/NormalRenderer.h"
#include "../Shader/SmoothRenderer.h"
#include "../Shader/VolumeRenderer.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Model {


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
		enableLight = true;
		drawCells = false;
		drawNormal = false;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool enableLight;
	bool drawVolume;
	bool drawCells;
	bool drawNormal;
};


template<typename T>
class RenderingCommand final : UnCopyable
{

public:
	RenderingCommand() = default;

	~RenderingCommand() = default;

	void clear(){
		pointBuffer.clear();
		selectedPointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
		vBuffer.clear();
	}

	/*
	void add(const SurfaceModel<T>& surface)
	{
		for (const auto& p : surface.getSurfaces()) {
			if (p->isVisible()) {
				//normalRenderer.add(*(p->getPolygon()));
				const auto& surface = p->getSurface();
				const int type = static_cast<int>(p->getType());
				const int isSelected = p->isSelected();
				//pointBuffer.add(*surface, type, p->getId(), isSelected);
				triangleBuffer.add(*surface, type, p->getId(), isSelected);
			}
		}
	}
	*/

	void add(const Graphics::Surface<T>& surface) {
		lineBuffer.add(surface);
		if (config.drawNormal) {
			pointBuffer.add(surface, -1, false);
		}
		triangleBuffer.add(surface);
	}

	void add(const Math::Volume3d<T>& volume) {
		lineBuffer.add(volume);
		if (config.drawCells) {
			addCells(volume);
		}
		if (config.drawVolume) {
			vBuffer.add(volume);
		}
	}

	void addCells(const Math::Volume3d<T>& v) {
		const auto& cells = v.toCells();
		for (const auto c : cells) {
			const auto& space = c.getSpace();
			const Math::Box<T> box(space.getStart(), space.getEnd());
			lineBuffer.add(box);
		}
	}

	void add(const Math::Particle3d<T>& particle) {
		const auto& center = particle.getCenter();
		selectedPointBuffer.addPosition(center, Math::Vector3d<T>::Zero(), 0, 1);

	}

	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

	void render(const int width, const int height, const Graphics::Camera<float>& camera) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glPointSize(20.0);
		glLineWidth(getConfig().lineWidth);

		wireframeRenderer.render(width, height, camera, lineBuffer, false);
		pointRenderer.render(width, height, camera, pointBuffer, false);

		normalRenderer.render(width, height, camera, pointBuffer);

		if (config.enableLight) {
			smoothRenderer.render(width, height, camera, triangleBuffer);
		}

		glClear(GL_DEPTH_BUFFER_BIT);
		pointRenderer.render(width, height, camera, selectedPointBuffer, true);
		//wireframeRenderer.render(width, height, camera, triangleBuffer);

		glPointSize(getConfig().pointSize);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);

		volumeRenderer.render(width, height, camera, vBuffer);

		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
	}

	void buildRenderer() {
		normalRenderer.build();
		wireframeRenderer.build();
		smoothRenderer.build();
		volumeRenderer.build();
		pointRenderer.build();
	}

private:
	RenderingConfig<T> config;

	Shader::NormalRenderer normalRenderer;
	Shader::PointRenderer pointRenderer;
	Shader::WireframeRenderer wireframeRenderer;
	Shader::SmoothRenderer smoothRenderer;
	Shader::VolumeRenderer volumeRenderer;

	Graphics::PointBuffer<T> pointBuffer;
	Graphics::LineBuffer<T> lineBuffer;
	Graphics::TriangleBuffer<T> triangleBuffer;
	Graphics::VolumeBuffer<T> vBuffer;

	Graphics::PointBuffer<T> selectedPointBuffer;


};

	}
}

#endif