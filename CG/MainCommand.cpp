#include <stdafx.h>

#include "MainCommand.h"
#include "../IO/STLFile.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

MainCommand::MainCommand()
{
	mc.buildTable();

	Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
	//Volume3d<float> v(vConfig.space, grid);
	volume = std::make_shared< Volume3d<float> >(vConfig.space, grid);

	surface = std::make_shared< Surface<float> >();

	cameraOperation = std::make_shared<UI::CameraOperationCommand>(camera);
	spriteStrokeCommand = std::make_shared<SpriteStrokeCommand>(camera);
	//boneOperation = std::make_shared<UI::LineStrokeCommand>(camera, cursor);

	mouse = cameraOperation;
	//createPreVolume(1.0);
	//surfaceCommand.create(v, 0.5);
	setRendering();
}

void MainCommand::clear()
{
	surface = std::make_shared< Surface<float> >();
	//volumeCommand.clear();
	volume->setValue(0.0f);
	//bakedSurfaces.clear();
}

void MainCommand::doExport(const std::string& filename) const
{
	IO::STLFile file;

	IO::STLCellVector cells;
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


void MainCommand::setRendering()
{
	//rendering.add( spriteStrokeCommand->toParticle(cursor) );
	DisplayList list;
	list.add(mouse->getDisplayList());
	list.add(volume);
	list.add(surface);
	rendering.set(list);
}


void MainCommand::setUIControl(const UIControl ctrl)
{
	if (ctrl == UIControl::CAMERA) {
		mouse = cameraOperation;
	}
	else if (ctrl == UIControl::SPRITE_STROKE) {
		mouse = spriteStrokeCommand;
	}
	else {
		assert(false);
	}
}

void MainCommand::postMouseEvent()
{
	if (mouse->doBakeParticlesToVolume()) {
		const auto& particles = mouse->getBrushes();
		for (const auto& p : particles) {
			p->add(*volume);
			//volume->add(p.getPosition(), p.getSize().getX());
		}
	}
	if (mouse->doSurfaceConstruction()) {
		this->surface = std::make_shared< Surface<float> >();
		const auto& triangles = mc.march(*volume, 0.5);//vConfig.threshold);
		for (const auto& t : triangles) {
			surface->add(t, Graphics::ColorRGBA<float>::Blue());
		}
	}
	if (mouse->doRefresh()) {
		setRendering();
	}
}
