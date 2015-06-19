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
		lineWidth = 10;
		drawBB_ = true;
		drawPlane_ = true;
		pointSize = 10;
	}

	T pointSize;
	T lineWidth;
	T normalScale;

	bool drawBB_;
	bool drawPlane_;

	bool drawSurface;
	bool drawVolume;
	bool drawMetaball;
};


template<typename T>
class RenderingModel {

public:

	void clear(){
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();
	}

	void set(const SurfaceModelSPtr<float>& model)
	{
		if (!config.drawSurface) {
			return;
		}
		for (const auto& p : model->getPolygons()) {
			if (p->isVisible()) {
				//normalRenderer.add(*(p->getPolygon()));
				const auto& surface = p->getPolygon();
				const int type = static_cast<int>(p->getType());
				const int isSelected = p->isSelected();
				pointBuffer.add(*surface, type, p->getId(), isSelected);
				lineBuffer.add(*surface, type, p->getId(), isSelected);
				triangleBuffer.add(*surface, type, p->getId(), isSelected);
			}
		}
	}

	void set(const VolumeModelSPtr<float>& model)
	{
		if (!config.drawVolume) {
			return;
		}
		for (const auto& b : model->getSpaces()) {
			if (b->isVisible()) {
				const auto& ss = b->getSpace();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				lineBuffer.add(*ss, type, b->getId(), isSelected);
			}
		}

	}

	void set(const MetaballModelSPtr<float>& model)
	{
		if (!config.drawMetaball) {
			return;
		}
		for (const auto& b : model->getBalls()) {
			if (b->isVisible()) {
				const auto center = b->getMetaball()->getCenter();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				pointBuffer.addPosition(center, type, b->getId(), isSelected);
			}
		}
	}


	Graphics::PointBuffer<float> getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer<float> getLineBuffer() const { return lineBuffer; }

	Graphics::TriangleBuffer<float> getTriangleBuffer() const { return triangleBuffer; }

	void setConfig(const RenderingConfig<float>& config) { this->config = config; }

	RenderingConfig<float> getConfig() const { return config; }

private:
	Graphics::PointBuffer<float> pointBuffer;
	Graphics::LineBuffer<float> lineBuffer;
	Graphics::TriangleBuffer<float> triangleBuffer;
	RenderingConfig<float> config;
};

template<typename T>
using RenderingModelSPtr = std::shared_ptr < RenderingModel<T> > ;
	}
}

#endif