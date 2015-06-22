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
		drawPlane = true;
		pointSize = 10;
		drawSurface = true;
		drawInstance = true;
		drawCells = true;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawBB;
	bool drawPlane;

	bool drawSurface;
	bool drawVolume;
	bool drawMetaball;
	bool drawInstance;
	bool drawCells;
};


template<typename T>
class RenderingCommand
{

public:
	RenderingCommand() :
	mode( Mode::WIRE_FRAME)
	{
	}

	enum class Mode {
		WIRE_FRAME,
		SURFACE,
	};

	void clear(){
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
	}

	void add(const SurfaceModel<T>& surface)
	{
		for (const auto& p : surface.getSurfaces()) {
			if (p->isVisible()) {
				//normalRenderer.add(*(p->getPolygon()));
				const auto& surface = p->getPolygon();
				const int type = static_cast<int>(p->getType());
				const int isSelected = p->isSelected();
				//pointBuffer.add(*surface, type, p->getId(), isSelected);
				triangleBuffer.add(*surface, type, p->getId(), isSelected);
			}
		}
	}

	void add(const Graphics::Surface<T>& surface) {
		lineBuffer.add(surface, -1, -1, false);
	}

	void add(const VolumeModel<T>& volume) {
		for (const auto& b : volume.getSpaces()) {
			if (b->isVisible()) {
				const auto& ss = b->getSpace();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				lineBuffer.add(*ss, type, b->getId(), isSelected);
				if (config.drawCells) {
					addCells(*ss);
				}
			}
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

	void add(const MetaballModel<T>& metaball) {
		for (const auto& b : metaball.getBalls()) {
			if (b->isVisible()) {
				const auto center = b->getMetaball()->getCenter();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				pointBuffer.addPosition(center, type, b->getId(), isSelected);
			}
		}

	}

	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

	void setMode(const Mode m) { this->mode = m; }

	Mode getMode() const { return mode; }

	void render(const int width, const int height, const Graphics::Camera<float>& camera) {

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);

		glPointSize(getConfig().pointSize);

		if ( getMode() == RenderingCommand<float>::Mode::WIRE_FRAME) {
			glLineWidth(getConfig().lineWidth);
			wireframeRenderer.render(width, height, camera, lineBuffer);

			//			glPointSize( this->getPointSize());
			wireframeRenderer.render(width, height, camera, pointBuffer);
			wireframeRenderer.render(width, height, camera, triangleBuffer);

		}
		else if ( getMode() == RenderingCommand<float>::Mode::SURFACE) {
			//surfaceRenderer.render(width, height, c );
		}
		else {
			assert(false);
		}
	}

	void buildRenderer() {
		normalRenderer.build();
		wireframeRenderer.build();
	}



private:
	RenderingConfig<float> config;
	Mode mode;

	Graphics::NormalRenderer normalRenderer;
	Shader::WireframeRenderer wireframeRenderer;

	Graphics::PointBuffer<float> pointBuffer;
	Graphics::LineBuffer<float> lineBuffer;
	Graphics::TriangleBuffer<float> triangleBuffer;


};

	}
}

#endif