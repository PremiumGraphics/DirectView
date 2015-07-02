#include "VolumeCommand.h"

using namespace Crystal::Math;
using namespace Crystal::UI;

void VolumeCommand::setupVolumes(const VolumeConfig<float>& vConfig)
{
	Grid3d<float> grid(vConfig.resx, vConfig.resy, vConfig.resz);
	Volume3d<float> v(vConfig.space, grid);
	preVolume = v;
	bakedVolume = v;
}

void VolumeCommand::clear()
{
	preVolume.setValue(0);
	bakedVolume.setValue(0);
}
