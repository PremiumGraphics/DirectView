#ifndef __CRYSTAL_IO_CGS_FILE_H__
#define __CRYSTAL_IO_CGS_FILE_H__

#include <string>

namespace Crystal {
	namespace CG {

class CGSFile {
public:
	bool save(  const std::string& filename );
};

	}
}

#endif