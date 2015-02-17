#ifndef __CRYSTAL_IO_COLOR_RGBA_MAP_IO_H__
#define __CRYSTAL_IO_COLOR_RGBA_MAP_IO_H__

#include <istream>
#include <ostream>
#include "../Graphics/ColorRGBAMap.h"

namespace Crystal {
	namespace IO {

class ColorRGBAMapIO {
public:

	static void save( const Graphics::ColorRGBAMap<float>& map, const std::string& filename );

	static void save( const Graphics::ColorRGBAMap<float>& map, std::ostream& stream);

	static void load( Graphics::ColorRGBAMap<float>& map, const std::string& filename );

	static void load( Graphics::ColorRGBAMap<float>& map, std::istream& stream );
};
	}
}

#endif