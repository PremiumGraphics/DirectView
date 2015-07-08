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

	cameraOperation = std::make_shared<UI::CameraOperationCommand>(camera);
	spriteStrokeCommand = std::make_shared<SpriteStrokeCommand>(camera, cursor, volume);
	cursorOperation = std::make_shared<UI::Cursor3dOperationCommand>(camera, cursor);
	lineOperation = std::make_shared<UI::LineStrokeCommand>(camera, cursor, volume);
	//boneOperation = std::make_shared<UI::LineStrokeCommand>(camera, cursor);

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
	skeleton.clear();
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
	rendering.add( spriteStrokeCommand->toParticle(cursor) );
	rendering.add(volume);
	rendering.add(s);
}

void MainCommand::setRendering()
{
	const auto& s = toSurface(volume, 0.5);
	setRendering(*s);
}



void MainCommand::setUIControl(const UIControl ctrl)
{
	if (ctrl == UIControl::CAMERA) {
		mouse = cameraOperation;
	}
	else if (ctrl == UIControl::CURSOR) {
		mouse = cursorOperation;
	}
	else if (ctrl == UIControl::SPRITE_STROKE) {
		mouse = spriteStrokeCommand;
	}
	else if (ctrl == UIControl::LINE_STROKE) {
		mouse = lineOperation;
	}
	else if (ctrl == UIControl::BONE_STROKE) {
		mouse = boneOperation;
	}
	else {
		assert(false);
	}
}

void MainCommand::postMouseEvent()
{
	mouse->doPost();
	if (mouse->doRealTimePreview()) {
		const auto& s = toSurface(volume, 0.5);
		setRendering(*s);
		const auto& line = lineOperation->getLine();
		rendering.add(line);
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
