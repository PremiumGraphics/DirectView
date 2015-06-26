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

enum class UIMode
{
	CAMERA_TRANSLATE,
	PARTICLE_TRANSLATE,
	PARTICLE_STROKE,
};

enum class PlaneMode {
	XY,
	X,
	Y,
	Z,
};

enum class RenderingMode {
	POINT = 1,
	WIREFRAME = 2,
	VOLUME = 4,
	SMOOTH = 8,
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
	MainModel();

	void clear();

	void fitCamera() {
		camera.init();
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

	void createPreVolume(const T& factor) {
		preSurfaces.clear();
		preVolume = bakedVolume;
		preVolume.add(particle, factor);
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
		rendering.render(width, height, camera);
	}


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


	Math::Vector3d<T> getDiff(const Math::Vector3d<T>& src) {
		const T x =  src.getX();
		const T y = -src.getY();
		const T z =  src.getZ();
		if (planeMode == PlaneMode::XY) {
			return Vector3d<T>(x, y, 0);
		}
		else if (planeMode == PlaneMode::X) {
			return Vector3d<T>(x, 0, 0);
		}
		else if (planeMode == PlaneMode::Y) {
			return Vector3d<T>(0, x, 0);
		}
		else if (planeMode == PlaneMode::Z) {
			return Vector3d<T>(0, 0, x);
		}
		else {
			assert(false);
			return Vector3d<T>::Zero();
		}
	}

	void onDraggingLeft(const Math::Vector3d<T>& src)
	{
		const Math::Vector3d<T>& v = getDiff(src);
		if (uiMode == UIMode::CAMERA_TRANSLATE) {
			camera.move(v);
		}
		else if (uiMode == UIMode::PARTICLE_TRANSLATE) {
			particle.move(v);
			createPreVolume(1.0);
			const auto& s = createSurface(preVolume);
			setRendering();
		}
		else if (uiMode == UIMode::PARTICLE_STROKE) {
			particle.move(v);
			createPreVolume(1.0);
			const auto& s = createSurface(preVolume);
			setRendering();
			bakeParticleToVolume();
		}
	}

	void onDraggingRight(const Math::Vector3d<T>& src)
	{
		const Math::Vector3d<T>& v = getDiff(src);
		if (uiMode == UIMode::CAMERA_TRANSLATE) {
			camera.addAngle(src);
		}
		else if (uiMode == UIMode::PARTICLE_STROKE) {
			particle.move(v);
			createPreVolume(-1.0);
			const auto& s = createSurface(preVolume);
			setRendering();
			bakeParticleToVolume();
		}

	}

	void onDraggindMiddle(const Math::Vector3d<T>& diff)
	{
		if (uiMode == UIMode::CAMERA_TRANSLATE) {
			const Vector3d<T> v(0, 0, diff.getY());
			camera.move(v);
		}
		else {
			particle.addRadius(diff.getX());
			createPreVolume(1.0);
			const auto& s = createSurface(preVolume);
			createSurface(preVolume);
			setRendering();
		}
		/*
		else if (uiMode == PARTICLE_TRANSLATE) {
			const Vector3d<T> v(0, 0, diff.getX());
			particle.move(v);
		}
		*/

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

	void setUIMode(const UIMode m) { this->uiMode = m; }

	void setPlaneMode(const PlaneMode m) { this->planeMode = m; }

	PlaneMode getPlaneMode() const { return planeMode; }

	RenderingConfig<T> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<T>& config) { rendering.setConfig(config); }

	VolumeConfig<T> getVolumeConfig() const { return vConfig; }

	void setVolumeConfig(const VolumeConfig<T>& config) { vConfig = config; }

private:
	Graphics::Camera<T> camera;

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
	PlaneMode planeMode;
};

template<typename T>
using MainModelSPtr = std::shared_ptr < MainModel<T> > ;
	}
}

#endif