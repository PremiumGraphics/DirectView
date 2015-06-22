#ifndef __CRYSTAL_MODEL_FILE_EXPORT_COMMAND_H__
#define __CRYSTAL_MODEL_FILE_EXPORT_COMMAND_H__

#include "../IO/STLFile.h"
#include <sstream>

namespace Crystal {
	namespace Model {

template<typename T>
class FileExportCommand final
{
public:
	void exportToSTL(const std::string& filename) {
		IO::STLFile file;

		const Math::Vector3d<T> normal1(0.0, 0.0, 1.0);
		const Math::Vector3dVector<T> positions1 = {
			Vector3d<T>(0.0, 0.0, 1.0),
			Vector3d<T>(1.0, 0.0, 1.0),
			Vector3d<T>(0.0, 1.0, 1.0)
		};
		const Math::Vector3d<T> normal2(0.0, 0.0, 1.0);
		const Math::Vector3dVector<T> positions2 = {
			Vector3d<T>(1.0, 1.0, 1.0),
			Vector3d<T>(0.0, 1.0, 1.0),
			Vector3d<T>(1.0, 0.0, 1.0)
		};
		const STLCellVector cells{
			STLCell(positions1, normal1),
			STLCell(positions2, normal2)
		};

		file.setTitle("TestTitle");
		file.setCells(cells);
		file.writeASCII(filename);

	}

};
	}
}

#endif