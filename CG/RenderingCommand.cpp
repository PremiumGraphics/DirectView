#include "stdafx.h"

#include "RenderingCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

void RenderingCommand::build()
{
	normalRenderer.build();
	wireframeRenderer.build();
	smoothRenderer.build();
	volumeRenderer.build();
	pointRenderer.build();
}

void RenderingCommand::clear()
{
	pointRenderer.clear();
	//selectedPointBuffer.clear();
	wireframeRenderer.clear();
	smoothRenderer.clear();
	volumeRenderer.clear();
}

void RenderingCommand::add(const Surface<float>& surface)
{
	if (config.drawWire) {
		wireframeRenderer.add(surface);
	}
	if (config.drawNormal) {
		normalRenderer.add(surface);
	}
	if (config.drawSmooth) {
		smoothRenderer.add(surface);
	}
}

void RenderingCommand::add(const Volume3d<float>& volume)
{
	if (config.drawWire) {
		wireframeRenderer.add(volume);
	}
	/*
	if (config.drawCells) {
		addCells(volume);
	}
	*/
	if (config.drawVolume) {
		volumeRenderer.add(volume);
	}
}


void RenderingCommand::render(const int width, const int height, const Camera<float>& camera)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPointSize(20.0);
	glLineWidth(getConfig().lineWidth);

	if (config.drawPoint) {
		pointRenderer.render(width, height, camera, false);
	}

	if (config.drawWire) {
		wireframeRenderer.render(width, height, camera, false);
	}

	if (config.drawNormal) {
		normalRenderer.render(width, height, camera);
	}

	if (config.drawSmooth) {
		smoothRenderer.render(width, height, camera);
	}

	//glClear(GL_DEPTH_BUFFER_BIT);
	//pointRenderer.render(width, height, camera, selectedPointBuffer, true);
	//wireframeRenderer.render(width, height, camera, triangleBuffer);

	glPointSize(getConfig().pointSize);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);

	if (config.drawVolume) {
		volumeRenderer.render(width, height, camera);
	}

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
}