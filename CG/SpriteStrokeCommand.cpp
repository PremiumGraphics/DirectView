#include <stdafx.h>
#include "SpriteStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void SpriteStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	_doRealTimeBakeParticle = true;
}

void SpriteStrokeCommand::onDraggingRight(const Vector3d<float>& v)
{
	attribute.radius += toCoord3d(toScreenCoord2d(v)).getX();
	_doRealTimeBakeParticle = false;
}

void SpriteStrokeCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	cursor += (toCoord3d(v * 1));
	_doRealTimeBakeParticle = true;
}

void SpriteStrokeCommand::bake()
{
	const Particle3d<float>& particle = toParticle(cursor);
	volume.add(particle);
}