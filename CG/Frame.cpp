#include <stdafx.h>

#include "Frame.h"

#include "View.h"

#include "MaterialProperty.h"
#include "MaterialTree.h"
#include "LightProperty.h"
#include "LightTree.h"
#include "PolygonProperty.h"


#include "wx/filename.h"

#include "../IO/OBJFile.h"
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::CG;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_CAMERA_CONFIG,

	ID_LIGHT_TRANSLATE,
	ID_CAMERA_TRANSLATE,
	ID_POLYGON_TRANSLATE,
	ID_POLYGON_ROTATE,

	ID_IMPORT,
	ID_EXPORT,

	ID_GL_CONFIG,
	ID_LOCALE,

	ID_POLYGON_SCALE,
	ID_OFF_SCREEN_CONFIG,

	ID_TEXTURE,

	ID_CREATE_TRIANGLE,
	ID_CREATE_QUAD,
	ID_CREATE_CIRCLE,
	ID_CREATE_SPHERE,
	ID_CREATE_CYLINDER,

	ID_RENDERING_WIREFRAME,
	ID_RENDERING_FLAT,
	ID_RENDERING_PHONG,
	ID_RENDERING_NORMAL,
	ID_RENDERING_POINT,

	ID_CAMERA_FIT,

	ID_CAPTURE,
};

#include "PolygonTree.h"


class AppInfo {
public:
	static std::string getProductName() { return "CGStudio"; }

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
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxT("CG Studio 0.10")),
	circleDivideAngle( 60.0f )
{
	SetTitle(AppInfo::getProductName() + " " + AppInfo::getVersionStr());

	sphereConfigDialog = new SphereConfigDialog(this);

	camera.setNear(1.0f);

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

	toolbar->AddButton( wxID_NEW,	"New",	wxArtProvider::GetBitmap( wxART_NEW, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( wxID_OPEN,	"Open", wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ));
	toolbar->AddButton( wxID_SAVE,	"Save", wxImage("../Resource/save.png") );
	toolbar->AddButton( wxID_ANY,	"Save As", wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( wxID_CLOSE, "Close", wxImage("../Resource/cancel.png"));


	Connect( wxID_NEW,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnNew ) );
	Connect( wxID_OPEN,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileOpen ) );
	Connect( wxID_SAVE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileSave ) );
	Connect( wxID_SAVEAS,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileSaveAs ) );
	Connect( wxID_CLOSE,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnClose ) );
	Connect( wxID_ABOUT,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnAbout ) );

	toolbar->AddButton( ID_IMPORT, "Import", wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ) );
	toolbar->AddButton( ID_EXPORT, "Export", wxImage( "../Resource/export.png"), "Export" );
	toolbar->AddButton( ID_CAPTURE, "Capture", wxImage("../Resource/screenshot.png"));


	Connect( ID_IMPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnImport ) );
	Connect( ID_EXPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnExport ) );
	Connect(ID_CAPTURE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

	//wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	//wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );

	wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );
	operation->AddToggleButton( ID_CAMERA_TRANSLATE,	"Camera",	wxImage("../Resource/view.png") );
	operation->AddToggleButton( ID_LIGHT_TRANSLATE,	"Light",	wxImage("../Resource/star.png") );
	operation->AddToggleButton( ID_CAMERA_FIT,		"Zoom",		wxImage("../Resource/zoom.png") );
	operation->AddToggleButton( ID_POLYGON_TRANSLATE, "Move",		wxImage("../Resource/8-direction.png") );
	operation->AddToggleButton( ID_POLYGON_ROTATE,	"Rotate",	wxImage("../Resource/3D-X-Axis-Rotation.png") );
	operation->AddToggleButton( ID_POLYGON_SCALE,		"Scale",	wxImage("../Resource/8-direction.png") );

	Connect( ID_CAMERA_FIT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraFit ) );
	Connect( ID_LIGHT_TRANSLATE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnLightTranslate ) );
	Connect( ID_POLYGON_TRANSLATE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonTranslate ) );
	Connect( ID_POLYGON_SCALE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonScale ) );
	Connect( ID_POLYGON_ROTATE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotate ) );

	wxRibbonPanel *renderingPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Rendering") );
	wxRibbonButtonBar* rendering = new wxRibbonButtonBar( renderingPanel );
	rendering->AddButton( ID_RENDERING_WIREFRAME, "WireFrame", wxImage("../Resource/wireframe.png") );
	rendering->AddButton( ID_RENDERING_PHONG,	"Phong", wxImage("../Resource/surface.png"));
	rendering->AddButton( ID_RENDERING_FLAT,	"Flat", wxImage("../Resource/surface.png") );
	rendering->AddButton( ID_RENDERING_NORMAL,	"Normal", wxImage("../Resource/arrow-1-down-right.png"));
	rendering->AddButton( ID_RENDERING_POINT,	"Point", wxImage("../Resource/point.png"));

	Connect( ID_RENDERING_WIREFRAME,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnWireFrame ) );
	Connect( ID_RENDERING_PHONG,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPhong ) );
	Connect( ID_RENDERING_FLAT,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFlat ) );
	Connect( ID_RENDERING_NORMAL,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnNormal) );
	Connect( ID_RENDERING_POINT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPoint) );


	wxRibbonPanel* modelingPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Modeling"));
	wxRibbonButtonBar* modelingBar = new wxRibbonButtonBar( modelingPanel );
	modelingBar->AddButton( ID_CREATE_TRIANGLE, "Triangle", wxImage("../Resource/triangle.png") );
	modelingBar->AddHybridButton( ID_CREATE_QUAD,		"Quad", wxImage("../Resource/quad.png") );
	modelingBar->AddHybridButton(ID_CREATE_CIRCLE, "Circle", wxImage("../Resource/quad.png"));
	modelingBar->AddHybridButton(ID_CREATE_SPHERE, "Sphere", wxImage("../Resource/quad.png"));
	modelingBar->AddHybridButton(ID_CREATE_CYLINDER, "Cylinder", wxImage("../Resource/quad.png"));
	
	Connect( ID_CREATE_TRIANGLE,	wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateTriangle) );
	Connect( ID_CREATE_QUAD,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateQuad) );
	Connect( ID_CREATE_QUAD,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateQuadConfig));
	Connect( ID_CREATE_CIRCLE,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateCircle) );
	Connect( ID_CREATE_CIRCLE,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateCircleConfig));
	Connect( ID_CREATE_SPHERE,		wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateSphere) );
	Connect( ID_CREATE_SPHERE,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateSphereConfig));
	Connect( ID_CREATE_CYLINDER,	wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateCylinder) );

	wxRibbonPanel* animationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Movie") );
	wxRibbonButtonBar *toolbar2 = new wxRibbonButtonBar( animationPanel );
	toolbar2->AddButton( wxID_ANY, "Play", wxImage("../Resource/MD-play.png") );
	toolbar2->AddButton( wxID_ANY, "Stop", wxImage("../Resource/MD-stop.png") );

	wxRibbonPanel *helpPanel = new wxRibbonPanel(page, wxID_ANY, wxT("ヘルプ"));
	wxRibbonButtonBar* helpToolBar = new wxRibbonButtonBar(helpPanel);
	helpToolBar->AddButton(wxID_ABOUT, "About", wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(32, 32)), "このソフトについて");

	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));


	bar->Realize();

	Connect( ID_LOCALE,		wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnLocale ) );
	

	const int width = 1024;//720;
	const int height = 512;////480;

	view = new View( this, width, height );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	polygonProperty = new PolygonProperty( this, wxSize( 300, 100), materials );
	materialProperty = new MaterialProperty( this, wxSize( 300, 100) );
	lightProperty = new LightProperty( this, wxSize( 300, 100  ) );

	wxSizer *vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );

	polygonTree = new PolygonTree( this, wxPoint( 0, 0 ), wxSize( 300, 100 ), polygonProperty, polygons, materials );
	materialTree = new MaterialTree( this, wxPoint( 0, 300 ), wxSize( 300, 100), materialProperty, &materials);
	lightTree= new LightTree( this, wxPoint( 0, 600 ), wxSize( 300, 100 ), lightProperty, &lights );

	wxSizer* rSizer = new wxBoxSizer( wxVERTICAL );
	rSizer->Add( polygonTree, 0, wxEXPAND );
	rSizer->Add( materialTree, 0, wxEXPAND );
	rSizer->Add( lightTree, 0, wxEXPAND );

	rSizer->Add( polygonProperty, 0, wxEXPAND );
	rSizer->Add( materialProperty, 0, wxEXPAND );
	rSizer->Add( lightProperty, 0, wxEXPAND );

	hSizer->Add( rSizer, 0, wxEXPAND );
	hSizer->Add(view, 0, wxEXPAND);


	vSizer->Add( bar, 0, wxEXPAND );
	vSizer->Add( hSizer, 0, wxEXPAND );

	//sizer->Add( tree, 0, wxEXPAND );

	polygonTree->build();
	lightTree->build();

	SetSizer( vSizer );
	
	Show();
}

Frame::~Frame()
{
	clear();
}

void Frame::clear()
{
	for ( PolygonGroup& g : polygons ) {
		Graphics::Polygon* p = g.getPolygon();
		delete p;
	}
	polygons.clear();
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

	polygonTree->build();
	materialTree->build();
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

void Frame::OnCameraTranslate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::CameraTranslate );
}

void Frame::OnPolygonRotate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::PolygonRotate );
}

void Frame::OnLightTranslate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::LightTranslate );
}

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

		OBJFile obj;
		const bool isOK = obj.read( path.ToStdString(), name.ToStdString() );
		if( isOK ) {
			wxMessageBox( wxT("インポートに成功しました。") );
		}
		else {
			wxMessageBox( wxT("インポートに失敗しました。"), wxEmptyString, wxICON_WARNING );
			return;
		}
		//model->getPolygonModel()->polygons = obj.getPolygons();
		//const MTLFile& mtl = obj.getMTLFile();
		view->Refresh();

		polygonTree->build();
		materialTree->build();

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

		PolygonFactory factory;
		PolygonGroupList g = factory.create(file);
		polygons.insert(polygons.end(), g.begin(), g.end());
		view->Refresh();

		polygonTree->build();
		materialTree->build();

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
	view->setMode( View::PolygonTranslate );
}

void Frame::OnPolygonScale( wxRibbonButtonBarEvent& e)
{
	view->setMode( View::PolygonScale );
}

void Frame::OnWireFrame( wxRibbonButtonBarEvent& e)
{
	view->setRenderingMode(View::RenderingMode::WireFrame);
	view->Refresh();
}

void Frame::OnPhong( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::Phong );
	view->Refresh();
}

void Frame::OnFlat( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::Flat );
	view->Refresh();
}

void Frame::OnNormal(wxRibbonButtonBarEvent&)
{
	view->setRenderingMode( View::RenderingMode::Normal );
	view->Refresh();
}

void Frame::OnPoint(wxRibbonButtonBarEvent&)
{
	view->setRenderingMode(View::RenderingMode::Point);
	view->Refresh();
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

void Frame::OnCreateQuad(wxRibbonButtonBarEvent& e)
{
	polygons.push_back( Polygon::createQuad(1.0, 1.0) );

	polygonTree->build();
}

void Frame::OnCreateQuadConfig(wxRibbonButtonBarEvent& e)
{
	QuadConfigDialog dialog(this);
	dialog.ShowModal();
}

void Frame::OnCreateTriangle(wxRibbonButtonBarEvent& e)
{
	polygons.push_back( Polygon::createTriangle() );
	polygonTree->build();
}


void Frame::OnCreateCircle(wxRibbonButtonBarEvent& e)
{
	polygons.push_back(Polygon::createCircle(1.0f, circleDivideAngle));
	polygonTree->build();
}

void Frame::OnCreateCircleConfig(wxRibbonButtonBarEvent& e)
{
	CircleConfigDialog dialog(this);
	int ret = dialog.ShowModal();
	if (ret == wxID_OK) {
		circleDivideAngle = dialog.getDivideAngle();
	}
}


void Frame::OnCreateSphere(wxRibbonButtonBarEvent& e)
{
	Graphics::Polygon* p = new Graphics::Polygon();
	p->setName( "sphere" );
	Vector3dVector positions;
	Face f;
	std::vector<unsigned int> vertexIds;
	int i = 0;
	for (float vAngle = 0.0; vAngle < 180.0; vAngle += 30.0) {
		for (float angle = 0.0; angle < 360.0; angle += 60.0) {
			const float rad = angle * Tolerances::getPI() / 180.0f;
			const float radius = ::sin(vAngle * Tolerances::getPI() / 180.0);
			const float z = ::sin(vAngle * Tolerances::getPI() / 180.0f);
			positions.push_back(Vector3d(std::sin(rad) * radius, std::cos(rad) * radius, z ));
			vertexIds.push_back(i++);
		}
	}
	f.setVertexIds(vertexIds);
	p->setPositions( positions );

	p->setFaces( {f} );
	polygons.push_back(p);

	polygonTree->build();

}

void Frame::OnCreateSphereConfig(wxRibbonButtonBarEvent& e)
{
	//const int num = wxGetNumberFromUser("Divide Number", wxEmptyString, wxEmptyString, 3, 360);
	sphereConfigDialog->ShowModal();
}

void Frame::OnCreateCylinder(wxRibbonButtonBarEvent& e)
{
	polygons.push_back( Polygon::createCylinder( 1.0f, 1.0f));
	polygonTree->build();

}
