#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "../Math/MarchingCube.h"
#include "../Math/Volume.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Bone.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "RenderingCommand.h"
#include "MouseCommand.h"
#include "SurfaceCommand.h"

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



enum class UIControl {
	CAMERA,
	CURSOR,
	PARTICLE_BAKE,
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

	void setVolume(const Math::Volume3d<float> v) { volume = v; }

	/*
	Math::Box<T> getBoundingBox() const {
		return Math::Box<T>(Math::Vector3d<T>(-1, -1, -1), Math::Vector3d<T>(1, 1, 1));
	}
	*/

	void bake(const Math::Line3d<float>& line);

	void doExport(const std::string& filename) const;

	void buildRenderer() {
		rendering.build();
	}

	/*
	void createBone() {
		boneCommand.create();
	}
	*/

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

	void setMousePosition(const Graphics::ScreenCoord& c) {
		mouse->setMousePosition(c);
	}

	Graphics::ScreenCoord getMousePosition() const {
		return mouse->getMousePosition();
	}

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

	void onLeftButtonDown() {
		mouse->onLeftButtonDown();
		postMouseEvent();
	}

	void onLeftButtonUp() {
		mouse->onLeftButtonUp();
		postMouseEvent();
	}

	void postMouseEvent();

	void setUIControl(const UIControl ctrl);

	//void setRealTimeBake(const bool b) { this->realTimeBake = b; }

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

	void setParticleCharge(const float c) { this->particleAttribute.charge = c; }

private:
	Graphics::Camera<float> camera;
	Math::Volume3d<float> volume;


	RenderingCommand rendering;
	Math::Volume3d<float>::Attribute vConfig;
	Math::Particle3d<float>::Attribute particleAttribute;
	std::shared_ptr<UI::MouseOperationCommand> mouse;
	Graphics::Bone<float> bone;
	UI::SurfaceCommand surfaceCommand;

	std::shared_ptr<UI::CameraOperationCommand> cameraOperation;
	std::shared_ptr<UI::Cursor3dOperationCommand> cursorOperation;
	std::shared_ptr<UI::Line3dOperationCommand> lineOperation;

	Math::Vector3d<float> cursor;
	bool isSphere;

	void setUpVolume();
};
	}
}

#endif