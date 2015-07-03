#include <stdafx.h>

#include "MainCommand.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

MainCommand::MainCommand()
{
	mc.buildTable();

	cameraOperation = std::make_shared<UI::CameraOperationCommand>(camera);
	cursorOperation = std::make_shared<UI::Cursor3dOperationCommand>(camera, cursor);
	lineOperation = std::make_shared<UI::Line3dOperationCommand>(camera, cursor);
	mouse = cameraOperation;
	Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
	Volume3d<float> v(vConfig.space, grid);
	volume = v;
	//createPreVolume(1.0);
	//surfaceCommand.create(v, 0.5);
	setRendering();
}

void MainCommand::clear()
{
	//volumeCommand.clear();
	volume.setValue(0.0f);
	//bakedSurfaces.clear();
}

void MainCommand::doExport(const std::string& filename) const
{
	IO::STLFile file;

	IO::STLCellVector cells;
	const auto& surface = toSurface(volume, 0.5f);
	for (const auto& f : surface->getFaces()) {
		Math::Vector3dVector<float> positions;
		for (const auto& e : f->getEdges()) {
			positions.push_back(e->getStartPosition());
		}
		const auto normal = f->getNormal();
		IO::STLCell cell(positions, normal);
		cells.push_back(cell);
	}

	file.setTitle("TestTitle");
	file.setCells(cells);
	file.writeASCII(filename);
}


void MainCommand::setRendering( const Surface<float>& s)
{
	rendering.clear();
	rendering.add( toParticle(cursor) );
	rendering.add(volume);
	rendering.add(s);
}

void MainCommand::setRendering()
{
	rendering.clear();
	rendering.add(toParticle(cursor));
	rendering.add(volume);
	const auto& s = toSurface(volume, 0.5);
	rendering.add(*s);
}



void MainCommand::setUIControl(const UIControl ctrl)
{
	if (ctrl == UIControl::CAMERA) {
		mouse = cameraOperation;
	}
	else if (ctrl == UIControl::CURSOR) {
		mouse = cursorOperation;
	}
	else if (ctrl == UIControl::PARTICLE_BAKE) {
		mouse = std::make_shared<UI::ParticleOperationCommand>(camera, cursor);
	}
	else if (ctrl == UIControl::PARTICLE_SCALE) {
		mouse = std::make_shared<UI::ParticleScaleCommand>(camera, particleAttribute.radius);
	}
	else if (ctrl == UIControl::BONE_MOVE) {
		lineOperation = std::make_shared<UI::Line3dOperationCommand>(camera, cursor);
		mouse = lineOperation;
	}
	else {
		assert(false);
	}
}

void MainCommand::postMouseEvent()
{
	if (!mouse->doRefresh()){
		return;
	}
	const UI::PostEvent& e = mouse->getPostEvent();
	if (e.doBakeParticle) {
		const Particle3d<float>& particle = toParticle(cursor);
		volume.add(particle, 0.1f);
		const auto& s = toSurface(volume, 0.5);
		setRendering(*s);
		return;
	}
	if (e.doBakeBone) {
		const auto& line = lineOperation->getLine();
		const auto& positions = line.toPositions(10);
		for (const auto& p : positions) {
			volume.add(toParticle(p), 1.0f);
		}
		const auto& s = toSurface(volume, 0.5);
		setRendering(*s);
		return;
	}
	if (e.doPreview) {
		const auto& s = toSurface(volume, 0.5);
		setRendering(*s);
	}
}


SurfaceSPtr<float> MainCommand::toSurface(const Volume3d<float>& ss, const float threshold) const
{
	auto surface = std::make_shared< Surface<float> >();
	const auto& triangles = mc.march(ss, threshold);//vConfig.threshold);

	for (const auto& t : triangles) {
		surface->add(t, Graphics::ColorRGBA<float>::Blue());
	}
	return surface;
}
