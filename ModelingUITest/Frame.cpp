#include <stdafx.h>

#include "Frame.h"

#include "View.h"

#include "Tree.h"
#include "PropertyDialog.h"
#include "../Graphics/PolygonBuilder.h"

#include "wx/filename.h"

#include "../IO/OBJFile.h"
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Modeling;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_CAMERA_CONFIG,

	ID_CAMERA_TRANSLATE,
	ID_POLYGON_TRANSLATE,
	ID_POLYGON_ROTATE,
	ID_POLYGON_ROTATE_X,
	ID_POLYGON_ROTATE_Y,
	ID_POLYGON_ROTATE_Z,
	//ID_PICK_VERTEX,

	ID_IMPORT,
	ID_EXPORT,

	ID_POLYGON_SCALE,
	ID_POLYGON_SCALE_X,
	ID_POLYGON_SCALE_Y,
	ID_POLYGON_SCALE_Z,

	ID_CREATE_TRIANGLE,
	ID_CREATE_QUAD,
	ID_CREATE_CIRCLE,
	ID_CREATE_SPHERE,
	ID_CREATE_CYLINDER,
	ID_CREATE_BOX,
	ID_CREATE_CONE,

	ID_CAMERA_FIT,

	ID_CAPTURE,
};


class AppInfo {
public:
	static std::string getProductName() { return "Modeling3DUITest"; }

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

void Widgets::build(Frame* parent, Model& model)
{
	polygonProperty = new PolygonProperty(parent, wxSize(300, 300), model.getPolygonBuilder()->getMaterialBuilder()->getMaterials());

	polygonTree = new PolygonTree(parent, wxPoint(0, 0), wxSize(300, 300), polygonProperty, model.getPolygonBuilder());
}


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

	Connect( ID_CAMERA_TRANSLATE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraTranslate ) );

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


	Connect( ID_IMPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnImport ) );
	Connect( ID_EXPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnExport ) );
	Connect( ID_CAPTURE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

	wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );
	operation->AddButton( ID_CAMERA_TRANSLATE,	"Camera",	wxImage("../Resource/view.png") );
	operation->AddButton( ID_CAMERA_FIT,		"Zoom",		wxImage("../Resource/zoom.png") );
	operation->AddButton( ID_POLYGON_TRANSLATE, "Move",		wxImage("../Resource/8-direction.png") );
	//operation->AddDropdownButton( ID_POLYGON, wxT("Other Polygon"), wxBitmap(hexagon_xpm), wxEmptyString);

	operation->AddDropdownButton( ID_POLYGON_ROTATE,	"Rotate",	wxImage("../Resource/3D-X-Axis-Rotation.png") );
	operation->AddButton( ID_POLYGON_ROTATE_X, "RotateX",	wxImage("../Resource/3D-X-Axis-Rotation.png"));
	operation->AddButton( ID_POLYGON_ROTATE_Y, "RotateY",	wxImage("../Resource/3D-Y-Axis-Rotation.png"));
	operation->AddButton( ID_POLYGON_ROTATE_Z, "RotateZ",	wxImage("../Resource/3D-Z-Axis-Rotation.png"));
	//operation->AddButton(ID_PICK_VERTEX, "Pick", wxImage("../Resource/8-direction.png"));

	operation->AddButton( ID_POLYGON_SCALE,		"Scale",	wxImage("../Resource/8-direction.png") );

	Connect( ID_CAMERA_FIT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraFit ) );
	Connect( ID_POLYGON_TRANSLATE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonTranslate ) );
	Connect( ID_POLYGON_SCALE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonScale ) );
	Connect( ID_POLYGON_ROTATE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotate ) );
	Connect( ID_POLYGON_ROTATE_X,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotateX) );
	Connect( ID_POLYGON_ROTATE_Y,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotateY) );
	Connect( ID_POLYGON_ROTATE_Z,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotateZ) );
	//Connect(ID_PICK_VERTEX,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnPick) );
	Connect(ID_POLYGON_ROTATE, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnDropDown));


	wxRibbonPanel* modelingPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Modeling"));
	wxRibbonButtonBar* modelingBar = new wxRibbonButtonBar( modelingPanel );
	modelingBar->AddHybridButton( ID_CREATE_TRIANGLE,	"Triangle",	wxImage("../Resource/triangle.png") );
	modelingBar->AddHybridButton( ID_CREATE_QUAD,		"Quad",		wxImage("../Resource/quad.png") );
	modelingBar->AddHybridButton( ID_CREATE_CIRCLE,		"Circle",	wxImage("../Resource/circle.png"));
	modelingBar->AddHybridButton( ID_CREATE_SPHERE,		"Sphere",	wxImage("../Resource/quad.png"));
	modelingBar->AddHybridButton( ID_CREATE_CYLINDER,	"Cylinder", wxImage("../Resource/cylinder.png"));
	modelingBar->AddHybridButton( ID_CREATE_BOX,		"Box",		wxImage("../Resource/box.png"));
	modelingBar->AddHybridButton( ID_CREATE_CONE,		"Cone",		wxImage("../Resource/cylinder.png"));
	
	Connect( ID_CREATE_TRIANGLE,	wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateTriangle) );
	Connect( ID_CREATE_TRIANGLE,	wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED,	wxRibbonButtonBarEventHandler(Frame::OnCreateTriangleConfig));
	Connect( ID_CREATE_QUAD,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateQuad) );
	Connect( ID_CREATE_QUAD,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateQuadConfig));
	Connect( ID_CREATE_CIRCLE,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateCircle) );
	Connect( ID_CREATE_CIRCLE,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCircleConfig));
	Connect( ID_CREATE_SPHERE,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateSphere) );
	Connect( ID_CREATE_SPHERE,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateSphereConfig));
	Connect( ID_CREATE_CYLINDER,	wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateCylinder) );
	Connect( ID_CREATE_CYLINDER,	wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCylinderConfig));
	Connect( ID_CREATE_BOX,			wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateBox));
	Connect( ID_CREATE_BOX,			wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateBoxConfig));
	Connect( ID_CREATE_CONE,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateCone));
	Connect( ID_CREATE_CONE,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateConeConfig) );

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

	w.build(this, model);

	/*
	polygonProperty = new PolygonProperty(parent, wxSize(300, 100), model.getPolygonBuilder()->getMaterialBuilder()->getMaterials());
	materialProperty = new MaterialProperty(parent, wxSize(300, 100));
	lightProperty = new LightProperty(parent, wxSize(300, 100));

	polygonTree = new PolygonTree(parent, wxPoint(0, 0), wxSize(300, 100), polygonProperty, *model.getPolygonBuilder());
	materialTree = new MaterialTree(parent, wxPoint(0, 300), wxSize(300, 100), materialProperty, model.getPolygonBuilder()->getMaterialBuilder());
	lightTree = new LightTree(parent, wxPoint(0, 600), wxSize(300, 100), lightProperty, model.getLightBuilder());
	*/

	wxSizer *vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );

	wxSizer* rSizer = new wxBoxSizer( wxVERTICAL );
	rSizer->Add( w.getPolygonTree(), 0, wxEXPAND );

	rSizer->Add( w.getPolygonProperty(), 0, wxEXPAND );

	hSizer->Add( rSizer, 0, wxEXPAND );
	hSizer->Add( view, 0, wxEXPAND);


	vSizer->Add( bar, 0, wxEXPAND );
	vSizer->Add( hSizer, 0, wxEXPAND );

	//sizer->Add( tree, 0, wxEXPAND );
	w.refresh();

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

	w.refresh();
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

void Frame::OnCameraTranslate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::CAMERA_TRANSLATE );
}

void Frame::OnPolygonRotate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::POLYGON_ROTATE );
}

void Frame::OnPolygonRotateX(wxRibbonButtonBarEvent&)
{
	view->setMode(View::POLYGON_ROTATE_X);
}

void Frame::OnPolygonRotateY(wxRibbonButtonBarEvent&)
{
	view->setMode(View::POLYGON_ROTATE_Y);
}

void Frame::OnPolygonRotateZ(wxRibbonButtonBarEvent&)
{
	view->setMode(View::POLYGON_ROTATE_Z);
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

		w.refresh();

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

		PolygonFactory factory( model.getPolygonBuilder() );
		PolygonSPtrList g = factory.create(file);
		view->Refresh();

		w.refresh();

		OnCameraFit( e );
	}
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

void Frame::OnGLConfig( wxRibbonButtonBarEvent& e )
{
	const GLubyte* str = glGetString( GL_RENDERER );
	const GLubyte* vendor = glGetString( GL_VENDOR );
	const GLubyte* glVersion = glGetString( GL_VERSION );
	const GLubyte* glslVersion = glGetString( GL_SHADING_LANGUAGE_VERSION );

	wxString s;

	char a[256];
	sprintf( a, "%s\n", str );
	
	s += wxString::Format("Renderer = %s", a );

	sprintf( a, "%s\n", vendor );
	s += wxString::Format("Vendor = %s", a );

	sprintf( a, "%s\n", glVersion );
	s += wxString::Format("GL Version = %s", a );

	sprintf( a, "%s\n", glslVersion );
	s += wxString::Format("GLSL Version = %s", a );

	GLint bufs;
	glGetIntegerv( GL_SAMPLE_BUFFERS, &bufs );

	sprintf( a, "%d\n", bufs );
	s += wxString::Format("Sample Buffer = %s", a );

	wxMessageBox( s );
}

void Frame::OnLocale( wxCommandEvent& )
{
	const wxString names[] =
	{
		"System default",
		"Japanese",
	};
	const int index = wxGetSingleChoiceIndex
		(
		_("Language Choice"),
		_("Language"),
		WXSIZEOF( names ),
		names
		);
	//locale.Init( m_lang, wxLOCALE_DONT_LOAD_DEFAULT)
}

#include "wx/numdlg.h"

void Frame::OnPolygonTranslate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::POLYGON_TRANSLATE );
}

void Frame::OnPolygonScale( wxRibbonButtonBarEvent& e)
{
	view->setMode( View::POLYGON_SCALE );
}


void Frame::OnCameraFit( wxRibbonButtonBarEvent& e )
{
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

void Frame::OnCreateTriangle(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildTriangle();
	polygon->setName("Triangle");
	w.getPolygonTree()->build();
}

void Frame::OnCreateTriangleConfig(wxRibbonButtonBarEvent& e)
{
	TriangleConfigDialog dialog(this);
	if ( dialog.ShowModal() == wxID_OK) {
		dialog.setConfig( dialog.getConfig() );
	}
}

void Frame::OnCreateQuad(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildQuad();
	polygon->setName("Quad");
	w.getPolygonTree()->build();
}

void Frame::OnCreateQuadConfig(wxRibbonButtonBarEvent& e)
{
	QuadConfigDialog dialog(this);
	dialog.setConfig( modelings.quadConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.quadConfig = dialog.getConfig();
	}
}

void Frame::OnCreateCircle(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildCircleByNumber(1.0f, modelings.circleConfig.getDivideNumber());
	polygon->setName("Circle");
	w.getPolygonTree()->build();
}

void Frame::OnCreateCircleConfig(wxRibbonButtonBarEvent& e)
{
	CircleConfigDialog dialog(this);
	dialog.setConfig(modelings.circleConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.circleConfig = dialog.getConfig();
	}
}

void Frame::OnCreateSphere(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildSphere(modelings.sphereConfig.getUDivideNumber(), modelings.sphereConfig.getVDivideNumber());
	polygon->setName("Sphere");
	w.getPolygonTree()->build();
}

void Frame::OnCreateSphereConfig(wxRibbonButtonBarEvent& e)
{
	//const int num = wxGetNumberFromUser("Divide Number", wxEmptyString, wxEmptyString, 3, 360);
	SphereConfigDialog dialog(this);
	dialog.setConfig(modelings.sphereConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.sphereConfig = dialog.getConfig();
	}
}

void Frame::OnCreateCylinder(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildCylinder(modelings.cylinderConfig.divideNumber);
	polygon->setName("Cylinder");
	w.getPolygonTree()->build();
}

void Frame::OnCreateCylinderConfig(wxRibbonButtonBarEvent& e)
{
	CylinderConfigDialog dialog(this);
	dialog.setConfig(modelings.cylinderConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.cylinderConfig = dialog.getConfig();
	}
}

void Frame::OnCreateBox(wxRibbonButtonBarEvent& e)
{
	const PolygonSPtr& polygon = model.getPolygonBuilder()->buildBox();
	polygon->setName("Box");
	w.getPolygonTree()->build();
}

void Frame::OnCreateBoxConfig(wxRibbonButtonBarEvent& e)
{
	BoxConfigDialog dialog(this);
	dialog.setConfig(modelings.boxConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.boxConfig = dialog.getConfig();
	}
}


void Frame::OnCreateCone(wxRibbonButtonBarEvent& e)
{
	model.getPolygonBuilder()->buildCone( modelings.coneConfig.divideNumber);
	w.getPolygonTree()->build();
}

void Frame::OnCreateConeConfig(wxRibbonButtonBarEvent& e)
{
	ConeConfigDialog dialog(this);
	dialog.setConfig(modelings.coneConfig);
	if (dialog.ShowModal() == wxID_OK) {
		modelings.coneConfig = dialog.getConfig();
	}
}


void Frame::OnDropDown(wxRibbonButtonBarEvent& e)
{
	wxMenu menu;
	menu.Append(wxID_ANY, wxT("X"));
	menu.Append(wxID_ANY, wxT("Y"));
	menu.Append(wxID_ANY, wxT("Z"));

	e.PopupMenu(&menu);
}
