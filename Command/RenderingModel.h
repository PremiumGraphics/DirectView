#ifndef __CRYSTAL_MODEL_RENDERING_MODEL_H_
#define __CRYSTAL_MODEL_RENDERING_MODEL_H_

#include "../Graphics/Buffer.h"

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
		drawPlane_ = true;
		pointSize = 10;
		drawSurface = true;
		drawInstance = true;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawBB;
	bool drawPlane_;

	bool drawSurface;
	bool drawVolume;
	bool drawMetaball;
	bool drawInstance;
};

template<typename T>
class ViewBase {
public:


	void clear(){
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
	}


	void add(const Graphics::LineBuffer<T>& lines) {
		lineBuffer.add(lines);
	}

	void add(const Graphics::TriangleBuffer<T>& triangles) {
		triangleBuffer.add(triangles);
	}

	Graphics::PointBuffer<float> getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer<float> getLineBuffer() const { return lineBuffer; }

	Graphics::TriangleBuffer<float> getTriangleBuffer() const { return triangleBuffer; }

protected:
	Graphics::PointBuffer<float> pointBuffer;
	Graphics::LineBuffer<float> lineBuffer;
	Graphics::TriangleBuffer<float> triangleBuffer;

};

template<typename T>
class SurfaceView final : public ViewBase<T> {
public:
	void set(const SurfaceModel<float>& model)
	{

		for (const auto& p : model.getSurfaces()) {
			if (p->isVisible()) {
				//normalRenderer.add(*(p->getPolygon()));
				const auto& surface = p->getPolygon();
				const int type = static_cast<int>(p->getType());
				const int isSelected = p->isSelected();
				//pointBuffer.add(*surface, type, p->getId(), isSelected);
				if (p->isInstance()) {
					triangleBuffer.add(*surface, type, p->getId(), isSelected);
				}
				else {
					lineBuffer.add(*surface, type, p->getId(), isSelected);
				}
			}
		}
	}
};

template<typename T>
class VolumeView : public ViewBase < T >
{
public:
	void set(const VolumeModelSPtr<float>& model)
	{
		for (const auto& b : model->getSpaces()) {
			if (b->isVisible()) {
				const auto& ss = b->getSpace();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				lineBuffer.add(*ss, type, b->getId(), isSelected);
			}
		}

	}

};

template<typename T>
class MetaballView : public ViewBase < T >
{
public:
	void set(const MetaballModel<float>& model)
	{
		for (const auto& b : model.getBalls()) {
			if (b->isVisible()) {
				const auto center = b->getMetaball()->getCenter();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				pointBuffer.addPosition(center, type, b->getId(), isSelected);
			}
		}
	}
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


	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

	void setMode(const Mode m) { this->mode = m; }

	Mode getMode() const { return mode; }

private:
	RenderingConfig<float> config;
	Mode mode;

	SurfaceView<T> surface;
	VolumeView<T> volume;
	MetaballView<T> metaball;
};

template<typename T>
using RenderingModelSPtr = std::shared_ptr < RenderingCommand<T> > ;
	}
}

#endif