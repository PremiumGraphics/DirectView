#include "stdafx.h"

#include "RenderingCommand.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Command;

RenderingCommand::RenderingCommand() :
wireframeRenderer(std::make_shared<WireframeRenderer>()),
pointRenderer(std::make_shared<PointRenderer>())
{

}


void RenderingCommand::build()
{
	normalRenderer.build();
	wireframeRenderer->build();
	smoothRenderer.build();
	volumeRenderer.build();
	pointRenderer->build();
}

void RenderingCommand::clear()
{
	normalRenderer.clear();
	pointRenderer->clear();
	wireframeRenderer->clear();
	smoothRenderer.clear();
	volumeRenderer.clear();
}

void RenderingCommand::set(const Crystal::UI::DisplayList& list)
{
	clear();
	for (const auto& l : list.getLines()) {
		add(l);
	}
	for (const auto& p : list.getParticles()) {
		add(p);
	}
	for (const auto& v : list.getVolumes()) {
		add(*v);
	}
	for (const auto& s : list.getSurfaces()) {
		add(*s);
	}
}

void RenderingCommand::add(const Particle3d<float>& particle)
{
	if (config.drawPoint) {
		pointRenderer->add(particle);
	}
	if (config.drawWire) {
		wireframeRenderer->add(particle);
	}
}

void RenderingCommand::add(const Surface<float>& surface)
{
	if (config.drawWire) {
		wireframeRenderer->add(surface);
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
		wireframeRenderer->add(volume);
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

void RenderingCommand::add(const Line3d<float>& line)
{
	if (config.drawWire) {
		wireframeRenderer->add(line);
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
		pointRenderer->render(width, height, camera);
	}

	if (config.drawWire) {
		wireframeRenderer->render(width, height, camera);
	}

	if (config.drawNormal) {
		normalRenderer.render(width, height, camera);
	}

	if (config.drawSmooth) {
		smoothRenderer.render(width, height, camera);
	}

	if (config.drawVolume) {
		glPointSize(getConfig().pointSize);
		volumeRenderer.render(width, height, camera);
	}
}
