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

	ID_RENDERING_WIREFRAME,
	ID_RENDERING_FLAT,
	ID_RENDERING_PHONG,

	ID_CAMERA_FIT,

	ID_CAPTURE,
};

#include "PolygonTree.h"

Frame::Frame()
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxT("CG Studio 0.10"))
{
    wxRibbonBar* bar = new wxRibbonBar
		(
		this,
		wxNewId(),
		wxDefaultPosition,
		wxDefaultSize
		);

	bar->SetArtProvider( new wxRibbonAUIArtProvider );

	Connect( ID_CAMERA_TRANSLATE,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnCameraTranslate ) );

	wxRibbonPage* page = new wxRibbonPage( bar, wxNewId(), wxT("Polygon") );
	//wxRibbonPanel* panel = new wxRibbonPanel( page, wxID_ANY, wxT("Polygon") );

	wxRibbonPanel *filePanel = new wxRibbonPanel( page, wxID_ANY, wxT("File") );
	wxRibbonToolBar *toolbar = new wxRibbonToolBar( filePanel );

	toolbar->AddToggleTool( wxID_NEW, wxArtProvider::GetBitmap( wxART_NEW, wxART_OTHER, wxSize( 32, 32 ) ), "New");
	toolbar->AddToggleTool( wxID_OPEN, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ), "Open");
	toolbar->AddToggleTool( wxID_SAVE, wxImage("../Resource/save.png"), "Save");
	toolbar->AddToggleTool( wxID_ANY, wxArtProvider::GetBitmap( wxART_FILE_SAVE_AS, wxART_OTHER, wxSize( 32, 32 ) ), "Save as");
	toolbar->AddToggleTool( wxID_CLOSE, wxImage("../Resource/cancel.png"), "Close" );
	toolbar->AddSeparator();

	Connect( wxID_NEW,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnNew ) );
	Connect( wxID_OPEN,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileOpen ) );
	Connect( wxID_SAVE,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileSave ) );
	Connect( wxID_SAVEAS,	wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileSaveAs ) );
	Connect( wxID_CLOSE,	wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnClose ) );
	Connect( wxID_ABOUT,	wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnAbout ) );

	toolbar->AddToggleTool( ID_IMPORT, wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ), "Import" );
	toolbar->AddToggleTool( ID_EXPORT, wxImage( "../Resource/export.png"), "Export" );

	Connect( ID_IMPORT,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnImport ) );
	Connect( ID_EXPORT,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnExport ) );

	//wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	//wxRibbonToolBar* operation = new wxRibbonToolBar( operationPanel );

	wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	wxRibbonToolBar* operation = new wxRibbonToolBar( operationPanel );
	operation->AddSeparator();
	operation->AddTool( ID_CAMERA_TRANSLATE, wxImage("../Resource/view.png"),  "Camera" );
	operation->AddTool( ID_LIGHT_TRANSLATE, wxImage("../Resource/star.png"), "Light" );
	operation->AddTool( ID_CAMERA_FIT, wxImage("../Resource/zoom.png"), "Zoom" );
	operation->AddTool( ID_POLYGON_TRANSLATE, wxImage("../Resource/8-direction.png"), "Move");
	operation->AddTool( ID_POLYGON_ROTATE, wxImage("../Resource/3D-X-Axis-Rotation.png"), "Rotate" );
	operation->AddTool( ID_POLYGON_SCALE, wxImage("../Resource/8-direction.png"), "Scale");
	operation->AddTool( ID_CAPTURE, wxImage( "../Resource/screenshot.png"), "Capture" );

	Connect( ID_CAMERA_FIT,	wxEVT_RIBBONTOOLBAR_CLICKED,	wxRibbonToolBarEventHandler( Frame::OnCameraFit ) );
	Connect( ID_CAPTURE,	wxEVT_RIBBONTOOLBAR_CLICKED,	wxRibbonToolBarEventHandler( Frame::OnCapture ) );
	Connect( ID_LIGHT_TRANSLATE,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnLightTranslate ) );
	Connect( ID_POLYGON_TRANSLATE,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnPolygonTranslate ) );
	Connect( ID_POLYGON_SCALE,			wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnPolygonScale ) );
	Connect( ID_POLYGON_ROTATE,			wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnPolygonRotate ) );

	wxRibbonPanel *renderingPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Rendering") );
	wxRibbonToolBar* rendering = new wxRibbonToolBar( renderingPanel );
	rendering->AddTool( ID_RENDERING_WIREFRAME, wxImage("../Resource/8-direction.png"), "WireFrame");
	rendering->AddTool( ID_RENDERING_PHONG, wxImage("../Resource/4-direction.png"),	"Phong");
	rendering->AddTool( ID_RENDERING_FLAT, wxImage("../Resource/4-direction.png"),	"Flat");

	Connect( ID_RENDERING_WIREFRAME,	wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnWireFrame ) );
	Connect( ID_RENDERING_PHONG,	wxEVT_RIBBONTOOLBAR_CLICKED,	wxRibbonToolBarEventHandler( Frame::OnPhong ) );
	Connect( ID_RENDERING_FLAT,		wxEVT_RIBBONTOOLBAR_CLICKED,	wxRibbonToolBarEventHandler( Frame::OnFlat ) );

	rendering->AddSeparator();

	wxRibbonPanel* animationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Movie") );
	wxRibbonToolBar *toolbar2 = new wxRibbonToolBar( animationPanel );
	toolbar2->AddTool( wxID_ANY, wxImage("../Resource/MD-play.png"), "Play");
	toolbar2->AddTool( wxID_ANY, wxImage("../Resource/MD-stop.png"), "Stop");
	toolbar2->AddSeparator();

	//toolbar2->AddTool( wxID_ANY, bitmap("MD-camera-video.png"), "SaveMovie");


	bar->Realize();

	Connect( ID_LOCALE,		wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::OnLocale ) );
	

	const int width = 1024;//720;
	const int height = 512;////480;

	view = new View( this, width, height );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	polygonProperty = new PolygonProperty( this, wxSize( 300, 100) );
	materialProperty = new MaterialProperty( this, wxSize( 300, 100) );
	lightProperty = new LightProperty( this, wxSize( 300, 100  ) );

	wxSizer *vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );

	polygonTree = new PolygonTree( this, wxPoint( 0, 0 ), wxSize( 300, 100 ), polygonProperty, polygons );
	materialTree = new MaterialTree( this, wxPoint( 0, 300 ), wxSize( 300, 100), materialProperty );
	lightTree= new LightTree( this, wxPoint( 0, 600 ), wxSize( 300, 100 ), lightProperty, lights );

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

	polygonTree->build( polygons );
	lightTree->build();

	SetSizer( vSizer );
	
	Show();
}

Frame::~Frame()
{
	for (Graphics::Polygon* p : polygons) {
		delete p;
	}
}

void Frame::OnNew( wxRibbonToolBarEvent& e )
{
	const int ret = wxMessageBox(wxT("モデルを保存しますか？"), wxEmptyString, wxYES_NO, this );

	if( ret == wxYES ) {
		OnFileSaveAs( e );
		return;
	}

	for (Graphics::Polygon* p : polygons) {
		delete p;
	}

	view->Refresh();

	polygonTree->build( polygons );
	materialTree->build();
}

void Frame::OnClose( wxRibbonToolBarEvent& )
{
	bool isChanged = true;
	if( isChanged ) {
		wxMessageBox(wxT("モデルが変更されています。終了しますか。"));
	}
	Close(true);
}

void Frame::OnAbout( wxRibbonToolBarEvent& )
{
	wxMessageBox( wxT( "CG Studio 0.10" ) );
}

#include "../IO/CGSFile.h"

void Frame::OnFileSave( wxRibbonToolBarEvent& )
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

void Frame::OnFileSaveAs( wxRibbonToolBarEvent& e )
{
	wxMessageBox("TODO");
}

void Frame::OnFileOpen( wxRibbonToolBarEvent& e )
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

void Frame::OnCameraTranslate( wxRibbonToolBarEvent& )
{
	view->setMode( View::CameraTranslate );
}

void Frame::OnPolygonRotate( wxRibbonToolBarEvent& )
{
	view->setMode( View::PolygonRotate );
}

void Frame::OnLightTranslate( wxRibbonToolBarEvent& )
{
//	model->getLightModel()->setSelectedLight( &( model->getLightModel()->getLights().front() ) );
	view->setMode( View::LightTranslate );
}

#include "../IO/PolygonFactory.h"

void Frame::OnImport( wxRibbonToolBarEvent& e )
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

		polygonTree->build( polygons );
		materialTree->build();

		OnCameraFit( e );
	}
	else if( ext == "stl" || ext == "STL" ) {
		STLFile file;
		const bool isOK = file.read( filename.ToStdString() );
		PolygonFactory factory;
		polygons.push_back( factory.create(file) );
		view->Refresh();

		polygonTree->build( polygons );
		materialTree->build();

		OnCameraFit( e );
	}
}


void Frame::OnExport( wxRibbonToolBarEvent& e )
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

void Frame::OnGLConfig( wxRibbonToolBarEvent& e )
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

void Frame::OnPolygonTranslate( wxRibbonToolBarEvent& )
{
	view->setMode( View::PolygonTranslate );
}

void Frame::OnPolygonScale( wxRibbonToolBarEvent& )
{
	view->setMode( View::PolygonScale );
}

void Frame::OnWireFrame( wxRibbonToolBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::WireFrame );
	view->Refresh();
}

void Frame::OnPhong( wxRibbonToolBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::Phong );
	view->Refresh();
}

void Frame::OnFlat( wxRibbonToolBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::Flat );
	view->Refresh();
}

void Frame::OnCameraFit( wxRibbonToolBarEvent& e )
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

void Frame::OnCapture( wxRibbonToolBarEvent& e )
{
	const int width = 1024;//GetClientSize().GetWidth();
	const int height = 512;//GetClientSize().GetHeight();
	std::vector< GLubyte > pixels( width * height * 4 );
	glReadPixels( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()) );
	wxImage image( width, height );

	int index = 0;

	for( int y = 0; y < height; ++y ) {
		for( int x = 0; x < width; ++x ) {
			image.SetRGB( x, y, pixels[ index ], pixels[ index + 1 ], pixels[ index + 2] );
			index += 4;
		}
	}

	const wxString& filename = wxFileSelector
		(
		wxT("Save"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"BMP files (*.bmp)|*.bmp",
		//"PNG files (*.png)|*.png",
		wxFD_SAVE
		);

	if( filename.empty() ) {
		return;
	}
	image.SaveFile( filename, wxBITMAP_TYPE_BMP );
}