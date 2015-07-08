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

void Cursor3dOperationCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d( toScreenCoord2d(v) );
}

void Cursor3dOperationCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	cursor += (toCoord3d(v * 1));
}

void BrushScaleCommand::onDraggingLeft(const Vector3d<float>& v)
{
	size += toCoord3d(toScreenCoord2d(v)).getX();
}

void BrushScaleCommand::onDraggingRight(const Vector3d<float>& src)
{
}

void BrushScaleCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
}
