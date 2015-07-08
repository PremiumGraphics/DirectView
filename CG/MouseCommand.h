#ifndef __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__
#define __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__

#include "../Math/Vector.h"
#include "../Math/Line.h"
#include "../Graphics/Camera.h"
#include "../Math/Particle.h"
#include "../Graphics/ScreenCoord.h"

namespace Crystal {
	namespace UI {

class MouseOperationCommand
{
public:
	MouseOperationCommand(Graphics::Camera<float>& camera) :
		camera(camera),
		_doRealTimePreview(true)
	{}


	MouseOperationCommand() = default;

	virtual void onRightDoubleClicked(){};

	virtual void onLeftDoubleClicked(){};

	virtual void onLeftButtonDown(){};

	virtual void onLeftButtonUp(){};

	virtual void onRightButtonDown(){};

	virtual void onDraggingLeft(const Math::Vector3d<float>& src){};

	virtual void onDraggingRight(const Math::Vector3d<float>& src){};

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src){};

	virtual void doPost(){};

	virtual bool doRealTimePreview() const { return _doRealTimePreview; }


protected:
	Math::Vector3d<float> toScreenCoord2d(const Math::Vector3d<float>& src) {
		const float x = src.getX();
		const float y = -src.getY();
		const float z = src.getZ();
		return Math::Vector3d<float>(x, y, 0);
	}

	Math::Vector3d<float> toCoord3d(const Math::Vector3d<float>& src) const {
		Math::Matrix3d<float> m = camera.getRotationMatrix();
		return src * m;
		//const auto& pos = particle.getCenter() * m;
	}

	Graphics::Camera<float>& camera;
	bool _doRealTimePreview;

private:
	Graphics::ScreenCoord mouseCoord;
};

class CameraOperationCommand : public MouseOperationCommand
{
public:
	CameraOperationCommand(Graphics::Camera<float>& camera) :
		MouseOperationCommand(camera)
	{
		_doRealTimePreview = false;
	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual bool doRealTimePreview() const override  { return false; }

};
	}
}

#endif