#include <stdafx.h>
#include "LineStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void LineStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	endPosition = cursor;
	_doRealTimePreview = true;
	//particle.addRadius(src.getX());
}

void LineStrokeCommand::onDraggingRight(const Vector3d<float>& src)
{
	//particle.move(getScrennSpaceDiff(v * 1));
}

void LineStrokeCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	endPosition = cursor;
	cursor += (toCoord3d(v * 1));
}

void LineStrokeCommand::onRightButtonDown()
{

}

void LineStrokeCommand::onLeftButtonDown()
{
	startPosition = cursor;
}

void LineStrokeCommand::onLeftButtonUp()
{
	endPosition = cursor;
	_doRealTimeBakeBone = true;
	_doRealTimePreview = true;
}
