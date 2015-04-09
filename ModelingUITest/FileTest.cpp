#include "stdafx.h"

#include "FileTest.h"


#include "wx/filename.h"

#include "../IO/OBJFile.h"
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

using namespace FileTest;


enum {
	ID_IMPORT = wxID_HIGHEST+1,
	ID_EXPORT,
	ID_CAPTURE,

};

Frame::Frame()
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxEmptyString)
{
	wxRibbonBar* bar = new wxRibbonBar
		(
		this,
		wxNewId(),
		wxDefaultPosition,
		wxDefaultSize
		);

	bar->SetArtProvider(new wxRibbonAUIArtProvider);


	wxRibbonPage* page = new wxRibbonPage(bar, wxNewId(), wxT("Polygon"));
	//wxRibbonPanel* panel = new wxRibbonPanel( page, wxID_ANY, wxT("Polygon") );


	Connect(ID_IMPORT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnImport));
	Connect(ID_EXPORT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnExport));
	//Connect(ID_CAPTURE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

	wxRibbonPanel *filePanel = new wxRibbonPanel(page, wxID_ANY, wxT("File"));
	wxRibbonButtonBar *toolbar = new wxRibbonButtonBar(filePanel);

	toolbar->AddButton(wxID_NEW, "New", wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(32, 32)));
	toolbar->AddButton(wxID_OPEN, "Open", wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(32, 32)));
	toolbar->AddButton(wxID_SAVE, "Save", wxImage("../Resource/save.png"));
	toolbar->AddButton(wxID_ANY, "Save As", wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_OTHER, wxSize(32, 32)));
	toolbar->AddButton(wxID_CLOSE, "Close", wxImage("../Resource/cancel.png"));


	Connect(wxID_NEW, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnNew));
	Connect(wxID_OPEN, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileOpen));
	Connect(wxID_SAVE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileSave));
	Connect(wxID_SAVEAS, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileSaveAs));
	Connect(wxID_CLOSE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnClose));
	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));

	toolbar->AddButton(ID_IMPORT, "Import", wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(32, 32)));
	toolbar->AddButton(ID_EXPORT, "Export", wxImage("../Resource/export.png"), "Export");
	toolbar->AddButton(ID_CAPTURE, "Capture", wxImage("../Resource/screenshot.png"));

	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));

	bar->Realize();

	Show();
}

void Frame::OnFileSave(wxRibbonButtonBarEvent&)
{
	const wxString& filename = wxFileSelector
		(
		wxT("Import"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"XML files (*.xml)|*.xml",
		wxFD_SAVE
		);

	if (filename.empty()) {
		return;
	}

	/*
	CGSFile file;
	const bool isOk = file.save( filename.ToStdString() );
	if( isOk ) {
	wxMessageBox( wxT("保存しました。") );
	}
	else {
	wxMessageBox( wxT("保存に失敗しました。") );
	}
	*/
}

void Frame::OnFileSaveAs(wxRibbonButtonBarEvent& e)
{
	wxMessageBox("TODO");
}

void Frame::OnFileOpen(wxRibbonButtonBarEvent& e)
{
	const wxString& filename = wxFileSelector
		(
		wxT("Import"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"XML files (*.xml)|*.xml",
		wxFD_OPEN
		);

	if (filename.empty()) {
		return;
	}

	/*
	const bool isOk = model->read( filename.ToStdString() );
	if( !isOk ) {
	wxMessageBox( wxT("読み込みに失敗しました。") );
	}
	*/
}


void Frame::OnNew(wxRibbonButtonBarEvent& e)
{
	const int ret = wxMessageBox(wxT("モデルを保存しますか？"), wxEmptyString, wxYES_NO, this);

	if (ret == wxYES) {
		OnFileSaveAs(e);
		return;
	}

	//clear();
	//view->Refresh();

	//w.refresh();
}

void Frame::OnClose(wxRibbonButtonBarEvent&)
{
	bool isChanged = true;
	if (isChanged) {
		wxMessageBox(wxT("モデルが変更されています。終了しますか。"));
	}
	Close(true);
}

void Frame::OnAbout(wxRibbonButtonBarEvent&)
{
	//wxMessageBox( wxT( "CG Studio 0.10" ) );

	//wxMessageBox(AppInfo::getProductName() + " " + AppInfo::getVersionStr() + "\n" + "Release" + AppInfo::getReleaseDateStr());
}

#include "../IO/PolygonFactory.h"

void Frame::OnImport(wxRibbonButtonBarEvent& e)
{
	const wxString& filename = wxFileSelector
		(
		wxT("Import"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"OBJ files (*.obj)|*.obj|"
		"STL files (*.stl)|*.stl",
		wxFD_OPEN
		);

	if (filename.empty()) {
		return;
	}

	wxFileName fn(filename);

	const wxString& ext = fn.GetExt();
	if (ext == "obj") {
		wxString path = fn.GetPath(false);
		wxString name = fn.GetName() + "." + fn.GetExt();

		OBJFileReader reader;
		OBJFile file = reader.read(path.ToStdString(), name.ToStdString());
		if (file.isValid()) {
			wxMessageBox(wxT("インポートに成功しました。"));
		}
		else {
			wxMessageBox(wxT("インポートに失敗しました。"), wxEmptyString, wxICON_WARNING);
			return;
		}
		//model->getPolygonModel()->polygons = obj.getPolygons();
		//const MTLFile& mtl = obj.getMTLFile();
		//view->Refresh();

		//w.refresh();

		//OnCameraFit(e);
	}
	else if (ext == "stl" || ext == "STL") {
		STLFile file;
		const bool isOK = file.read(filename.ToStdString());
		if (isOK) {
			wxMessageBox(wxT("インポートに成功しました。"));
		}
		else {
			wxMessageBox(wxT("インポートに失敗しました。"), wxEmptyString, wxICON_WARNING);
			return;
		}

		/*
		PolygonFactory factory(model.getPolygonBuilder());
		PolygonSPtrList g = factory.create(file);
		view->Refresh();

		w.refresh();

		OnCameraFit(e);
		*/
	}
}


void Frame::OnExport(wxRibbonButtonBarEvent& e)
{
	const wxString filename = wxFileSelector
		(
		wxT("Export"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"OBJ files (*.obj)|*.obj|"
		"STL files (*.stl)|*.stl",
		wxFD_SAVE
		);

	if (filename.empty()) {
		return;
	}

	wxFileName fn(filename);
	wxString path = fn.GetPath(false);
	wxString name = fn.GetName() + "." + fn.GetExt();
	const wxString& ext = fn.GetExt();

	if (ext == "obj") {
		OBJFile file;
		/*const bool isOk = file.write( path.ToStdString(), name.ToStdString() );
		if( !isOk ) {
		wxMessageBox(wxT("エクスポートに失敗しました。"), wxEmptyString, wxICON_WARNING );
		}
		*/
	}
	/*
	else if( ext == "stl" || ext == "STL" ) {
	STLFile stl;
	const bool isOk = stl.save( filename.ToStdString(), model );
	if( !isOk ) {
	wxMessageBox(wxT("エクスポートに失敗しました。"), wxEmptyString, wxICON_WARNING );
	}
	}
	*/
}
