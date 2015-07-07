#ifndef __CRYSTAL_COMMAND_MAIN_COMMAND_H__
#define __CRYSTAL_COMMAND_MAIN_COMMAND_H__

#include "../Math/MarchingCube.h"
#include "../Math/Volume.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Surface.h"
#include "../Util/UnCopyable.h"
#include "../IO/STLFile.h"

#include "RenderingCommand.h"
#include "MouseCommand.h"

#include <memory>
#include <map>

namespace Crystal {
	namespace Command {

enum class UIControl {
	CAMERA,
	CURSOR,
	SPRITE_STROKE,
	LINE_STROKE,
	BRUSH_SCALE,
	PARTICLE_ERASE,
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

	void doExport(const std::string& filename) const;

	void buildRenderer() {
		rendering.build();
	}

	void render(const int width, const int height) {
		rendering.render(width, height, camera);
	}

	void setRendering(const Graphics::Surface<float>& s);

	void setRendering();

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

	void setUIControl(const UIControl ctrl);

	RenderingConfig<float> getRenderingConfig() const { return rendering.getConfig(); }

	void setRenderingConfig(const RenderingConfig<float>& config) { rendering.setConfig(config); }

	void setParticleCharge(const float c) { this->particleAttribute.charge = c; }

	void setParticleRadius(const float radius) { this->particleAttribute.radius = radius; }

private:

	Graphics::Camera<float> camera;
	Math::Volume3d<float> volume;


	RenderingCommand rendering;
	Math::Volume3d<float>::Attribute vConfig;
	Math::Particle3d<float>::Attribute particleAttribute;
	std::shared_ptr<UI::MouseOperationCommand> mouse;

	std::shared_ptr<UI::CameraOperationCommand> cameraOperation;
	std::shared_ptr<UI::Cursor3dOperationCommand> cursorOperation;
	std::shared_ptr<UI::LineStrokeCommand> lineOperation;

	Math::Vector3d<float> cursor;

	Math::MarchingCube<float> mc;

	void postMouseEvent();

	Math::Particle3d<float> toParticle(const Math::Vector3d<float>& pos) const {
		return Math::Particle3d<float>(pos, particleAttribute);
	}

	Graphics::SurfaceSPtr<float> toSurface(const Math::Volume3d<float>& ss, const float threshold) const;

};
	}
}

#endif