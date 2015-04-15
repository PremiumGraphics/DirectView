#ifndef __CRYSTAL_CG_APP_H__
#define __CRYSTAL_CG_APP_H__

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

	wxDECLARE_NO_COPY_CLASS( App );
};


	}
}


#endif