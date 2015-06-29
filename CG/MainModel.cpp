#include <stdafx.h>

#include "MainModel.h"

using namespace Crystal::UI;
using namespace Crystal::Math;
using namespace Crystal::Model;

MainModel::MainModel() :
mouse(std::make_shared<UI::CameraCommand>(camera)),
isSphere(false)
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

void MainModel::setupVolumes()
{
	Math::Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
	Math::Volume3d<float> v(vConfig.space, grid);
	preVolume = v;
	bakedVolume = v;
}


void MainModel::createPreVolume(const float factor)
{
	preSurfaces.clear();
	preVolume = bakedVolume;
	preVolume.add(particle, factor);
	const auto& s = createSurface(preVolume);
	preSurfaces.push_back(s);
	setRendering();
}

void MainModel::setUIControl(const UIControl ctrl)
{
	if (ctrl == UIControl::Camera) {
		mouse = std::make_shared<UI::CameraCommand>(camera);
	}
	else if (ctrl == UIControl::Particle) {
		mouse = std::make_shared<UI::ParticleCommand>(camera, particle);
	}
	else if (ctrl == UIControl::ParticleScale) {
		mouse = std::make_shared<UI::ParticleScaleCommand>(camera, particle);
	}
}
