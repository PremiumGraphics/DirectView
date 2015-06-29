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
void CameraCommand::onDragginRight(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	camera.addAngle(v);
}

void CameraCommand::onDragginMiddle(const Vector3d<float>& src)
{
	const Math::Vector3d<float> v(0, 0, src.getY());
	camera.move(v);
}

void ParticleCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleCommand::onDragginRight(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	particle.move(getScrennSpaceDiff(v * 1));
}

void ParticleCommand::onDragginMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	particle.move(getScrennSpaceDiff(v * 1));
}
