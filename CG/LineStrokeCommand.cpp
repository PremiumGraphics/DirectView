#include <stdafx.h>
#include "LineStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LineStrokeCommand::LineStrokeCommand(Camera<float>& camera, Vector3d<float>& cursor, Volume3dSPtr<float>& volume) :
MouseOperationCommand(camera),
cursor(cursor),
volume(volume),
radius(0.5f),
density(1.0f),
doRealTimeBake(false)
{}


void LineStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	doRealTimeBake = false;
}


void LineStrokeCommand::onDraggingRight(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	endPosition = cursor;
	_doSurfaceConstruction = true;
	//particle.addRadius(src.getX());
}

void LineStrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	radius += toCoord3d(toScreenCoord2d(v)).getY();
	_doSurfaceConstruction = true;
	doRealTimeBake = false;
}

void LineStrokeCommand::onRightButtonDown()
{
	startPosition = cursor;
	doRealTimeBake = false;

}

void LineStrokeCommand::onRightButtonUp()
{
	endPosition = cursor;
	doRealTimeBake = true;
	_doSurfaceConstruction = true;
}

void LineStrokeCommand::doPost()
{
	if (!doRealTimeBake) {
		return;
	}
	const auto& line = getLine();

	const auto& positions = line.toPositionsByLength(radius);
	for (const auto& p : positions) {
		volume->add(toParticle(p));
	}

}
