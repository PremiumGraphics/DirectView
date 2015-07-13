#include <stdafx.h>

#include "FileIO.h"

using namespace Crystal::Math;
using namespace Crystal::Command;

bool FileIO::save(const wxString& filename, const Volume3dSPtr<float>& volume)
{
	const auto xSize = volume->getSizeX();
	const auto ySize = volume->getSizeY();
	const auto zSize = volume->getSizeZ();
	for (size_t z = 0; z < zSize; ++z) {
		wxImage image;
		for (size_t x = 0; x < xSize; ++x ) {
			for (size_t y = 0; y < ySize; ++y) {
				const auto v = volume->getValue(x, y, z);
				image.SetRGB(x, y, v, 0, 0);
			}
		}
		if( !image.SaveFile(filename + std::to_string(z)) ) {
			return false;
		}
	}
	return true;
}