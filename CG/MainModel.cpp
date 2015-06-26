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
