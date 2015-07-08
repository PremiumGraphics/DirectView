#include <stdafx.h>
#include "LineStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LineStrokeCommand::LineStrokeCommand(Camera<float>& camera, Vector3d<float>& cursor, Volume3d<float>& volume) :
MouseOperationCommand(camera),
cursor(cursor),
volume(volume),
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
	_doRealTimePreview = true;
	//particle.addRadius(src.getX());
}

void LineStrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	attr.radius += toCoord3d(toScreenCoord2d(v)).getY();
	_doRealTimePreview = true;
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
	_doRealTimePreview = true;
}

void LineStrokeCommand::doPost()
{
	if (!doRealTimeBake) {
		return;
	}
	const auto& line = getLine();
	const auto& positions = line.toPositionsByLength(attr.radius);
	for (const auto& p : positions) {
		volume.add(toParticle(p));
	}

}
