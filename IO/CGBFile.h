#ifndef __CRYSTAL_IO_CGB_FILE_H__
#define __CRYSTAL_IO_CGB_FILE_H__

#include "../ThirdParty/tinyxml2-master/tinyxml2.h"

#include <string>

namespace Crystal {
	namespace IO {


class CGBFile{
public:
	bool save(const std::string& directory, const std::string& filename);

};
	}
}
#endif