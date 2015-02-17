#ifndef __CRYSTAL_APP_APP_H__
#define __CRYSTAL_APP_APP_H__

namespace Crystal {
	namespace App {

class App : public wxApp
{
public:
	App()
	{
	}

	virtual bool OnInit();
	virtual int OnExit();

private:

	wxDECLARE_NO_COPY_CLASS( App );
};


	}
}


#endif