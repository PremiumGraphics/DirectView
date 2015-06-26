#include <stdafx.h>

#include "MainModel.h"

using namespace Crystal::Model;

MainModel<float>::MainModel() :
uiMode(UIMode::CAMERA_TRANSLATE),
planeMode(PlaneMode::XY)
{
	mc.buildTable();
	setupVolumes();
	createPreVolume(1.0);
	createSurface(preVolume);
	setRendering();
}

void MainModel<float>::clear()
{
	preVolume.setValue(0);
	bakedVolume.setValue(0);
	preSurfaces.clear();
	//bakedSurfaces.clear();
}

void MainModel<float>::doExport(const std::string& filename) const
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
