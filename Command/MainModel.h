#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

#include "VolumeModel.h"
#include "MetaballModel.h"
#include "RenderingModel.h"
#include "FileExportCommand.h"
#include "SurfaceConstructCommand.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

enum UIMode
{
	CAMERA_TRANSLATE,
	SELECTED_TRANSLATE,
};


template<typename T>
class MainModel final : private UnCopyable
{
public:
	MainModel() :
		camera(std::make_shared< Graphics::Camera<T> >()),
		uiMode( CAMERA_TRANSLATE )
	{
	}

	void clear()
	{
		volume.clear();
		surface.clear();
		metaball.clear();
	}

	void toVolume() {
		for (const auto& s : volume.getSpaces()) {
			s->getSpace()->setValue(0);
		}
		for (const auto& b : metaball.getBalls()) {
			for (const auto& s : volume.getSpaces()) {
				const auto& m = b->getMetaball();
				s->getSpace()->add(*(m));
			}
		}
	}

	void createMetaball() {
		metaball.create();
		createSurface();
	}

	void fitCamera() {
		camera->init();
	}

	/*
	Math::Box<T> getBoundingBox() const {
		return Math::Box<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(1, 1, 1));
	}
	*/

	void createSurface() {
		surface.clear();
		toVolume();
		for (const auto& s : volume.getSpaces()) {
			//getSurface()->create(*s->getSpace());
			const auto ss = surface.create(*s->getSpace());
		}
		setRendering();
	}

	void doExport(const std::string& filename) const {
		FileExportCommand<T> command;
		command.exportToSTL(filename, surface.getSurfaces());
	}

	void createVolume() {
		volume.create();
	}

	bool canNotCreateMetaball() {
		return volume.getSpaces().empty();
	}

	void buildRenderer() {
		rendering.buildRenderer();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, *camera);
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	void changeSelected(const Object::Type& type, const unsigned int id) {
		if (type == Object::Type::Metaball) {
			const auto selected = metaball.find(id);
			if (selected != nullptr) {
				selected->changeSelected();
			}
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		metaball.move(vector);
	}

	void deleteSelected() {
		metaball.deleteSelected();
	}

	void clearSelected() {
		metaball.clearSelected();
	}

	MetaballConfig<T> getMetaballConfig() const {
		return metaball.getConfig();
	}

	void setMetaballConfig(const MetaballConfig<T>& config) {
		metaball.setConfig(config);
	}

	void setRendering() {
		rendering.clear();
		rendering.add(metaball);
		rendering.add(volume);
		for (const auto& s : surface.getSurfaces()) {
			rendering.add(*s);
		}

	}

	//Graphics::PointBuffer getPointBuffer() { }

	void move(const Math::Vector3d<T>& pos, const Math::Vector3d<T>& angle) {
		if (getUIMode() == CAMERA_TRANSLATE) {
			getCamera()->move(pos);
			getCamera()->addAngle(angle);
		}
		else if (getUIMode() == SELECTED_TRANSLATE) {
			move(pos);
			createSurface();
			setRendering();
			//ssTransformCmd->move(pos);
		}
		else {
			assert(false);
		}
	}


	UIMode getUIMode() const { return uiMode; }

	void setUIMode(const UIMode m) { this->uiMode = m; }

	RenderingConfig<T> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<T>& config) { rendering.setConfig(config); }

	VolumeConfig<T> getVolumeConfig() const { return volume.getConfig(); }

	void setVolumeConfig(const VolumeConfig<T>& config) { volume.setConfig(config); }

private:
	Graphics::CameraSPtr<T> camera;
	VolumeModel<T> volume;
	MetaballModel<T> metaball;
	RenderingCommand<T> rendering;
	SurfaceConstructCommand<T> surface;
	UIMode uiMode;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif