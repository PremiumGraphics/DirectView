#ifndef __CRYSTAL_UI_VOLUME_COMMAND_H__
#define __CRYSTAL_UI_VOLUME_COMMAND_H__

namespace Crystal {
	namespace UI{

class VolumeCommand {
public:

	Math::Volume3d<float> preVolume;
	Math::Volume3d<float> bakedVolume;

private:
};

	}
}

#endif