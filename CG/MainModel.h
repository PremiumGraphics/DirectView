#ifndef __CRYSTAL_COMMAND_MAIN_MODEL_H__
#define __CRYSTAL_COMMAND_MAIN_MODEL_H__

#include "../Math/MarchingCube.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Bone.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "RenderingCommand.h"
#include "MouseCommand.h"
#include "BoneCommand.h"
#include "SurfaceCommand.h"
#include "VolumeCommand.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {

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
	CAMERA,
	PARTICLE,
	PARTICLE_SCALE,
	PARTICLE_ERASE,
	BONE_MOVE,
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

	void setupVolumes();

	/*
	void zeroPreVolume() {
		preSurfaces.clear();
		preVolume = bakedVolume;
		preVolume.setZero(particle);
		const auto& s = createSurface(preVolume);
		preSurfaces.push_back(s);
		setRendering();
	}
	*/

	void createPreVolume(const float factor);

	void bakeParticleToVolume();

	void doExport(const std::string& filename) const;

	void buildRenderer() {
		rendering.build();
	}

	void setParticleCharge(const float c) {
		particle.setCharge(c);
	}

	void createBone() {
		boneCommand.create();
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

	void changeNormal() {
		rendering.changeNormal();
	}


	void setRendering() {
		rendering.clear();
		//rendering.add(particle);
		rendering.add(volumeCommand.preVolume);
		for (const auto& s : surfaceCommand.getSurfaces() ) {
			rendering.add(*s);
		}
		for (const auto& b : boneCommand.getBones()) {
			rendering.add(*b);
		}
		/*
		for (const auto& s : bakedSurfaces) {
			rendering.add(*s);
		}
		*/
	}

	void preview() {
		if (mouse->getType() == UI::MouseOperationCommand::Type::Camera ) {
			return;
		}
		createPreVolume(1.0);
		surfaceCommand.create(volumeCommand.preVolume, vConfig.threshold);
		setRendering();
	}

	void onDraggingLeft(const Math::Vector3d<float>& src) {
		mouse->onDraggingLeft(src);
		preview();
	}

	void onDraggingRight(const Math::Vector3d<float>& src) {
		mouse->onDraggingRight(src);
		preview();
		if (mouse->getType() == UI::MouseOperationCommand::Type::Particle) {
			bakeParticleToVolume();
		}
	}

	void onRightDoubleClick() {
		bakeParticleToVolume();
	}

	void onDraggindMiddle(const Math::Vector3d<float>& diff) {
		mouse->onDraggingMiddle(diff);
		preview();
	}

	void setUIControl(const UIControl ctrl);

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
	UI::VolumeCommand volumeCommand;

	Math::Particle3d<float> particle;
	RenderingCommand rendering;
	VolumeConfig<float> vConfig;
	ParticleConfig<float> pConfig;
	std::shared_ptr<UI::MouseOperationCommand> mouse;
	UI::BoneCommand boneCommand;
	UI::SurfaceCommand surfaceCommand;
	bool isSphere;
};

using MainModelSPtr = std::shared_ptr < MainModel > ;
	}
}

#endif