#ifndef __CRYSTAL_GRAPHICS_IMAGE_H__
#define __CRYSTAL_GRAPHICS_IMAGE_H__

#include <array>

#include "ColorRGBA.h"
#include "../Math/Grid1d.h"
#include "../Math/Grid2d.h"
#include "../Math/Grid3d.h"

namespace Crystal {
	namespace Graphics {

		template< size_t N, class T = ColorRGBA<float> >
		using Image1d = Math::Grid1d < N, T >;


		template< size_t N1, size_t N2, class T = ColorRGBA<float> >
		using Image2d = Math::Grid2d < N1, N2, T >;


		template< size_t N1, size_t N2, size_t N3 >
		using Image3d = Math::Grid3d < N1, N2, N3, ColorRGBA<float> >;


	}
}

#endif