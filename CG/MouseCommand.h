#ifndef __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__
#define __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__

#include "../Math/Vector.h"
#include "../Math/Line.h"
#include "../Graphics/Camera.h"
#include "../Math/Particle.h"
#include "../Graphics/ScreenCoord.h"

namespace Crystal {
	namespace UI {

class PostEvent {
public:
	bool doPreview;
	bool doBakeBone;
};

class MouseOperationCommand
{
public:
	MouseOperationCommand(Graphics::Camera<float>& camera) :
		camera(camera),
		_doRealTimePreview(true),
		_doRealTimeBakeBone(false)
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

	/*
	bool doRealTimePreview() { return _doRealTimePreview; }

	bool doRealTimeBakeParticle() const { return _doRealTimeBakeParticle; }

	bool doRealTimeBakeBone() const { return _doRealTimeBakeBone; }
	*/

	PostEvent getPostEvent() {
		PostEvent e;
		e.doBakeBone = _doRealTimeBakeBone;
		e.doPreview = _doRealTimePreview;
		return e;
	}

	virtual bool doRefresh() { return true; }

	void setMousePosition(const Graphics::ScreenCoord& c) {
		this->mouseCoord = c;
	}

	Graphics::ScreenCoord getMousePosition() const {
		return mouseCoord;
	}


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
	bool _doRealTimeBakeBone;

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

	virtual bool doRefresh() { return false; }
};

class Cursor3dOperationCommand : public MouseOperationCommand
{
public:
	Cursor3dOperationCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor) :
		MouseOperationCommand(camera),
		cursor(cursor)//,
		//	_doRealTimeBake(false)
	{
		//_doRealTimePreview = false;
	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

private:
	Math::Vector3d<float>& cursor;
	//bool _doRealTimeBake;
};



class BrushScaleCommand : public MouseOperationCommand
{
public:

	BrushScaleCommand(Graphics::Camera<float>& camera, float& size) :
		MouseOperationCommand(camera),
		size(size)//,
		//	_doRealTimeBake(false)
	{
		//_doRealTimeBakeParticle = true;

	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	//virtual bool doRealTimeBake() override { return _doRealTimeBake; }

private:
	float& size;
	//bool _doRealTimeBake;
};



/*
class JointCreateCommand : public MouseOperationCommand
{
public:
	JointCreateCommand(Graphics::Camera<float>& camera, Math::Vector3d<float>& cursor) :
		MouseOperationCommand(camera),
		cursor(cursor)
	{}

private:
	Math::Vector3d<float>& cursor;
};
*/
	}
}

#endif