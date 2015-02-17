#include <stdafx.h>

#include "Frame.h"

#include "App.h"
//#include "Model.h"

using namespace Crystal::App;

IMPLEMENT_APP( App )

#include <wx/generic/choicdgg.h>


bool App::OnInit()
{
	if ( !wxApp::OnInit() ) {
		return false;
	}

	new Frame( );

	SetVendorName( wxT("VendorName") );
	//new Frame( &doc );
	
	return true;
}

int App::OnExit()
{
	return wxApp::OnExit();
}