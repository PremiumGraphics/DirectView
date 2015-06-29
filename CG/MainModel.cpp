#include <stdafx.h>

#include "MainModel.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Model;

MainModel::MainModel() :
mouse(std::make_shared<UI::CameraCommand>(camera)),
realtimePreviewMode(false),
doRealTimeBaking(false)
{
	mc.buildTable();
	setupVolumes();
	createPreVolume(1.0);
	createSurface(preVolume);
	setRendering();
}

void MainModel::clear()
{
	preVolume.setValue(0);
	bakedVolume.setValue(0);
	preSurfaces.clear();
	//bakedSurfaces.clear();
}

void MainModel::doExport(const std::string& filename) const
{
	IO::STLFile file;

	IO::STLCellVector cells;
	for (const auto& s : preSurfaces) {
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

/*

void MainModel::onDraggingLeft(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	if (uiMode == UIMode::CAMERA_TRANSLATE) {
		camera.move(v);
	}
	else if (uiMode == UIMode::PARTICLE_TRANSLATE) {
		particle.move(getScrennSpaceDiff(v * 1));
		createPreVolume(1.0);
		const auto& s = createSurface(preVolume);
		setRendering();
	}
	else if (uiMode == UIMode::PARTICLE_STROKE) {
		particle.move(getScrennSpaceDiff(v * 1));
		createPreVolume(1.0);
		const auto& s = createSurface(preVolume);
		setRendering();
		bakeParticleToVolume();
	}
}

void MainModel::onDraggingRight(const Vector3d<float>& src)
{
	const Math::Vector3d<float>& v = getDiff(src);
	if (uiMode == UIMode::CAMERA_TRANSLATE) {
		camera.addAngle(src);
	}
	else if (uiMode == UIMode::PARTICLE_STROKE) {
		particle.move(getScrennSpaceDiff(v * 1));
		createPreVolume(-1.0);
		const auto& s = createSurface(preVolume);
		setRendering();
		bakeParticleToVolume();
	}

}

void MainModel::onDraggindMiddle(const Vector3d<float>& diff)
{
	if (uiMode == UIMode::CAMERA_TRANSLATE) {
		const Math::Vector3d<float> v(0, 0, diff.getY());
		camera.move(v);
	}
	else {
		const Math::Vector3d<float> v(0, 0, diff.getY());
		particle.move(getScrennSpaceDiff(v * 1));
		createPreVolume(1.0);
		const auto& s = createSurface(preVolume);
		setRendering();
	}
	/*
	else if (uiMode == PARTICLE_TRANSLATE) {
	const Vector3d<float> v(0, 0, diff.getX());
	particle.move(v);
	}
	*/

//}
