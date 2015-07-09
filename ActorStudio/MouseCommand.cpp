#include "stdafx.h"
#include "MouseCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

void CameraOperationCommand::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = toScreenCoord2d(src);
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
