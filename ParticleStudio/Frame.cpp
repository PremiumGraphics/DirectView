#include <stdafx.h>

#include "Frame.h"

#include "View.h"

#include "ParticleTree.h"

#include "../Graphics/PolygonBuilder.h"


#include "wx/filename.h"

#include "../IO/OBJFile.h"
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::CG;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_IMPORT,
	ID_EXPORT,

	ID_CREATE_SPHERE,
	ID_CREATE_CYLINDER,
	ID_CREATE_BOX,
	ID_CREATE_CONE,

	ID_CREATE_UNION,
	ID_CREATE_DIFF,
	ID_CREATE_INTERSECTION,

	ID_CAMERA_FIT,

	ID_CAPTURE,

	ID_GRAPHICS_SETTING,
};


class AppInfo {
public:
	static std::string getProductName() { return "ParticleStudio"; }

#define CG_STUDIO_MAJOR_VERSION 0
#define CG_STUDIO_MINOR_VERSION 2
#define CG_STUDIO_PATCH_VERSION 0


	static std::string getVersionStr()
	{
		return std::to_string(CG_STUDIO_MAJOR_VERSION) + "." + std::to_string(CG_STUDIO_MINOR_VERSION) + "." + std::to_string(CG_STUDIO_PATCH_VERSION);
	}

	static std::string getReleaseDateStr()
	{
		const int year = 2015;
		const int month = 2;
		const int day = 27;
		return std::to_string(year) + std::to_string(month) + std::to_string(day);
	}

};

Frame::Frame()
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxEmptyString )
{
	SetTitle(AppInfo::getProductName() + " " + AppInfo::getVersionStr());


    wxRibbonBar* bar = new wxRibbonBar
		(
		this,
		wxNewId(),
		wxDefaultPosition,
		wxDefaultSize
		);

	bar->SetArtProvider( new wxRibbonAUIArtProvider );

	wxRibbonPage* page = new wxRibbonPage( bar, wxNewId(), wxT("Polygon") );
	//wxRibbonPanel* panel = new wxRibbonPanel( page, wxID_ANY, wxT("Polygon") );

	wxRibbonPanel *filePanel = new wxRibbonPanel( page, wxID_ANY, wxT("File") );
	wxRibbonButtonBar *toolbar = new wxRibbonButtonBar( filePanel );

	toolbar->AddButton( wxID_NEW,	"New",		wxArtProvider::GetBitmap( wxART_NEW, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( wxID_OPEN,	"Open",		wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ));
	toolbar->AddButton( wxID_SAVE,	"Save",		wxImage("../Resource/save.png") );
	toolbar->AddButton( wxID_ANY,	"Save As",	wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( wxID_CLOSE, "Close",	wxImage("../Resource/cancel.png"));


	Connect( wxID_NEW,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnNew ) );
	Connect( wxID_OPEN,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileOpen ) );
	Connect( wxID_SAVE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileSave ) );
	Connect( wxID_SAVEAS,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileSaveAs ) );
	Connect( wxID_CLOSE,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnClose ) );
	Connect( wxID_ABOUT,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnAbout ) );

	toolbar->AddButton( ID_IMPORT,	"Import",	wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( ID_EXPORT,	"Export",	wxImage( "../Resource/export.png"), "Export" );
	toolbar->AddButton( ID_CAPTURE, "Capture",	wxImage("../Resource/screenshot.png"));

	toolbar->AddButton(ID_CAMERA_FIT, "Origin", wxImage("../Resource/zoom.png"));
	toolbar->AddButton(ID_GRAPHICS_SETTING, "Graphics", wxImage(32, 32));

	Connect( ID_IMPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnImport ) );
	Connect( ID_EXPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnExport ) );
	Connect( ID_CAPTURE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

	Connect(ID_CAMERA_FIT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraFit));
	Connect(ID_GRAPHICS_SETTING, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnGraphicsSetting));

	//wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	//wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );

	//Connect(ID_PICK_VERTEX,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnPick) );

	wxRibbonPanel* modelingPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Modeling"));
	wxRibbonButtonBar* modelingBar = new wxRibbonButtonBar(modelingPanel);
	modelingBar->AddButton(ID_CREATE_SPHERE, "Sphere", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_CYLINDER, "Cylinder", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_BOX, "Box", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_CONE, "Cone", wxImage(32, 32));

	modelingBar->AddButton(ID_CREATE_UNION, "Union", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_DIFF, "Diff", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_INTERSECTION, "Intersect", wxImage(32,32) );

	Connect(ID_CREATE_SPHERE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateSphere));
	Connect(ID_CREATE_CYLINDER, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCylinder));
	Connect(ID_CREATE_BOX, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateBox));
	Connect(ID_CREATE_CONE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCone));

	Connect(ID_CREATE_UNION, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateUnion));
	Connect(ID_CREATE_DIFF, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateDiff));
	Connect(ID_CREATE_INTERSECTION, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateIntersection));

	wxRibbonPanel *helpPanel = new wxRibbonPanel(page, wxID_ANY, wxT("ヘルプ"));
	wxRibbonButtonBar* helpToolBar = new wxRibbonButtonBar(helpPanel);
	helpToolBar->AddButton(wxID_ABOUT, "About", wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(32, 32)), "このソフトについて");

	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));


	bar->Realize();
	
	const int width = 1600;//720;
	const int height = 900;////480;

	view = new View( this, width, height, model );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	/*
	polygonProperty = new PolygonProperty(parent, wxSize(300, 100), model.getPolygonBuilder()->getMaterialBuilder()->getMaterials());
	materialProperty = new MaterialProperty(parent, wxSize(300, 100));
	lightProperty = new LightProperty(parent, wxSize(300, 100));

	polygonTree = new PolygonTree(parent, wxPoint(0, 0), wxSize(300, 100), polygonProperty, *model.getPolygonBuilder());
	materialTree = new MaterialTree(parent, wxPoint(0, 300), wxSize(300, 100), materialProperty, model.getPolygonBuilder()->getMaterialBuilder());
	lightTree = new LightTree(parent, wxPoint(0, 600), wxSize(300, 100), lightProperty, model.getLightBuilder());
	*/
	particleTree = new ParticleTree(this, wxPoint(0, 0), wxSize(300, 100));

	wxSizer *vSizer = new wxBoxSizer( wxVERTICAL );

	wxSizer *hSizer = new wxBoxSizer(wxHORIZONTAL);

	hSizer->Add(particleTree, 0, wxEXPAND);
	hSizer->Add(view, 0, wxEXPAND);

	vSizer->Add( bar, 0, wxEXPAND );
	vSizer->Add( hSizer, 0, wxEXPAND);


	SetSizer( vSizer );
	
	Show();
}

Frame::~Frame()
{
	model.clear();
}

void Frame::clear()
{
}

void Frame::OnNew( wxRibbonButtonBarEvent& e )
{
	const int ret = wxMessageBox(wxT("モデルを保存しますか？"), wxEmptyString, wxYES_NO, this );

	if( ret == wxYES ) {
		OnFileSaveAs( e );
		return;
	}

	clear();
	view->Refresh();
}

void Frame::OnClose( wxRibbonButtonBarEvent& )
{
	bool isChanged = true;
	if( isChanged ) {
		wxMessageBox(wxT("モデルが変更されています。終了しますか。"));
	}
	Close(true);
}

void Frame::OnAbout( wxRibbonButtonBarEvent& )
{
	//wxMessageBox( wxT( "CG Studio 0.10" ) );

	wxMessageBox(AppInfo::getProductName() + " " + AppInfo::getVersionStr() + "\n" + "Release" + AppInfo::getReleaseDateStr());
}

#include "../IO/CGSFile.h"

void Frame::OnFileSave( wxRibbonButtonBarEvent& )
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

	if ( filename.empty() ) {
		return;
	}

	CGSFile file;
	const bool isOk = file.save( filename.ToStdString() );
	if( isOk ) {
		wxMessageBox( wxT("保存しました。") );
	}
	else {
		wxMessageBox( wxT("保存に失敗しました。") );
	}
}

void Frame::OnFileSaveAs( wxRibbonButtonBarEvent& e )
{
	wxMessageBox("TODO");
}

void Frame::OnFileOpen( wxRibbonButtonBarEvent& e )
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
	
	if ( filename.empty() ) {
		return;
	}

	/*
	const bool isOk = model->read( filename.ToStdString() );
	if( !isOk ) {
		wxMessageBox( wxT("読み込みに失敗しました。") );
	}
	*/
}

/*
void Frame::OnPick(wxRibbonButtonBarEvent&)
{
	view->setMode(View::PICK_VERTEX);
	const int width = view->GetClientSize().GetWidth();
	const int height = view->GetClientSize().GetHeight();
	std::vector< GLubyte > pixels(width * height * 4);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()));
	wxImage image(width, height);

	int index = 0;

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			image.SetRGB(x, y, pixels[index], pixels[index + 1], pixels[index + 2]);
			index += 4;
		}
	}

	view->
}
*/


#include "../IO/PolygonFactory.h"

void Frame::OnImport( wxRibbonButtonBarEvent& e )
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

	if ( filename.empty() ) {
		return;
	}

	wxFileName fn( filename );

	/*

	const wxString& ext = fn.GetExt();
	if( ext == "obj" ) {
		wxString path = fn.GetPath( false );
		wxString name = fn.GetName() + "."  + fn.GetExt();

		OBJFileReader reader;
		OBJFile file = reader.read( path.ToStdString(), name.ToStdString() );
		if( file.isValid() ) {
			wxMessageBox( wxT("インポートに成功しました。") );
		}
		else {
			wxMessageBox( wxT("インポートに失敗しました。"), wxEmptyString, wxICON_WARNING );
			return;
		}
		//model->getPolygonModel()->polygons = obj.getPolygons();
		//const MTLFile& mtl = obj.getMTLFile();
		view->Refresh();

		OnCameraFit( e );
	}
	else if( ext == "stl" || ext == "STL" ) {
		STLFile file;
		const bool isOK = file.read( filename.ToStdString() );
		if (isOK) {
			wxMessageBox(wxT("インポートに成功しました。"));
		}
		else {
			wxMessageBox(wxT("インポートに失敗しました。"), wxEmptyString, wxICON_WARNING);
			return;
		}

		PolygonSPtrList g = factory.create(file);
		view->Refresh();

		OnCameraFit( e );
	}
	*/
}


void Frame::OnExport( wxRibbonButtonBarEvent& e )
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

	if( filename.empty() ) {
		return;
	}

	wxFileName fn( filename );
	wxString path = fn.GetPath( false );
	wxString name = fn.GetName() + "."  + fn.GetExt();
	const wxString& ext = fn.GetExt();

	if( ext == "obj" ) {
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


void Frame::OnCameraFit( wxRibbonButtonBarEvent& e )
{
	Camera<float>* camera = model.getCamera();
	camera->setPos( Vector3d( 0.0f, 0.0f, 0.0f ));
	camera->setAngle(Vector3d(0.0f, 0.0f, 0.0f));
	view->Refresh();

	/*
	const Math::Vector3d& center = getModel()->getPolygonModel()->getCenter();
	Camera<float>* camera = getModel()->getCamera();
	camera->setPos( -1.0 * center );
	const float minZ = getModel()->getPolygonModel()->getBoundingBox().getMinZ();
	//camera->setPos( .setZ( camera->pos.getZ() - minZ );
	camera->setAngle( Math::Vector3d( 0.0, 0.0, 0.0 ) );
	view->Refresh();
	*/
}

void Frame::OnCapture( wxRibbonButtonBarEvent& e )
{
	const int width = view->GetClientSize().GetWidth();
	const int height = view->GetClientSize().GetHeight();
	std::vector< GLubyte > pixels(width * height * 4);
	glReadBuffer(GL_FRONT);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()));
	wxImage image(width, height);

	int index = 0;

	for (int y = height - 1; y >= 0; --y) {
		for (int x = 0; x < width; ++x) {
			image.SetRGB(x, y, pixels[index], pixels[index + 1], pixels[index + 2]);
			index += 4;
		}
	}

	const wxString& filename = wxFileSelector
		(
		wxT("Save"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"BMP files (*.bmp)|*.bmp|"
		"PNG files (*.png)|*.png",
		wxFD_SAVE
		);

	if (filename.empty()) {
		return;
	}
	image.SaveFile(filename, wxBITMAP_TYPE_BMP);

}


void Frame::OnCreateSphere(wxRibbonButtonBarEvent& e)
{
	const Sphere s;
	model.create(s);
	view->Refresh();
	/*
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildSphere(modelings.sphereConfig.getUDivideNumber(), modelings.sphereConfig.getVDivideNumber());
	polygon->setName("Sphere");
	w.getPolygonTree()->build();
	*/
}

void Frame::OnCreateCylinder(wxRibbonButtonBarEvent& e)
{
	const Cylinder c;
	model.create(c);
	view->Refresh();
}


void Frame::OnCreateBox(wxRibbonButtonBarEvent& e)
{
	const Box b;
	model.create(b);
	view->Refresh();
}

void Frame::OnCreateCone(wxRibbonButtonBarEvent& e)
{
	view->Refresh();
}

#include <wx/numdlg.h>

void Frame::OnGraphicsSetting(wxRibbonButtonBarEvent& e)
{
	const int v = wxGetNumberFromUser("PointSize", wxEmptyString, wxEmptyString, view->getPointSize());
	if (v != -1) {
		view->setPointSize(v);
		view->Refresh();
	}
}


void Frame::OnCreateUnion(wxRibbonButtonBarEvent& e)
{
	if (model.getSelectedObjects().size() != 2) {
		wxMessageBox("Select Two Objects");
		return;
	}
}

void Frame::OnCreateDiff(wxRibbonButtonBarEvent& e)
{
	if (model.getSelectedObjects().size() != 2) {
		wxMessageBox("Select Two Objects");
		return;
	}
}

void Frame::OnCreateIntersection(wxRibbonButtonBarEvent& e)
{
	if (model.getSelectedObjects().size() != 2) {
		wxMessageBox("Select Two Objects");
		return;
	}
}