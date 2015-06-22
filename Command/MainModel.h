#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

#include "VolumeModel.h"
#include "SurfaceModel.h"
#include "LightModel.h"
#include "MetaballModel.h"
#include "RenderingModel.h"
#include "SurfaceConstructCommand.h"

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
		camera(std::make_shared< Graphics::Camera<T> >()),
		volume(std::make_shared< VolumeModel<T> >())
	{
		uiMode = CAMERA_TRANSLATE;
	}

	void clear()
	{
		volume->clear();
		surface.clear();
		metaball.clear();
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
		for (const auto& b : metaball.getBalls()) {
			for (const auto& s : volume->getSpaces()) {
				const auto& m = b->getMetaball();
				s->getSpace()->add(*(m));
			}
		}
	}

	void createMetaball() {
		metaball.create();
		buildSurface();
	}

	void buildSurface()
	{
		//getSurface()->clear();
		surface.clear();
		toVolume();
		for (const auto& s : getVolume()->getSpaces()) {
			//getSurface()->create(*s->getSpace());
			const auto ss = surfaceConstructCommand.create(*s->getSpace());
			surface.add(ss);
		}
	}

	void instanciateSurface() {
		surface.instanciate();
	}

	void rotate(const Math::Vector3d<T>& v) {
		;
	}

	void buildRenderer() {
		rendering.buildRenderer();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, *camera);
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	VolumeModelSPtr<T> getVolume() const { return volume; }

	//SurfaceModelSPtr<T> getSurface() const { return surface; }


	void changeSelected(const Object::Type& type, const unsigned int id) {
		if (type == Object::Type::Metaball) {
			const auto selected = metaball.find(id);
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
			const auto selected = surface.find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		metaball.move(vector);
		volume->move(vector);
		surface.move(vector);
	}

	void deleteSelected() {
		metaball.deleteSelected();
		volume->deleteSelected();
		surface.deleteSelected();
	}

	void clearSelected() {
		metaball.clearSelected();
		volume->clearSelected();
		//surface->clearSelected();
	}

	void scale(const Math::Vector3d<T>& s) {
		volume->scale(s);

		//surface->scale(s);
	}

	MetaballConfig<T> getMetaballConfig() const {
		return metaball.getConfig();
	}

	void setMetaballConfig(const MetaballConfig<T>& config) {
		metaball.setConfig(config);
	}

	void setRendering() {
		rendering.clear();
		rendering.set(metaball);
		rendering.set(volume);
		rendering.set(surface);
	}

	//Graphics::PointBuffer getPointBuffer() { }

	void move(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& angle) {
		if (getUIMode() == CAMERA_TRANSLATE) {
			getCamera()->move(pos);
			getCamera()->addAngle(angle);
		}
		else if (getUIMode() == SELECTED_TRANSLATE) {
			move(pos);
			buildSurface();
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

	RenderingConfig<T> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<T>& config) { rendering.setConfig(config); }


private:
	Graphics::CameraSPtr<T> camera;
	LightModel<T> light;
	VolumeModelSPtr<T> volume;
	SurfaceModel<T> surface;
	MetaballModel<T> metaball;
	RenderingCommand<T> rendering;
	SurfaceConstructCommand<T> surfaceConstructCommand;

	UIMode uiMode;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif