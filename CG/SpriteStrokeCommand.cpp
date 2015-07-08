#include <stdafx.h>
#include "SpriteStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void SpriteStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
}

void SpriteStrokeCommand::onDraggingRight(const Vector3d<float>& src)
{
	;
}

void SpriteStrokeCommand::onDraggingMiddle(const Vector3d<float>& diff)
{
	const Math::Vector3d<float> v(0, 0, diff.getY());
	cursor += (toCoord3d(v * 1));
}

void SpriteStrokeCommand::bake()
{
	const Particle3d<float>& particle = toParticle(cursor);
	volume.add(particle);
}