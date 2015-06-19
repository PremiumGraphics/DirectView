#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "LightModel.h"
#include "MetaballModel.h"
#include "RenderingModel.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

enum UIMode
{
	CAMERA_TRANSLATE,
	SELECTED_TRANSLATE,
	SELECTED_ROTATE,
	SELECTED_SCALE,
};


template<typename T>
class MainModel final : private UnCopyable
{
public:
	MainModel() :
		light(std::make_shared< LightModel<T> >()),
		camera(std::make_shared< Graphics::Camera<T> >()),
		volume(std::make_shared< VolumeModel<T> >()),
		surface(std::make_shared< SurfaceModel<T> >()),
		metaball(std::make_shared< MetaballObjectModel<T> >()),
		rendering(std::make_shared< RenderingModel<T> >() )
	{
		uiMode = CAMERA_TRANSLATE;
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
		for (const auto& s : volume->getSpaces()) {
			s->getSpace()->setValue(0);
		}
		for (const auto& b : metaball->getBalls()) {
			for (const auto& s : volume->getSpaces()) {
				const auto& m = b->getMetaball();
				s->getSpace()->add(*(m));
			}
		}
	}

	void polygonize()
	{
		getSurfaceModel()->clear();
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

	void clearSelected() {
		metaball->clearSelected();
		volume->clearSelected();
		//surface->clearSelected();
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

	void move(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& angle) {
		if (getUIMode() == CAMERA_TRANSLATE) {
			getCamera()->move(pos);
			getCamera()->addAngle(angle);
		}
		else if (getUIMode() == SELECTED_TRANSLATE) {
			move(pos);
			polygonize();
			setRendering();
			//ssTransformCmd->move(pos);
		}
		else if (getUIMode() == SELECTED_ROTATE) {
			rotate(angle);
			setRendering();
		}
		else if (getUIMode() == SELECTED_SCALE) {
			scale(Vector3d<float>(1, 1, 1) + pos*0.01f);
			setRendering();
		}
		else {
			assert(false);
		}
	}

	UIMode getUIMode() const { return uiMode; }

	void setUIMode(const UIMode m) { this->uiMode = m; }

private:
	Graphics::CameraSPtr<T> camera;
	LightModelSPtr<T> light;
	VolumeModelSPtr<T> volume;
	SurfaceModelSPtr<T> surface;
	MetaballModelSPtr<T> metaball;
	RenderingModelSPtr<T> rendering;

	UIMode uiMode;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif