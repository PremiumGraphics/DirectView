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


void ParticleOperationCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
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
	cursor += (toCoord3d(v * 1));
}


void Line3dOperationCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));

	//particle.addRadius(src.getX());
}

void Line3dOperationCommand::onDraggingRight(const Vector3d<float>& src)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void Line3dOperationCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	cursor += (toCoord3d(v * 1));
}

void Line3dOperationCommand::onRightButtonDown()
{

}

void Line3dOperationCommand::onLeftButtonDown()
{
	startPosition = cursor;
}

void Line3dOperationCommand::onLeftButtonUp()
{
	endPosition = cursor;
	_doRealTimeBakeBone = true;
	_doRealTimePreview = true;
}
