#ifndef __CRYSTAL_GRAPHICS_IMAGE_2D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_2D_H__

#include "../Math/Grid2d.h"

namespace Crystal {
	namespace Graphics {

template< size_t N1, size_t N2, class T = ColorRGBA<float> >
using Image2d = Math::Grid2d < N1, N2, T >;

	}
}

#endif