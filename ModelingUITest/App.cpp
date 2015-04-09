#include <stdafx.h>

#include "Frame.h"

#include "App.h"
//#include "Model.h"

using namespace Crystal::Modeling;

IMPLEMENT_APP( App )

#include <wx/generic/choicdgg.h>

#include "FileTest.h"
#include "ModelingDialogTest.h"

bool App::OnInit()
{
	if (!wxApp::OnInit()) {
		return false;
	}

	SetVendorName(wxT("VendorName"));
	//new Frame();
	//new FileTest::Frame();
	new ModelingDialogTest::Frame();

	return true;
}

int App::OnExit()
{
	return wxApp::OnExit();
}