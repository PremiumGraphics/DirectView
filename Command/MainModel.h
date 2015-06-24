#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"

#include "MetaballModel.h"
#include "RenderingModel.h"
#include "FileExportCommand.h"

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
class VolumeConfig {
public:
	VolumeConfig() {
		setDefault();
	}

	VolumeConfig(const unsigned int resx, const unsigned int resy, const unsigned int resz, const Math::Space3d<T>& space) :
		resx(resx),
		resy(resy),
		resz(resz),
		space(space)
	{}

	unsigned int getResx() const { return resx; }

	unsigned int getResy() const { return resy; }

	unsigned int getResz() const { return resz; }

	Math::Space3d<T> getSpace() const { return space; }

	void setDefault() {
		resx = 20;
		resy = 20;
		resz = 20;
		space = Math::Space3d<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(2, 2, 2));
	}

private:
	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	Math::Space3d<T> space;
};


template<typename T>
class MainModel final : private UnCopyable
{
public:
	MainModel() :
		camera(std::make_shared< Graphics::Camera<T> >()),
		volume(std::make_shared< Math::Volume3d<T> >()),
		uiMode( CAMERA_TRANSLATE )
	{
		mc.buildTable();
		createVolume(vConfig);
	}

	void clear()
	{
		surfaces.clear();
		metaball.clear();
	}

	void toVolume() {
		volume->setValue(0);
		for (const auto& b : metaball.getParticles()) {
			const auto& m = b->getMetaball();
			volume->add(*(m));
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
		surfaces.clear();
		toVolume();
		const auto& ss = create(*volume);
		setRendering();
	}


	Graphics::SurfaceSPtr<T> create(const Math::Volume3d<float>& ss)
	{
		const auto& triangles = mc.march(ss, 0.5);

		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		surfaces.push_back(polygon);
		return surfaces.back();
	}

	void doExport(const std::string& filename) const {
		FileExportCommand<T> command;
		command.exportToSTL(filename, surfaces);
	}

	void createVolume(const VolumeConfig<T>& config) {
		Math::Grid3d<T> grid(config.getResx(), config.getResy(), config.getResz());
		Math::Volume3dSPtr<T> ss(new Math::Volume3d<T>(config.getSpace(), grid));
		volume = ss;
	}

	void buildRenderer() {
		rendering.buildRenderer();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, *camera);
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	void changeSelected(const unsigned int id) {
		const auto selected = metaball.find(id);
		if (selected != nullptr) {
			selected->changeSelected();
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		metaball.move(vector);
	}

	void deleteSelected() {
		surfaces.clear();
		metaball.deleteSelected();
	}

	void clearSelected() {
		surfaces.clear();
		metaball.clearSelected();
	}

	ParticleConfig<T> getMetaballConfig() const {
		return metaball.getConfig();
	}

	void setMetaballConfig(const ParticleConfig<T>& config) {
		metaball.setConfig(config);
	}

	void setRendering() {
		rendering.clear();
		rendering.add(metaball);
		rendering.add(*volume);
		for (const auto& s : surfaces) {
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

	VolumeConfig<T> getVolumeConfig() const { return vConfig; }

	void setVolumeConfig(const VolumeConfig<T>& config) { vConfig = config; }

private:
	Graphics::CameraSPtr<T> camera;
	Math::Volume3dSPtr<T> volume;
	ParticleModel<T> metaball;
	RenderingCommand<T> rendering;
	Math::MarchingCube<T> mc;
	Graphics::SurfaceSPtrList<T> surfaces;
	UIMode uiMode;
	VolumeConfig<T> vConfig;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif