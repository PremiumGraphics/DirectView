#include "MouseCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void CameraOperationCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	camera.move(v);
}
void CameraOperationCommand::onDraggingRight(const Vector3d<float>& src)
{
	//const Math::Vector3d<float>& v = getDiff(src);
	camera.addAngle(src);
}

void CameraOperationCommand::onDraggingMiddle(const Vector3d<float>& src)
{
	const Math::Vector3d<float> v(0, 0, src.getY());
	camera.move(v);
}

void ParticleOperationCommand::onDraggingLeft(const Vector3d<float>& src)
{
	//_doRealTimeBake = false;
	const Math::Vector3d<float>& v = getDiff(src);
	particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleOperationCommand::onDraggingRight(const Vector3d<float>& src)
{
	//_doRealTimeBake = true;
	//const Math::Vector3d<float>& v = getDiff(src);
	//particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleOperationCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleScaleCommand::onDraggingLeft(const Vector3d<float>& src)
{
	particle.addRadius( src.getX() );
}

void ParticleScaleCommand::onDraggingRight(const Vector3d<float>& src)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleScaleCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void BoneOperationCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	for (const auto& b : command.getBones()) {
		b->moveEnd(getScrennSpaceDiff(v * 1));
	}
	//particle.addRadius(src.getX());
}

void BoneOperationCommand::onDraggingRight(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	for (const auto& b : command.getBones()) {
		b->move(getScrennSpaceDiff(v * 1));
	}

	//particle.move(getScrennSpaceDiff(v * 1));
}

void BoneOperationCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void BoneOperationCommand::onRightDoubleClicked()
{

}

void BoneOperationCommand::onLeftDoubleClicked()
{

}
