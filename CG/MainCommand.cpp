#include <stdafx.h>

#include "MainCommand.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

MainCommand::MainCommand() :
isSphere(false)
{
	cameraOperation = std::make_shared<UI::CameraOperationCommand>(camera);
	cursorOperation = std::make_shared<UI::Cursor3dOperationCommand>(camera, cursor);
	lineOperation = std::make_shared<UI::Line3dOperationCommand>(camera, boneCommand, cursor);
	mouse = cameraOperation;
	volumeCommand.setupVolumes(vConfig);
	//createPreVolume(1.0);
	surfaceCommand.create(volumeCommand.getPreVolume(), vConfig.threshold);
	setRendering();
}

void MainCommand::clear()
{
	volumeCommand.clear();
	surfaceCommand.clear();
	boneCommand.clear();
	//bakedSurfaces.clear();
}

void MainCommand::doExport(const std::string& filename) const
{
	IO::STLFile file;

	IO::STLCellVector cells;
	for (const auto& s : surfaceCommand.getSurfaces()) {
		for (const auto& f : s->getFaces()) {
			Math::Vector3dVector<float> positions;
			for (const auto& e : f->getEdges()) {
				positions.push_back(e->getStartPosition());
			}
			const auto normal = f->getNormal();
			IO::STLCell cell(positions, normal);
			cells.push_back(cell);
		}
	}

	file.setTitle("TestTitle");
	file.setCells(cells);
	file.writeASCII(filename);
}

void MainCommand::bakeBoneToVolume()
{
	surfaceCommand.clear();
	for (const auto& b : boneCommand.getBones()) {
		const auto& positions = b->getLine().toPositions(10);
		std::list<Particle3d<float>> boneParticles;
		for (const auto& p : positions) {
			Particle3d<float> particle(p, 0.5f, 1.0f);
			boneParticles.emplace_back(particle);
		}
		volumeCommand.copyBakedToPre();
		volumeCommand.add(boneParticles, 1.0f);
		surfaceCommand.create(volumeCommand.getPreVolume(), vConfig.threshold);
	}
	setRendering();
}

void MainCommand::bakeParticleToVolume()
{
	volumeCommand.bake();
	surfaceCommand.create(volumeCommand.getBakedVolume(), vConfig.threshold);
	setRendering();
}

void MainCommand::setRendering()
{
	rendering.clear();
	rendering.add(cursor);
	rendering.add(volumeCommand.getPreVolume());
	for (const auto& s : surfaceCommand.getSurfaces()) {
		rendering.add(*s);
	}
	for (const auto& b : boneCommand.getBones()) {
		rendering.add(*b);
	}
	/*
	for (const auto& s : bakedSurfaces) {
	rendering.add(*s);
	}
	*/
}


void MainCommand::preview()
{
	//createPreVolume(1.0);
	surfaceCommand.clear();
	volumeCommand.copyBakedToPre();
	Particle3d<float> particle(cursor, 1.0f, 1.0f);
	volumeCommand.add(particle, 0.1f);
	surfaceCommand.create(volumeCommand.getPreVolume(), vConfig.threshold);
	setRendering();
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
	/*
	else if (ctrl == UIControl::PARTICLE_SCALE) {
		mouse = std::make_shared<UI::ParticleScaleCommand>(camera, particle);
	}
	*/
	else if (ctrl == UIControl::BONE_MOVE) {
		lineOperation = std::make_shared<UI::Line3dOperationCommand>(camera, boneCommand, cursor);
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
		preview();
		bakeParticleToVolume();
		return;
	}
	if (e.doBakeBone) {
		boneCommand.create(lineOperation->getLine().getStart(), lineOperation->getLine().getEnd());
		preview();
		bakeBoneToVolume();
		return;
	}
	if (e.doPreview) {
		preview();
	}
}
