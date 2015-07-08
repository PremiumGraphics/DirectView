#include <stdafx.h>
#include "BoneStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

BoneStrokeCommand::BoneStrokeCommand(Camera<float>& camera, Vector3d<float>& cursor, Volume3d<float>& volume) :
MouseOperationCommand(camera),
cursor(cursor),
volume(volume),
doRealTimeBake(false)
{}


void BoneStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	endPosition = cursor;
	_doRealTimePreview = true;
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
	_doRealTimePreview = true;
}

void BoneStrokeCommand::doPost()
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
