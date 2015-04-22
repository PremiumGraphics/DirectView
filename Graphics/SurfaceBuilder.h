#ifndef __CRYSTAL_GRAPHICS_SURFACE_BUILDER_H__
#define __CRYSTAL_GRAPHICS_SURFACE_BUILDER_H__

#include "../Particle/ParticleObject.h"
#include "Polygon.h"

#include "ImageRGBA.h"

namespace Crystal {
	namespace Graphics {

class Grid2d
{
public:
	Grid2d(const unsigned int xSize, const unsigned int ySize) :
		xSize(xSize),
		ySize(ySize)
	{
		grid.resize(xSize);
	}

	void setPosition(const int x, const int y, const float value )
	{
		;
	}
private:
	const unsigned int xSize;
	const unsigned int ySize;
	std::vector< std::vector< float > > grid;
};

class Grid3d
{
	void setPosition(const Math::Vector3d& pos) {
		;
	}
private:
	std::vector<Grid2d> scene2ds;
};

class SurfaceBuilder {
public:
	Polygon* build(const Particle::ParticleObject& object);

	Math::Vector3dVector findEdges(const ImageRGBA<float>& image);

private:
};
	}
}

#endif