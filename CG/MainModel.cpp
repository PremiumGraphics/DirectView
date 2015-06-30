#include <stdafx.h>

#include "MainModel.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

MainModel::MainModel() :
mouse(std::make_shared<UI::CameraOperationCommand>(camera)),
isSphere(false)
{
	setupVolumes();
	createPreVolume(1.0);
	surfaceCommand.createSurface(preVolume);
	setRendering();
}

void MainModel::clear()
{
	preVolume.setValue(0);
	bakedVolume.setValue(0);
	surfaceCommand.clear();
	//bakedSurfaces.clear();
}

void MainModel::doExport(const std::string& filename) const
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

void MainModel::setupVolumes()
{
	Math::Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
	Math::Volume3d<float> v(vConfig.space, grid);
	preVolume = v;
	bakedVolume = v;
}


void MainModel::createPreVolume(const float factor)
{
	surfaceCommand.clear();
	preVolume = bakedVolume;
	preVolume.add(particle, factor);
	surfaceCommand.createSurface(preVolume);
	setRendering();
}

void MainModel::bakeParticleToVolume()
{
	bakedVolume = preVolume;
	surfaceCommand.createSurface(bakedVolume);
	setRendering();
}


void MainModel::setUIControl(const UIControl ctrl)
{
	if (ctrl == UIControl::CAMERA) {
		mouse = std::make_shared<UI::CameraOperationCommand>(camera);
	}
	else if (ctrl == UIControl::PARTICLE) {
		mouse = std::make_shared<UI::ParticleOperationCommand>(camera, particle);
	}
	else if (ctrl == UIControl::PARTICLE_SCALE) {
		mouse = std::make_shared<UI::ParticleScaleCommand>(camera, particle);
	}
	else if (ctrl == UIControl::BONE_MOVE) {
		mouse = std::make_shared<UI::BoneOperationCommand>(camera, *boneCommand.getSelectedBone());
	}
	else {
		assert(false);
	}
}
