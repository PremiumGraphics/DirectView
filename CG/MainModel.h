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

class MainCommand final : private UnCopyable
{
public:
	MainCommand();

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

	void setRendering();

	void preview();

	/*
	bool doRealtimePreview() {
		mouse->getType() == UI::MouseOperationCommand::Ty
	}
	*/

	void onDraggingLeft(const Math::Vector3d<float>& src) {
		mouse->onDraggingLeft(src);
		postMouseEvent();
	}

	void onDraggingRight(const Math::Vector3d<float>& src) {
		mouse->onDraggingRight(src);
		postMouseEvent();
	}

	void onRightDoubleClick() {
		mouse->onRightDoubleClicked();
		postMouseEvent();
	}

	void onDraggindMiddle(const Math::Vector3d<float>& diff) {
		mouse->onDraggingMiddle(diff);
		postMouseEvent();
	}

	void postMouseEvent() {
		if (realTimeBake) {
			preview();
			bakeParticleToVolume();
		}
		else if (mouse->doRealTimePreview()) {
			preview();
		}
	}

	void setUIControl(const UIControl ctrl);

	void setRealTimeBake(const bool b) { this->realTimeBake = b; }

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

	UI::VolumeConfig<float> getVolumeConfig() const { return vConfig; }

	void setVolumeConfig(const UI::VolumeConfig<float>& config) { vConfig = config; }

private:
	Graphics::Camera<float> camera;
	UI::VolumeCommand volumeCommand;

	Math::Particle3d<float> particle;
	RenderingCommand rendering;
	UI::VolumeConfig<float> vConfig;
	ParticleConfig<float> pConfig;
	std::shared_ptr<UI::MouseOperationCommand> mouse;
	UI::BoneCommand boneCommand;
	UI::SurfaceCommand surfaceCommand;
	bool isSphere;
	bool realTimeBake;
};
	}
}

#endif