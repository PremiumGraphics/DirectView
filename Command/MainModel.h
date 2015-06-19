#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Graphics/Camera.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "LightModel.h"
#include "MetaballModel.h"

#include "MainConfig.h"

#include "../Graphics/Buffer.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

template<typename T>
class MainModel {
public:
	MainModel() :
		light(std::make_shared< LightModel<T> >()),
		camera(std::make_shared< Graphics::Camera<T> >()),
		volume(std::make_shared< VolumeModel<T> >()),
		surface(std::make_shared< SurfaceModel<T> >()),
		metaball(std::make_shared< MetaballObjectModel<T> >())
	{
	}

	void clear()
	{
		volume->clear();
		surface->clear();
		metaball->clear();
	}

	/*
	void add(const GridConfig<T>& config)
	{
		const auto ss = getVolumeModel()->create(config);
		getSurfaceModel()->create(*(ss->getSpace()));
	}
	*/

	void toVolume() {
		for (const auto& b : metaball->getBalls()) {
			for (const auto& s : volume->getSpaces()) {
				const auto& m = b->getMetaball();
				s->getSpace()->add(*(m));
			}
		}
	}

	void polygonize()
	{
		toVolume();
		for (const auto& s : getVolumeModel()->getSpaces()) {
			getSurfaceModel()->create(*s->getSpace());
		}
	}
	void rotate(const Math::Vector3d<T>& v) {
		;
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	LightModelSPtr<T> getLightModel() const { return light; }

	VolumeModelSPtr<T> getVolumeModel() const { return volume; }

	SurfaceModelSPtr<T> getSurfaceModel() const { return surface; }

	MetaballModelSPtr<T> getMetaballModel() const { return metaball; }


	void changeSelected(const Object::Type& type, const unsigned int id) {
		if (type == Object::Type::Metaball) {
			const auto selected = metaball->find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
		else if (type == Object::Type::VOLUME) {
			const auto selected = volume->find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
		else if (type == Object::Type::Polygon) {
			const auto selected = surface->find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		metaball->move(vector);
		volume->move(vector);
		surface->move(vector);
	}

	void deleteSelected() {
		metaball->deleteSelected();
		volume->deleteSelected();
		surface->deleteSelected();
	}

	void scale(const Math::Vector3d<T>& s) {
		volume->scale(s);

		//surface->scale(s);
	}

	void set(const RenderingConfig<T>& config)
	{
		//normalRenderer.clear();
		pointBuffer.clear();
		lineBuffer.clear();
		triangleBuffer.clear();

		if (config.drawSurface) {
			set( getSurfaceModel());
		}
		if (config.drawVolume) {
			set( getVolumeModel());
		}
		if (config.drawMetaball) {
			set( getMetaballModel());
		}
	}

	Graphics::PointBuffer<float> getPointBuffer() const { return pointBuffer; }

	Graphics::LineBuffer<float> getLineBuffer() const { return lineBuffer; }

	Graphics::TriangleBuffer<float> getTriangleBuffer() const { return triangleBuffer; }


private:
	Graphics::CameraSPtr<T> camera;
	LightModelSPtr<T> light;
	VolumeModelSPtr<T> volume;
	SurfaceModelSPtr<T> surface;
	MetaballModelSPtr<T> metaball;

	Graphics::PointBuffer<float> pointBuffer;
	Graphics::LineBuffer<float> lineBuffer;
	Graphics::TriangleBuffer<float> triangleBuffer;



	void set(const SurfaceModelSPtr<float>& model)
	{
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
		for (const auto& b : model->getBalls()) {
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
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif