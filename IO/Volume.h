#ifndef __CRYSTAL_IO_VOLUME_H__
#define __CRYSTAL_IO_VOLUME_H__

#include "../Math/Vector3d.h"

#include <vector>

namespace Crystal {
	namespace IO {

class Volume {
public:
	Volume( const int dimX, const int dimY, const int dimZ ) :
		dimX( dimX ),
		dimY( dimY ),
		dimZ( dimZ )
	{
	}

	std::vector< float > createHydrogenVolume();

	std::vector< Math::Vector3d<float> > createTornadoVolume( const float time );

	void setDimensions( const int dimX, const int dimY, const int dimZ ) {
		this->dimX = dimX;
		this->dimY = dimY;
		this->dimZ = dimZ;
	}

private:
	int dimX;
	int dimY;
	int dimZ;

};


	}
}

#endif