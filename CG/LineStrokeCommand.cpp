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
	endPosition = cursor;
	_doRealTimePreview = true;
	//particle.addRadius(src.getX());
}

void LineStrokeCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	endPosition = cursor;
	cursor += (toCoord3d(v * 1));
}

void LineStrokeCommand::onLeftButtonDown()
{
	startPosition = cursor;
}

void LineStrokeCommand::onLeftButtonUp()
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
	const auto& positions = line.toPositions(10);
	for (const auto& p : positions) {
		volume.add(toParticle(p));
	}

}
