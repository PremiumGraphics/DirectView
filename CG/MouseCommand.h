#ifndef __CRYSTAL_UI_MOUSE_COMMAND_H__
#define __CRYSTAL_UI_MOUSE_COMMAND_H__

#include "../Math/Vector.h"
#include "../Graphics/Camera.h"
#include "../Math/Particle.h"

namespace Crystal {
	namespace UI {


class MouseCommand
{
public:
	MouseCommand(Graphics::Camera<float>& camera) :
		camera(camera)
	{}

	MouseCommand() = default;

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) = 0;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) = 0;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) = 0;

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

class CameraCommand : public MouseCommand
{
public:
	CameraCommand(Graphics::Camera<float>& camera) :
		MouseCommand(camera)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;
};

class ParticleCommand : public MouseCommand
{
public:

	ParticleCommand(Graphics::Camera<float>& camera, Math::Particle3d<float>& particle) :
		MouseCommand(camera),
		particle(particle)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

private:
	Math::Particle3d<float>& particle;
};

class ParticleScaleCommand : public MouseCommand
{
public:

	ParticleScaleCommand(Graphics::Camera<float>& camera, Math::Particle3d<float>& particle) :
		MouseCommand(camera),
		particle(particle)
	{}

	virtual void onDraggingLeft(const Math::Vector3d<float>& src) override;

	virtual void onDraggingRight(const Math::Vector3d<float>& src) override;

	virtual void onDraggingMiddle(const Math::Vector3d<float>& src) override;

private:
	Math::Particle3d<float>& particle;
};


	}
}

#endif