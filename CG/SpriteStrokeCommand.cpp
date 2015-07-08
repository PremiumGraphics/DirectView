#include <stdafx.h>
#include "SpriteStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void SpriteStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	_doRealTimeBake = false;
}

void SpriteStrokeCommand::onDraggingRight(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	_doRealTimeBake = true;

}

void SpriteStrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	radius += toCoord3d(toScreenCoord2d(v)).getY();
	_doRealTimeBake = false;
}
