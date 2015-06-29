#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Camera.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "RenderingCommand.h"
#include "MouseCommand.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Model {

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

enum class UIControl {
	Camera,
	Particle,
	ParticleScale,
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

	void setParticleCharge(const float c) {
		particle.setCharge(c);
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


	
	Math::Vector3d<float> getScrennSpaceDiff(const Math::Vector3d<float>& src) const {
		Math::Matrix3d<float> m = camera.getRotationMatrix();
		return src * m;
		//const auto& pos = particle.getCenter() * m;
	}

	void preview() {
		if (!realtimePreviewMode) {
			return;
		}
		createPreVolume(1.0);
		const auto& s = createSurface(preVolume);
		setRendering();
		if (doRealTimeBaking) {
			bakeParticleToVolume();
		}
	}

	void onDraggingLeft(const Math::Vector3d<float>& src) {
		mouse->onDraggingLeft(src);
		preview();
	}

	void onDraggingRight(const Math::Vector3d<float>& src) {
		mouse->onDraggingRight(src);
		preview();
	}

	void onDraggindMiddle(const Math::Vector3d<float>& diff) {
		mouse->onDraggingMiddle(diff);
		preview();
	}

	void setUIControl(const UIControl ctrl)
	{
		if (ctrl == UIControl::Camera) {
			mouse = std::make_shared<UI::CameraCommand>(camera);
			realtimePreviewMode = false;
		}
		else if( ctrl == UIControl::Particle ) {
			mouse = std::make_shared<UI::ParticleCommand>(camera, particle);
			realtimePreviewMode = true;
		}
		else if (ctrl == UIControl::ParticleScale) {
			mouse = std::make_shared<UI::ParticleScaleCommand>(camera, particle);
			realtimePreviewMode = true;
		}
	}

	void changeRealTimeBaking(const bool b) {
		doRealTimeBaking = b;
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
	VolumeConfig<float> vConfig;
	ParticleConfig<float> pConfig;
	std::shared_ptr<UI::MouseCommand> mouse;
	bool realtimePreviewMode;
	bool doRealTimeBaking;
};

using MainModelSPtr = std::shared_ptr < MainModel > ;
	}
}

#endif