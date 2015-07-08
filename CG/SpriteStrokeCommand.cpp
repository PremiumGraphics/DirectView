#include <stdafx.h>
#include "SpriteStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void SpriteStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	_doRealTimeBakeParticle = false;
}

void SpriteStrokeCommand::onDraggingRight(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	_doRealTimeBakeParticle = true;

}

void SpriteStrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	attribute.radius += toCoord3d(toScreenCoord2d(v)).getY();
	_doRealTimeBakeParticle = false;
}

void SpriteStrokeCommand::bake()
{
	const Particle3d<float>& particle = toParticle(cursor);
	volume.add(particle);
}