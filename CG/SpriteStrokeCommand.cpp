#include <stdafx.h>
#include "SpriteStrokeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::UI;


void StrokeCommand::onDraggingLeft(const Vector3d<float>& v)
{
	brush->move( toCoord3d(toScreenCoord2d(v)) );
	_doRealTimeBake = true;
	_doSurfaceConstruct = true;
}

void StrokeCommand::onDraggingRight(const Vector3d<float>& v)
{
	brush->move( toCoord3d(toScreenCoord2d(v)) );
	_doRealTimeBake = false;
	_doSurfaceConstruct = false;
}

void StrokeCommand::onWheel(const float delta)
{
	brush->move(toCoord3d(Vector3d<float>(0,0,delta)));
	_doRealTimeBake = false;
	_doSurfaceConstruct = false;

}


void StrokeCommand::onDraggingMiddle(const Vector3d<float>& v)
{
	brush->addSize(toCoord3d(toScreenCoord2d(v)));
	_doRealTimeBake = false;
	_doSurfaceConstruct = false;
}

DisplayList StrokeCommand::getDisplayList() const
{
	Graphics::DisplayList list;
	list.add(brush);
	return list;
}