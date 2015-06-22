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
	void exportToSTL(const std::string& filename, const Graphics::SurfaceSPtrList<T>& surfaces) {
		IO::STLFile file;

		IO::STLCellVector cells;
		for (const auto& s : surfaces) {
			for (const Graphics::FaceSPtr<T>& f : s->getFaces()) {
				Math::Vector3dVector<T> positions;
				for (const auto& e : f->getEdges()) {
					positions.push_back( e->getStartPosition() );
				}
				const auto normal = f->getNormal();
				STLCell cell(positions, normal);
				cells.push_back(cell);
			}
		}

		file.setTitle("TestTitle");
		file.setCells(cells);
		file.writeASCII(filename);

	}

};
	}
}

#endif