#ifndef __CRYSTAL_IO_CGB_FILE_H__
#define __CRYSTAL_IO_CGB_FILE_H__

#include "../ThirdParty/tinyxml2-master/tinyxml2.h"

#include "../Math/Volume.h"

#include <string>

namespace Crystal {
	namespace IO {


class CGBFile{
public:
	bool save(const std::string& filename, const Math::Volume3d<float>& volume);

};
	}
}
#endif