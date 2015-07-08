#ifndef __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__
#define __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__

#include "../Math/Vector.h"
#include "../Math/Line.h"
#include "../Graphics/Camera.h"
#include "../Math/Particle.h"
#include "../Graphics/ScreenCoord.h"
#include "DisplayList.h"

namespace Crystal {
	namespace UI {

class MouseOperationCommand
{
public:
	MouseOperationCommand(Graphics::Camera<float>& camera) :
		camera(camera)
	{}


	MouseOperationCommand() = default;

	virtual void onRightDoubleClicked(){};

	virtual void onLeftDoubleClicked(){};

	virtual void onLeftButtonDown(){};

	virtual void onLeftButtonUp(){};

	virtual void onRightButtonDown(){};

	virtual void onRightButtonUp(){};

	virtual void onDraggingLeft(const Math::Vector3d<float>& src){};

	virtual void onDraggingRight(const Math::Vector3d<float>& src){};

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src){};

	virtual bool doSurfaceConstruction() const { return false; }

	virtual bool doBakeParticlesToVolume() const { return false; }

	virtual bool doRefresh() const { return true; }

	virtual DisplayList getDisplayList() const { return DisplayList(); }

	virtual std::vector<Math::Particle3d<float> > getParticles() const { return std::vector < Math::Particle3d<float> >(); }

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

private:
	Graphics::ScreenCoord mouseCoord;
};

class CameraOperationCommand : public MouseOperationCommand
{
public:
	CameraOperationCommand(Graphics::Camera<float>& camera) :
		MouseOperationCommand(camera)
	{
	}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual bool doRefresh() const override { return false; }

};
	}
}

#endif