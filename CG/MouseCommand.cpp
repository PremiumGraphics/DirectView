#include "stdafx.h"

#include "MouseCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void CameraCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	camera.move(v);
}
void CameraCommand::onDraggingRight(const Vector3d<float>& src)
{
	//const Math::Vector3d<float>& v = getDiff(src);
	camera.addAngle(src);
}

void CameraCommand::onDraggingMiddle(const Vector3d<float>& src)
{
	const Math::Vector3d<float> v(0, 0, src.getY());
	camera.move(v);
}

void ParticleCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleCommand::onDraggingRight(const Vector3d<float>& src)
{
	//const Math::Vector3d<float>& v = getDiff(src);
	//particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleCommand::onDraggingMiddle(const Vector3d<float>& diff)
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

void BoneCommand::onDraggingLeft(const Vector3d<float>& src)
{
	//particle.addRadius(src.getX());
}

void BoneCommand::onDraggingRight(const Vector3d<float>& src)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void BoneCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}