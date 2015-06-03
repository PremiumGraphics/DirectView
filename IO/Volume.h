#ifndef __CRYSTAL_IO_VOLUME_H__
#define __CRYSTAL_IO_VOLUME_H__

#include "../Math/Vector.h"

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

	//  Orignal source code is developed by https://code.google.com/p/kvs/.
	std::vector< float > createHydrogenVolume() {
		const float kr1 = 32.0f / dimX;
		const float kr2 = 32.0f / dimY;
		const float kr3 = 32.0f / dimZ;
		const float kd = 6.0;

		std::vector< float > values;

		for (int z = 0; z < dimZ; ++z) {
			const float dz = kr3 * (z - (dimZ / 2.0f));
			for (int y = 0; y < dimY; ++y) {
				const float dy = kr2 * (y - (dimY / 2.0f));
				for (int x = 0; x < dimX; ++x) {
					const float dx = kr1 * (x - (dimX / 2.0f));
					const float r = std::sqrt(dx * dx + dy * dy + dz * dz);
					const float cos_theta = dz / r;
					const float phi = kd * (r*r) * std::exp(-r / 2) * (3 * cos_theta*cos_theta - 1);

					float c = phi * phi;
					if (c > 255.0) {
						c = 255.0;
					}

					values.push_back(c);
				}
			}
		}

		return values;
	}

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