#ifndef __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__
#define __CRYSTAL_UI_MOUSE_OPERATION_COMMAND_H__

#include "../Math/Vector.h"
#include "../Graphics/Camera.h"
#include "../Graphics/Bone.h"
#include "../Math/Particle.h"

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

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) = 0;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) = 0;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) = 0;

	virtual bool doRealTimePreview() { return true; }

	virtual bool doRealTimeBake() { return false; }

	virtual bool doRefresh() { return true; }

protected:
	Math::Vector3d<float> getDiff(const Math::Vector3d<float>& src) {
		const float x = src.getX();
		const float y = -src.getY();
		const float z = src.getZ();
		return Math::Vector3d<float>(x, y, 0);
	}

	Math::Vector3d<float> getScrennSpaceDiff(const Math::Vector3d<float>& src) const {
		Math::Matrix3d<float> m = camera.getRotationMatrix();
		return src * m;
		//const auto& pos = particle.getCenter() * m;
	}

	Graphics::Camera<float>& camera;
};

class CameraOperationCommand : public MouseOperationCommand
{
public:
	CameraOperationCommand(Graphics::Camera<float>& camera) :
		MouseOperationCommand(camera)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual bool doRealTimePreview() override { return false; }

	virtual bool doRefresh() { return false; }


};

class ParticleOperationCommand : public MouseOperationCommand
{
public:

	ParticleOperationCommand(Graphics::Camera<float>& camera, Math::Particle3d<float>& particle) :
		MouseOperationCommand(camera),
		particle(particle)//,
	//	_doRealTimeBake(false)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	//virtual bool doRealTimeBake() override { return _doRealTimeBake; }


private:
	Math::Particle3d<float>& particle;
	//bool _doRealTimeBake;
};

class ParticleScaleCommand : public MouseOperationCommand
{
public:

	ParticleScaleCommand(Graphics::Camera<float>& camera, Math::Particle3d<float>& particle) :
		MouseOperationCommand(camera),
		particle(particle)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;


private:
	Math::Particle3d<float>& particle;
};

class BoneOperationCommand : public MouseOperationCommand
{
public:
	BoneOperationCommand(Graphics::Camera<float>& camera, const Graphics::BoneSPtrList<float>& bones) :
		MouseOperationCommand(camera),
		bones( bones )
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

	virtual void onRightDoubleClicked() override;

private:
	Graphics::BoneSPtrList<float> bones;
};
	}
}

#endif