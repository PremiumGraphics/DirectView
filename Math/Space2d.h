#ifndef __CRYSTAL_MATH_SPACE_2D_H__
#define __CRYSTAL_MATH_SPACE_2D_H__

#include "../Math/Quad.h"
#include "../Math/Vector2d.h"

namespace Crystal {
	namespace Math {

class Space2d final {
public:
	Space2d(const Vector2d<float>& start, unsigned int resx, unsigned int resy ) :
		start(start),
		resx(resx),
		resy(resy),
		sizes(Vector2d<float>(1.0f, 1.0f ))
	{}

	Space2d(unsigned int resx, unsigned int resy) : Space2d(Vector2d<float>::Zero(), resx, resy){}

	Vector2d<float> getSizes() const { return sizes; }

	Vector2d<float> getStart() const;

	Vector2d<float> getEnd() const;

	unsigned int getResX() const { return resx; }

	unsigned int getResY() const { return resy; }

	Quad getBoundingQuad() const;

private:

	Vector2d<float> start;
	Vector2d<float> sizes;
	unsigned int resx;
	unsigned int resy;
};

	}
}

#endif