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
		Math::Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
		Math::Volume3d<float> v(vConfig.space, grid);
		preVolume = v;
		bakedVolume = v;
	}

	void createPreVolume(const float& factor) {
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

	Graphics::SurfaceSPtr<float> createSurface(const Math::Volume3d<float>& ss)
	{
		const auto& triangles = mc.march(ss, vConfig.threshold);

		Graphics::SurfaceSPtr<float> surface = std::make_shared<Graphics::Surface<float> >();
		for (const auto t : triangles) {
			surface->add(t, Graphics::ColorRGBA<float>::Blue());
		}
		return surface;
	}

	void doExport(const std::string& filename) const;

	void buildRenderer() {
		rendering.buildRenderer();
	}

	void reverseParticleCharge() {
		particle.reverseCharge();
	}


	void render(const int width, const int height) {
		rendering.render(width, height, camera);
	}

	/*
	void changeRenderingPoint() {
		rendering.getConfig().drawPoints();
	}
	*/

	void changePoint() {
		rendering.changePoint();
	}

	void changeWireframe() {
		rendering.changeWire();
	}

	void changeRenderingVolume() {
		rendering.changeVolume();
	}

	void changeRenderingSmooth() {
		rendering.changeSmooth();
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


	Math::Vector3d<float> getDiff(const Math::Vector3d<float>& src) {
		const float x =  src.getX();
		const float y = -src.getY();
		const float z =  src.getZ();
		if (planeMode == PlaneMode::XY) {
			return Math::Vector3d<float>(x, y, 0);
		}
		else if (planeMode == PlaneMode::X) {
			return Math::Vector3d<float>(x, 0, 0);
		}
		else if (planeMode == PlaneMode::Y) {
			return Math::Vector3d<float>(0, x, 0);
		}
		else if (planeMode == PlaneMode::Z) {
			return Math::Vector3d<float>(0, 0, x);
		}
		else {
			assert(false);
			return Math::Vector3d<float>::Zero();
		}
	}

	void onDraggingLeft(const Math::Vector3d<float>& src)
	{
		const Math::Vector3d<float>& v = getDiff(src);
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

	void onDraggingRight(const Math::Vector3d<float>& src)
	{
		const Math::Vector3d<float>& v = getDiff(src);
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

	void onDraggindMiddle(const Math::Vector3d<float>& diff)
	{
		if (uiMode == UIMode::CAMERA_TRANSLATE) {
			const Math::Vector3d<float> v(0, 0, diff.getY());
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
			const Vector3d<float> v(0, 0, diff.getX());
			particle.move(v);
		}
		*/

	}

	/*
	void addParticleCharge(const float delta) {
		particle.addCharge(delta);
	}
	*/


/*	void addParticleRadius(const float delta) {
		particle
	}
	*/

	void setUIMode(const UIMode m) { this->uiMode = m; }

	void setPlaneMode(const PlaneMode m) { this->planeMode = m; }

	PlaneMode getPlaneMode() const { return planeMode; }

	RenderingConfig<float> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<float>& config) { rendering.setConfig(config); }

	VolumeConfig<float> getVolumeConfig() const { return vConfig; }

	void setVolumeConfig(const VolumeConfig<float>& config) { vConfig = config; }

private:
	Graphics::Camera<float> camera;

	Math::Volume3d<float> preVolume;
	Math::Volume3d<float> bakedVolume;
	//Math::Volume3d<float> volume;

	Math::Particle3d<float> particle;
	RenderingCommand<float> rendering;
	Math::MarchingCube<float> mc;
	Graphics::SurfaceSPtrList<float> preSurfaces;
	//Graphics::SurfaceSPtrList<float> bakedSurfaces;
	UIMode uiMode;
	VolumeConfig<float> vConfig;
	ParticleConfig<float> pConfig;
	PlaneMode planeMode;
};

using MainModelSPtr = std::shared_ptr < MainModel > ;
	}
}

#endif