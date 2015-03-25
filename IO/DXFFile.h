#ifndef __CRYSTAL_IO_DXF_FILE_H__
#define __CRYSTAL_IO_DXF_FILE_H__

#include <istream>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace IO {

struct DXFFace{
	int getColorNumber() const { return colorNumber;  }

	Math::Vector3dVector setPositions();
	
private:
	int colorNumber;
	Math::Vector3dVector positions;
};

class DXFFile{
public:
	DXFFile(){};

	void read(std::istream& stream);

	void write(std::ostream& stream);

private:
	std::string layerName;

	Math::Vector3dVector positions;
};
	}
}

#endif