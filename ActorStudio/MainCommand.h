#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "../Math/MarchingCube.h"
#include "../Math/Volume.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Surface.h"
#include "../Util/UnCopyable.h"
#include "../ActorTest/Actor.h"

#include "RenderingCommand.h"
#include "MouseCommand.h"
#include "LineStrokeCommand.h"

#include "DisplayList.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {

enum class UIControl {
	CAMERA,
	LINE_STROKE,
	PARTICLE_ERASE,
	BONE_STROKE,
};

class MainCommand final : private UnCopyable
{
public:
	MainCommand();

	void clear();

	void fitCamera() {
		camera.init();
	}

	Graphics::Camera<float>* getCamera() { return &camera; }

	void setVolume(const Math::Volume3dSPtr<float>& v) { volume = v; }

	void doExport(const std::string& filename) const;

	void buildRenderer() {
		rendering.build();
	}

	void render(const int width, const int height) {
		rendering.render(width, height, camera);
	}

	void setRendering();

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

	void onLeftDoubleClick() {
		mouse->onLeftDoubleClicked();
		postMouseEvent();
	}

	void onMoving(const Math::Vector3d<float>& v) {
		//mouse->onMoving(v);
		//postMouseEvent();
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

	void onRightButtonDown() {
		mouse->onRightButtonDown();
		postMouseEvent();
	}

	void onRightButtonUp() {
		mouse->onRightButtonUp();
		postMouseEvent();
	}


	void setUIControl(const UIControl ctrl);

	RenderingConfig<float> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<float>& config) { rendering.setConfig(config); }

	//void setParticleCharge(const float c) { this->spriteStrokeCommand->particleAttribute.charge = c; }

	//void setParticleRadius(const float radius) { this->spriteStrokeCommand->particleAttribute.radius = radius; }


private:

	Graphics::Camera<float> camera;
	Math::Volume3dSPtr<float> volume;

	RenderingCommand rendering;
	Math::Volume3d<float>::Attribute vConfig;
	std::shared_ptr<UI::MouseOperationCommand> mouse;

	std::shared_ptr<UI::CameraOperationCommand> cameraOperation;
	std::shared_ptr<UI::LineStrokeCommand> lineOperation;
	std::shared_ptr<UI::LineStrokeCommand> boneOperation;

	Actor::Skeleton<float> skeleton;

	Math::Vector3d<float> cursor;

	Math::MarchingCube<float> mc;
	Graphics::SurfaceSPtr<float> surface;

	UI::DisplayList dispList;

	void postMouseEvent();

	void buildSurface(const Math::Volume3d<float>& ss, const float threshold);

};
	}
}

#endif