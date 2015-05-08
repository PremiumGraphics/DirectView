#ifndef __CRYSTAL_GRAPHICS_IMAGE_1D_H__
#define __CRYSTAL_GRAPHICS_IMAGE_1D_H__

#include <array>

#include "ColorRGBA.h"
#include "../Math/Grid1d.h"

namespace Crystal {
	namespace Graphics {

template< size_t N, class T = ColorRGBA<float> >
using Image1d = Math::Grid1d < N, T > ;

	}
}

#endif