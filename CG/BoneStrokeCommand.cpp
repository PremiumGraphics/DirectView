#include <stdafx.h>
#include "BoneStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

BoneStrokeCommand::BoneStrokeCommand(Camera<float>& camera, Vector3d<float>& cursor, Volume3d<float>& volume) :
MouseOperationCommand(camera),
cursor(cursor),
volume(volume),
radius(0.5f),
density(0.1f),
doRealTimeBake(false)
{}


void BoneStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	endPosition = cursor;
	_doSurfaceConstruction = true;
	//particle.addRadius(src.getX());
}

void BoneStrokeCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	endPosition = cursor;
	cursor += (toCoord3d(v * 1));
}

void BoneStrokeCommand::onLeftButtonDown()
{
	startPosition = cursor;
}

void BoneStrokeCommand::onLeftButtonUp()
{
	endPosition = cursor;
	doRealTimeBake = true;
	_doSurfaceConstruction = true;
}
