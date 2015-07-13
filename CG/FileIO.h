#ifndef __CRYSTAL_UI_FILE_IO_H__
#define __CRYSTAL_UI_FILE_IO_H__

#include <stdafx.h>
#include "MainCommand.h"

namespace Crystal {
	namespace Command {

class FileIO
{
	bool save(const wxString& filename, const Math::Volume3dSPtr<float>& volume );

	//void load(const wxString& filename);
};
	}
}

#endif