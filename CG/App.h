#ifndef __CRYSTAL_CG_APP_H__
#define __CRYSTAL_CG_APP_H__

#include "Model.h"

namespace Crystal {
	namespace CG {

class App : public wxApp
{
public:
	App()
	{
	}

	virtual bool OnInit();
	virtual int OnExit();

private:
	Model doc;

	wxDECLARE_NO_COPY_CLASS( App );
};


	}
}


#endif