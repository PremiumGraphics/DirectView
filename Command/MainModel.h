#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Graphics/Camera.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "LightModel.h"
#include "MetaballModel.h"
#include "RenderingModel.h"

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
		metaball(std::make_shared< MetaballObjectModel<T> >()),
		rendering(std::make_shared< RenderingModel<T> >() )
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

	RenderingModelSPtr<T> getRenderingModel() const { return rendering; }


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


	void setRendering()
	{
		//normalRenderer.clear();
		rendering->clear();

		rendering->set(getSurfaceModel());
		rendering->set(getVolumeModel());
		rendering->set(getMetaballModel());
	}



private:
	Graphics::CameraSPtr<T> camera;
	LightModelSPtr<T> light;
	VolumeModelSPtr<T> volume;
	SurfaceModelSPtr<T> surface;
	MetaballModelSPtr<T> metaball;
	RenderingModelSPtr<T> rendering;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif