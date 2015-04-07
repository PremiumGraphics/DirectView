#include <stdafx.h>

#include "Frame.h"

#include "App.h"
//#include "Model.h"

using namespace Crystal::CG;

IMPLEMENT_APP( App )

#include <wx/generic/choicdgg.h>


bool App::OnInit()
{
	if ( !wxApp::OnInit() ) {
		return false;
	}

	SetVendorName( wxT("VendorName") );
	new Frame();
	
	return true;
}

int App::OnExit()
{
	return wxApp::OnExit();
}