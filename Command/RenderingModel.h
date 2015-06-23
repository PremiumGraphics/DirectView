#ifndef __CRYSTAL_MODEL_RENDERING_MODEL_H_
#define __CRYSTAL_MODEL_RENDERING_MODEL_H_

#include "../Graphics/Buffer.h"
#include "../Shader/IDRenderer.h"
#include "../Shader/NormalRenderer.h"

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
		drawBB = true;
		pointSize = 20;
		drawSurface = true;
		drawCells = false;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawBB;

	bool drawSurface;
	bool drawVolume;
	bool drawCells;
};


template<typename T>
class RenderingCommand final : UnCopyable
{

public:
	RenderingCommand() = default;

	~RenderingCommand() = default;

	void clear(){
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
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
		lineBuffer.add(surface, -1, -1, false);
	}

	void add(const Math::Volume3d<T>& volume) {
		lineBuffer.add(volume, -1, -1, 0);
		if (config.drawCells) {
			addCells(volume);
		}
	}

	void addCells(const Math::Volume3d<T>& v) {
		const auto& cells = v.toCells();
		for (const auto c : cells) {
			const auto& space = c.getSpace();
			const Math::Box<T> box(space.getStart(), space.getEnd());
			lineBuffer.add(box, -1, -1, false);
		}
	}

	void add(const ParticleModel<T>& metaball) {
		for (const auto& b : metaball.getBalls()) {
			const auto center = b->getMetaball()->getCenter();
			const int type = static_cast<int>(b->getType());
			const int isSelected = b->isSelected();
			pointBuffer.addPosition(center, type, b->getId(), isSelected);
		}

	}

	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

	void render(const int width, const int height, const Graphics::Camera<float>& camera) {

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glPointSize(getConfig().pointSize);

		glLineWidth(getConfig().lineWidth);
		wireframeRenderer.render(width, height, camera, lineBuffer);

		wireframeRenderer.render(width, height, camera, pointBuffer);
		wireframeRenderer.render(width, height, camera, triangleBuffer);
	}

	void buildRenderer() {
		normalRenderer.build();
		wireframeRenderer.build();
	}



private:
	RenderingConfig<T> config;

	Graphics::NormalRenderer normalRenderer;
	Shader::WireframeRenderer wireframeRenderer;

	Graphics::PointBuffer<T> pointBuffer;
	Graphics::LineBuffer<T> lineBuffer;
	Graphics::TriangleBuffer<T> triangleBuffer;


};

	}
}

#endif