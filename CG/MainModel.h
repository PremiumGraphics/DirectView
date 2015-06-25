#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "RenderingModel.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

enum UIMode
{
	CAMERA_TRANSLATE,
	PARTICLE_TRANSLATE,
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
class ParticleConfig {
public:
	ParticleConfig()
	{
		setDefault();
	}

	ParticleConfig(const Math::Vector3d<T>& center, const T radius, const T charge) :
		center(center),
		radius(radius),
		charge(charge)
	{}

	void setDefault() {
		center = Math::Vector3d<T>(0, 0, 0);
		radius = 1;
		charge = 1;
	}

	Math::Vector3d<T> getCenter() const { return center; }

	T getRadius() const { return radius; }

	T getCharge() const { return charge; }

private:
	Math::Vector3d<T> center;
	T radius;
	T charge;
};


template<typename T>
class MainModel final : private UnCopyable
{
public:
	MainModel() :
		camera(std::make_shared< Graphics::Camera<T> >()),
		uiMode( CAMERA_TRANSLATE )
	{
		mc.buildTable();
		setupVolumes();
		createPreVolume();
		createSurface(preVolume);
		setRendering();
	}

	void clear()
	{
		preVolume.setValue(0);
		bakedVolume.setValue(0);
		preSurfaces.clear();
		//bakedSurfaces.clear();
	}

	void fitCamera() {
		camera->init();
	}

	/*
	Math::Box<T> getBoundingBox() const {
		return Math::Box<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(1, 1, 1));
	}
	*/

	void setupVolumes() {
		Math::Grid3d<T> grid(vConfig.resx, vConfig.resy, vConfig.resz);
		Math::Volume3d<T> v(vConfig.space, grid);
		preVolume = v;
		bakedVolume = v;
	}

	void createPreVolume() {
		preSurfaces.clear();
		preVolume = bakedVolume;
		preVolume.add(particle);
		const auto& s = createSurface(preVolume);
		preSurfaces.push_back(s);
		setRendering();
	}

	void bakeParticleToVolume() {
		bakedVolume = preVolume;
		const auto& surface = createSurface(bakedVolume);
		preSurfaces.push_back(surface);
		setRendering();
	}

	Graphics::SurfaceSPtr<T> createSurface(const Math::Volume3d<float>& ss)
	{
		const auto& triangles = mc.march(ss, vConfig.threshold);

		Graphics::SurfaceSPtr<T> surface = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			surface->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return surface;
	}

	void doExport(const std::string& filename) const {
		IO::STLFile file;

		IO::STLCellVector cells;
		for (const auto& s : preSurfaces) {
			for (const auto& f : s->getFaces()) {
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


	void buildRenderer() {
		rendering.buildRenderer();
	}

	void reverseParticleCharge() {
		particle.reverseCharge();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, *camera);
	}


	Graphics::CameraSPtr<T> getCamera() const { return camera; }


	void setRendering() {
		rendering.clear();
		rendering.add(particle);
		rendering.add(preVolume);
		for (const auto& s : preSurfaces) {
			rendering.add(*s);
		}
		/*
		for (const auto& s : bakedSurfaces) {
			rendering.add(*s);
		}
		*/
	}

	void move(const Math::Vector3d<T>& left, const Math::Vector3d<T>& middle, const Math::Vector3d<T>& right) {
		if (getUIMode() == CAMERA_TRANSLATE) {
			const Vector3d<T> v(left.getX(), left.getY(), middle.getX());
			camera->move(v);
			camera->addAngle(right);
		}
		else if (getUIMode() == PARTICLE_TRANSLATE) {
			const Vector3d<T> v(left.getX(), left.getY(), middle.getX());
			particle.move(v);
			particle.addRadius(right.getY());
			createPreVolume();
			const auto& s = createSurface(preVolume);
			setRendering();
			//ssTransformCmd->move(pos);
		}
		else {
			assert(false);
		}
	}

	/*
	void addParticleCharge(const T delta) {
		particle.addCharge(delta);
	}
	*/


/*	void addParticleRadius(const T delta) {
		particle
	}
	*/

	UIMode getUIMode() const { return uiMode; }

	void setUIMode(const UIMode m) { this->uiMode = m; }

	RenderingConfig<T> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<T>& config) { rendering.setConfig(config); }

	VolumeConfig<T> getVolumeConfig() const { return vConfig; }

	void setVolumeConfig(const VolumeConfig<T>& config) { vConfig = config; }

private:
	Graphics::CameraSPtr<T> camera;

	Math::Volume3d<T> preVolume;
	Math::Volume3d<T> bakedVolume;
	//Math::Volume3d<T> volume;

	Math::Particle3d<T> particle;
	RenderingCommand<T> rendering;
	Math::MarchingCube<T> mc;
	Graphics::SurfaceSPtrList<T> preSurfaces;
	//Graphics::SurfaceSPtrList<T> bakedSurfaces;
	UIMode uiMode;
	VolumeConfig<T> vConfig;
	ParticleConfig<T> pConfig;

};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif