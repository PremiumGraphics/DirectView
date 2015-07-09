#include <stdafx.h>
#include "LineStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;

LineStrokeCommand::LineStrokeCommand(Camera<float>& camera, Vector3d<float>& cursor) :
MouseOperationCommand(camera),
cursor(cursor),
radius(0.5f),
density(1.0f),
doRealTimeBake(false)
{}


void LineStrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	cursor += toCoord3d(toScreenCoord2d(v));
	endPosition = cursor;
	doRealTimeBake = false;
	_doSurfaceConstruction = false;
}

void LineStrokeCommand::onDraggingRight(const Vector3d<float>& v)
{

	cursor += toCoord3d(toScreenCoord2d(v));
	doRealTimeBake = false;
	_doSurfaceConstruction = false;

	//particle.addRadius(src.getX());
}

void LineStrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	radius += toCoord3d(toScreenCoord2d(v)).getY();
	_doSurfaceConstruction = false;
	doRealTimeBake = false;

}

void LineStrokeCommand::onLeftButtonDown()
{
	startPosition = cursor;
	doRealTimeBake = false;
	_doSurfaceConstruction = false;
}

void LineStrokeCommand::onLeftButtonUp()
{
	endPosition = cursor;
	doRealTimeBake = true;
	_doSurfaceConstruction = true;
}

std::vector<Particle3d<float> > LineStrokeCommand::getParticles() const
{
	std::vector<Particle3d<float> > particles;
	const auto& positions = getLine().toPositionsByLength(radius);
	for (const auto& p : positions) {
		particles.push_back(toParticle(p));
	}
	return particles;
}
