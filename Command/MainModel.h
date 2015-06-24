#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "ParticleModel.h"
#include "RenderingModel.h"

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

	void setDefault() {
		resx = 20;
		resy = 20;
		resz = 20;
		threshold = 0.5;
		space = Math::Space3d<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(2, 2, 2));
	}

	unsigned int resx;
	unsigned int resy;
	unsigned int resz;
	double threshold;
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
		particle.clear();
	}

	void toVolume() {
		volume->setValue(0);
		for (const auto& b : particle.getParticles()) {
			const auto& m = b->getMetaball();
			volume->add(*(m));
		}
	}

	void createMetaball() {
		particle.create();
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
		const auto& triangles = mc.march(ss, vConfig.threshold);

		Graphics::SurfaceSPtr<T> polygon = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			polygon->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		surfaces.push_back(polygon);
		return surfaces.back();
	}

	void doExport(const std::string& filename) const {
		IO::STLFile file;

		IO::STLCellVector cells;
		for (const auto& s : surfaces) {
			for (const Graphics::FaceSPtr<T>& f : s->getFaces()) {
				Math::Vector3dVector<T> positions;
				for (const auto& e : f->getEdges()) {
					positions.push_back(e->getStartPosition());
				}
				const auto normal = f->getNormal();
				STLCell cell(positions, normal);
				cells.push_back(cell);
			}
		}

		file.setTitle("TestTitle");
		file.setCells(cells);
		file.writeASCII(filename);
	}

	void createVolume(const VolumeConfig<T>& config) {
		Math::Grid3d<T> grid(config.resx, config.resy, config.resz);
		Math::Volume3dSPtr<T> ss(new Math::Volume3d<T>(config.space, grid));
		volume = ss;
		createSurface();
	}

	void buildRenderer() {
		rendering.buildRenderer();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, *camera);
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }

	void changeSelected(const unsigned int id) {
		const auto selected = particle.find(id);
		if (selected != nullptr) {
			selected->changeSelected();
		}
	}


	void move(const Math::Vector3d<T>& vector) {
		particle.move(vector);
	}

	void deleteSelected() {
		surfaces.clear();
		particle.deleteSelected();
	}

	void clearSelected() {
		surfaces.clear();
		particle.clearSelected();
	}

	ParticleConfig<T> getMetaballConfig() const {
		return particle.getConfig();
	}

	void setMetaballConfig(const ParticleConfig<T>& config) {
		particle.setConfig(config);
	}

	void setRendering() {
		rendering.clear();
		rendering.add(particle);
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
	ParticleModel<T> particle;
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