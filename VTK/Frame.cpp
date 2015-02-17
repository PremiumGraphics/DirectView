#include <stdafx.h>
#include <wx/aboutdlg.h>

#include "Frame.h"
#include "View.h"

#include "VTKPropertyGrid.h"
#include "VTKTree.h"
#include "../IO/AVSUCDFile.h"
#include "../IO/AVSFLDFile.h"
#include "../IO/STLFile.h"
#include "../IO/VTKObjectFactory.h"

#include "../Math/Vector3d.h"
#include "../Math/Box.h"

class AppInfo {
public:
	static std::string getProductName() { return "Direct View"; }

	#define DIRECT_VIEW_MAJOR_VERSION 0
	#define DIRECT_VIEW_MINOR_VERSION 6
	#define DIRECT_VIEW_PATCH_VERSION 1


	static std::string getVersionStr()
	{
		return std::to_string( DIRECT_VIEW_MAJOR_VERSION ) + "." + std::to_string( DIRECT_VIEW_MINOR_VERSION ) + "." + std::to_string( DIRECT_VIEW_PATCH_VERSION );
	}

	static std::string getReleaseDateStr()
	{
		const int year = 2015;
		const int month = 1;
		const int day = 30;
		return std::to_string( year ) + std::to_string( month ) + std::to_string( day );
	}

};

using namespace Crystal::Math;
using namespace Crystal::IO;
using namespace Crystal::App;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_RENDERING_WIREFRAME,
	ID_RENDERING_VECTOR,
	ID_RENDERING_POINT,
	ID_RENDERING_SURFACE,

	ID_RENDERING_FAST_POINT,

	ID_CAMERA_FIT,
	ID_CAPTURE,

	ID_FILE_GENERATE,
	//ID_VIEW_REFRESH,
};

Frame::Frame()
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxEmptyString)
{
	this->SetTitle( AppInfo::getProductName() + " " + AppInfo::getVersionStr() );

    wxRibbonBar* bar = new wxRibbonBar
		(
		this,
		wxNewId(),
		wxDefaultPosition,
		wxDefaultSize
		);

	bar->SetArtProvider( new wxRibbonAUIArtProvider );

	//Connect( wxEVT_SIZE, wxSizeEventHandler( Frame::OnSize ) );

	wxRibbonPage* page = new wxRibbonPage( bar, wxNewId(), wxT("VTK") );
	{
		wxRibbonPanel *filePanel = new wxRibbonPanel( page, wxID_ANY, wxT("ファイル") );
		wxRibbonButtonBar *toolbar = new wxRibbonButtonBar( filePanel );

		toolbar->AddButton( wxID_NEW, "New", wxArtProvider::GetBitmap( wxART_NEW, wxART_OTHER, wxSize( 32, 32 ) ), "新規" );
		toolbar->AddButton( wxID_OPEN, "Open", wxArtProvider::GetBitmap( wxART_FILE_OPEN, wxART_OTHER, wxSize( 32, 32 ) ), "ファイルを開く" );
		toolbar->AddButton( wxID_CLOSE, "Exit", wxImage("../Resource/cancel.png"), "終了" );

		Connect( wxID_NEW,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnNew ) );
		Connect( wxID_OPEN,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFileOpen ) );
		//Connect( wxID_SAVE,		wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileSave ) );
		//Connect( wxID_SAVEAS,	wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileSaveAs ) );
		Connect( wxID_CLOSE,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnClose ) );
	}

	{
		wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("カメラ") );
		wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );
		//operation->AddTool( ID_CAMERA_TRANSLATE, bitmap("view.png"),  "Camera" );
		operation->AddButton( ID_CAMERA_FIT, "Fit", wxImage("../Resource/zoom.png"), "フィット" );
		operation->AddButton( ID_CAPTURE, "Capture", wxImage("../Resource/screenshot.png"), "画面保存" );

		Connect( ID_CAMERA_FIT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraFit ) );
		Connect( ID_CAPTURE,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCapture ) );
	}

	{
		wxRibbonPanel *renderingPanel = new wxRibbonPanel( page, wxID_ANY, wxT("描画") );
		wxRibbonButtonBar* rendering = new wxRibbonButtonBar( renderingPanel );
		
		//rendering->AddTool( ID_VIEW_REFRESH, wxImage("../Resource/3D-X-Axis-Rotation.png"), "描画適用" );
		//rendering->AddSeparator();

		rendering->AddButton( ID_RENDERING_WIREFRAME, "Wire", wxImage( "../Resource/wireframe.png"), "ワイヤフレーム描画" );
		rendering->AddButton( ID_RENDERING_SURFACE, "Surface", wxImage( "../Resource/surface.png"), "サーフェス描画" );
		rendering->AddHybridButton( ID_RENDERING_VECTOR, "Vector", wxImage( "../Resource/arrow-1-down-right.png"), "ベクトル描画" );
		rendering->AddHybridButton( ID_RENDERING_POINT, "Point", wxImage( "../Resource/point.png"), "ポイント描画" );
		
		//Connect( ID_VIEW_REFRESH,			wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnViewRefresh ) );
		Connect( ID_RENDERING_WIREFRAME,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnWireFrameRendering ) );
		Connect( ID_RENDERING_SURFACE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnSurfaceRendering ) );
		Connect( ID_RENDERING_VECTOR,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnVectorRendering ) );
		Connect( ID_RENDERING_VECTOR,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnVectorRenderingDropDown ) );
		Connect( ID_RENDERING_POINT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPointRendering ) );
		Connect( ID_RENDERING_POINT,		wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPointRenderingDropDown ) );
	}

	/*
	{
		wxRibbonPanel *panel = new wxRibbonPanel( page, wxID_ANY, wxT("高速描画" ) );
		wxRibbonButtonBar* bar = new wxRibbonButtonBar( panel );

		bar->AddButton( ID_RENDERING_FAST_WIREFRAME, "Wire", wxImage( "../Resource/wireframe.png"), "ワイヤフレーム描画" );
		bar->AddButton( ID_RENDERING_FAST_SURFACE, "Surace", wxImage( "../Resource/surface.png"), "サーフェス描画" ); 
		bar->AddButton( ID_RENDERING_FAST_POINT, "Point", wxImage("../Resource/point.png"), "ポイント描画" );
		Connect( ID_RENDERING_FAST_WIREFRAME,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFastWireFrameRendering ) );
		Connect( ID_RENDERING_FAST_SURFACE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFastSurfaceRendering ) );
		Connect( ID_RENDERING_FAST_POINT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnFastPointRendering ) );
	}
	*/

	{
		wxRibbonPanel *helpPanel = new wxRibbonPanel( page, wxID_ANY, wxT("ヘルプ") );
		wxRibbonButtonBar* helpToolBar = new wxRibbonButtonBar( helpPanel );
		helpToolBar->AddButton( wxID_ABOUT, "About", wxArtProvider::GetBitmap( wxART_INFORMATION, wxART_OTHER, wxSize( 32, 32 )), "このソフトについて" );

		Connect( wxID_ABOUT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnAbout ) );
	}

	/*
	{
		wxRibbonPanel *developPanel = new wxRibbonPanel( page, wxID_ANY, wxT("開発者用") );
		wxRibbonToolBar* developToolBar = new wxRibbonToolBar( developPanel );
		developToolBar->AddTool( ID_FILE_GENERATE, wxBitmap( 24,24 ), "ファイル生成" );

		Connect( ID_FILE_GENERATE,			wxEVT_RIBBONTOOLBAR_CLICKED, wxRibbonToolBarEventHandler( Frame::OnFileGenerate ) );
	}
	*/

	bar->Realize();

	camera.setNear( 1.0f );
	camera.setFar( 10.0f );

	const int width = 1600;//720;
	const int height = 900;////480;
	
	//int args[] = {WX_GL_RGBA, WX_GL_DOUBLEBUFFER, WX_GL_DEPTH_SIZE, 16, 0};
	view = new View( this, nullptr, width, height );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	/*
	{
		IO::VTKFile file;
		file.read( IO::VTKSampleSource::getStructuredPoints() );
		factory.create( file );
	}

	{
		IO::VTKFile file;
		file.read( IO::VTKSampleSource::getPolyData() );
		factory.create( file );
	}
	*/

	wxSizer* vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );
	wxSizer* lSizer = new wxBoxSizer( wxVERTICAL );

	VTKPropertyGrid* propertyGrid = new VTKPropertyGrid( this, view, wxPoint( 0, 300 ), wxSize( 300, 300 ) );
	tree = new VTKTree( this, view, wxPoint( 0, 300 ), wxSize( 300, 300 ), &factory, propertyGrid );

	tree->build();

	hSizer->Add( lSizer, 0, wxEXPAND );
	hSizer->Add( view, 0, wxEXPAND );

	lSizer->Add( tree, 0, wxEXPAND );
	lSizer->Add( propertyGrid, 0, wxEXPAND );

	vSizer->Add( bar );	
	vSizer->Add( hSizer, 0, wxEXPAND );

	SetSizer( vSizer );

	view->setRenderingBlocks();

	Show();
}

Frame::~Frame()
{
}

void Frame::OnNew( wxRibbonButtonBarEvent& e )
{
	const int ret = wxMessageBox(wxT("削除してよろしいですか？"), wxEmptyString, wxYES_NO, this );

	if( ret == wxYES ) {
		factory.clear();
		tree->build();
		view->Refresh();
	}
}

void Frame::OnClose( wxRibbonButtonBarEvent& )
{
	const int ret = wxMessageBox(wxT("終了してよろしいですか？"), wxEmptyString, wxYES_NO, this );

	if( ret == wxYES ) {
		Close(true);
	}
}

/*
void Frame::OnAbout( wxRibbonToolBarEvent& )
{
	wxMessageBox( wxT( "CG Studio 0.10" ) );
}
*/

/*
void Frame::OnSize( wxSizeEvent& e )
{
	wxFrame::OnSize( e );
	tree->SetPosition( wxPoint( 1300, 0 ) );
}
*/

#include "../IO/VTKFile.h"

void Frame::OnFileOpen( wxRibbonButtonBarEvent& e )
{
	const wxString& filename = wxFileSelector
		(
		wxT("Import"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"VTK files (*.vtk)|*.vtk|"
		"AVS UCD files (*.inp)|*.inp",
		//"AVS Field files (*.fld)|*.fld",
		wxFD_OPEN
		);
	
	if ( filename.empty() ) {
		return;
	}

	if( filename.EndsWith( ".vtk") ) {
		IO::VTKFile file;
		const bool isOk = file.read( filename.ToStdString() );
		if( !isOk ) {
			wxMessageBox( wxT("読み込みに失敗しました。") );
			return;
		}
		else {
			factory.clear();
			factory.create( file );
			wxMessageBox( wxT("読み込みに成功しました。") );
			view->setRenderingBlocks();
			view->Refresh();
		}
	}
	else if( filename.EndsWith( ".inp" ) ) {
		Crystal::IO::AVSUCDFile file;
		const bool isOk = file.read( filename.ToStdString() );
		if( !isOk ) {
			wxMessageBox( wxT("読み込みに失敗しました。") );
			return;
		}
		else {
			factory.clear();
			VTKObject* object = factory.create( file );
			wxMessageBox( wxT("読み込みに成功しました。") );
			view->setRenderingBlocks();
			view->Refresh();
			//objects.push_back( object );
		}

	}
	/*
	else if( filename.EndsWith( ".fld" ) ) {
		wxFileName name = filename;
		const wxString& path = name.GetPath();
		Crystal::IO::AVSFLDFile file;
		const bool isOk = file.read( path.ToStdString(), name.GetName().ToStdString() + "." + name.GetExt().ToStdString() ); //, model );
		if( !isOk ) {
			wxMessageBox( wxT("読み込みに失敗しました。") );
			return;
		}
		else {
			factory.clear();
			factory.create( file );
			wxMessageBox( wxT("読み込みに成功しました。") );
			view->setRenderingBlocks();
			view->Refresh();
		}
	}
	*/
	//OnCameraFit( e );


	tree->build();
}

void Frame::OnWireFrameRendering( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::WireFrame );
	view->Refresh();
}

void Frame::OnSurfaceRendering( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::Surface );
	view->Refresh();
}

void Frame::OnVectorRendering( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::VectorMap );
	view->Refresh();
}

#include "wx/numdlg.h"
class VectorConfigPanel : public wxDialog
{
public:
	VectorConfigPanel(wxWindow* parent );

private:
	void OnOk( wxCommandEvent& e );

	void OnCancel( wxCommandEvent& e );

public:
	void setScale( const double s ) { this->scaleCtrl->SetValue( s ); }

	double getScale() const { return scaleCtrl->GetValue(); }

	void setWidth( const double w ) { this->widthCtrl->SetValue( w ); }

	double getWidth() const { return widthCtrl->GetValue(); }

private:
	wxSpinCtrlDouble* scaleCtrl;
	wxSpinCtrlDouble* widthCtrl;

	wxButton* okButton;
	wxButton* cancelButton;
};

VectorConfigPanel::VectorConfigPanel( wxWindow* parent ) :
	wxDialog( parent, wxNewId(), "ベクトル描画設定", wxDefaultPosition, wxSize( 500, 500 ) )
{
	okButton = new wxButton( this, wxID_OK, "OK", wxPoint( 300, 300 ) );
	cancelButton = new wxButton( this, wxID_CANCEL, "Cancel", wxPoint( 300, 400 ) );

	new wxStaticText( this, wxID_ANY, "ベクトル表示倍率", wxPoint( 0, 100 ) );
	scaleCtrl = new wxSpinCtrlDouble( this, wxNewId(), "1", wxPoint( 100, 100 ) );

	new wxStaticText( this, wxID_ANY, "ラインの幅", wxPoint( 0, 200 ) );
	widthCtrl = new wxSpinCtrlDouble( this, wxNewId(), "1", wxPoint( 100, 200 ) );

	//Connect( wxID_OK, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( VectorConfigPanel::OnOk ) );

	/*
	Connect( diffuseButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileCreatePanel::OnCreateDiffuse ) );

	Connect( fileSaveButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileCreatePanel::OnFileSave ) );
	*/
}

void VectorConfigPanel::OnOk( wxCommandEvent& )
{
	this->SetReturnCode( wxID_OK );
	Close();
}

void Frame::OnVectorRenderingDropDown( wxRibbonButtonBarEvent& )
{
	/*
	const int v = wxGetNumberFromUser( wxEmptyString, wxEmptyString, wxEmptyString, 1, 1, 100 );
	if( v != -1 ) {
		view->vectorScale = v;
	}
	*/
	VectorConfigPanel panel( this );
	panel.setScale( view->vectorScale );
	panel.setWidth( view->lineWidth );
	panel.ShowModal();

	if( panel.GetReturnCode() == wxID_OK ) {
		view->vectorScale = panel.getScale();
		view->lineWidth = panel.getWidth();
		view->setRenderingBlocks();
		view->Refresh();
	}
}

void Frame::OnPointRendering( wxRibbonButtonBarEvent& )
{
	view->setRenderingMode( View::RenderingMode::PointSprite );
	view->Refresh();
}


void Frame::OnPointRenderingDropDown( wxRibbonButtonBarEvent& )
{
	const int v = wxGetNumberFromUser( "ポイントのサイズ", wxEmptyString, wxEmptyString, view->pointSize, 1, 100 );
	if( v != -1 ) {
		view->pointSize = v;
		view->Refresh();
	}
}

void Frame::OnCameraFit( wxRibbonButtonBarEvent& e )
{
	camera.setPos( Vector3d( 0.0, 0.0, 0.0 ) );
	camera.setAngle( Vector3d( 0.0, 0.0, 0.0 ) );
	
	for( IO::VTKObject* object : factory.getSelectedObjects() ) {
		const Box& bb = object->getBoundingBox();
		const Vector3d& center = bb.getCenter();
		camera.setPos( -1.0 * center );
		const float minZ = bb.getMinZ();
		//camera.pos.setZ( camera.pos.getZ() - minZ );
	}
	
	view->Refresh();
}

void Frame::OnCapture( wxRibbonButtonBarEvent& e )
{
	const int width = view->GetClientSize().GetWidth();
	const int height = view->GetClientSize().GetHeight();
	std::vector< GLubyte > pixels( width * height * 4 );
	glReadBuffer(GL_FRONT);
	glReadPixels( 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, &(pixels.front()) );
	wxImage image( width, height );

	int index = 0;

	for( int y = height-1; y >= 0; --y ) {
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
		"BMP files (*.bmp)|*.bmp|"
		"PNG files (*.png)|*.png",
		wxFD_SAVE
		);

	if( filename.empty() ) {
		return;
	}
	image.SaveFile( filename, wxBITMAP_TYPE_BMP );
}

void Frame::OnViewRefresh( wxRibbonToolBarEvent& e )
{
	view->setRenderingBlocks();
	view->Refresh();
}


void Frame::OnAbout(wxRibbonButtonBarEvent& )
{
	/*
    wxAboutDialogInfo info;
    info.SetName("Direct View Beta");
    info.SetVersion(_("0.5.0"));
    //info.SetDescription(_("This program does something great."));
    info.SetCopyright(_T("(C) 2014 株式会社プレミアムグラフィクス <premiumgraphics2015@gmail.com>"));

    wxAboutBox(info);
	*/
	wxMessageBox(AppInfo::getProductName() + " " + AppInfo::getVersionStr() + "\n" + "Release" + AppInfo::getReleaseDateStr() );
}

#include "wx/numdlg.h"

class FileCreatePanel : public wxDialog
{
public:
	FileCreatePanel(wxWindow* parent, VTKObjectFactory& factory);

private:
	void OnCreateHydrogen( wxCommandEvent& e );

	void OnCreateDiffuse( wxCommandEvent& e );

	void OnFileSave( wxCommandEvent& e );

private:
	wxChoice* gridTypeChoice;

	wxButton* fileSaveButton;

	wxButton* tornadoButton;

	wxButton* diffuseButton;

	VTKObjectFactory& factory;
};

FileCreatePanel::FileCreatePanel(wxWindow* parent, VTKObjectFactory& factory) :
	wxDialog( parent, wxNewId(), "ファイル作成", wxDefaultPosition, wxSize( 500, 500 ) ),
	factory( factory )
{
	wxArrayString strs;
	strs.push_back( "構造格子" );
	strs.push_back( "非構造格子" );
	gridTypeChoice = new wxChoice( this, wxNewId(), wxPoint( 100, 100 ), wxDefaultSize, strs );

	tornadoButton = new wxButton( this, wxNewId(), "竜巻", wxPoint( 100, 300 ) );
	Connect( tornadoButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileCreatePanel::OnCreateHydrogen ) );

	diffuseButton = new wxButton( this, wxNewId(), "拡散", wxPoint( 100, 400 ) );
	Connect( diffuseButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileCreatePanel::OnCreateDiffuse ) );

	fileSaveButton = new wxButton( this, wxNewId(), "ファイル出力", wxPoint( 300, 300 ) );
	Connect( fileSaveButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FileCreatePanel::OnFileSave ) );
}

#include "../IO/Volume.h"

void FileCreatePanel::OnCreateHydrogen( wxCommandEvent& e )
{
	VTKAttributePart attr;
	VTKAttributePart_ pointAttr;
	VTKScalarsVector scalars;
	
	Volume volume( 32, 32, 32 );
	const std::vector< float >& values = volume.createHydrogenVolume();
	VTKScalars s;
	s.setValues( values );
	scalars.push_back( s );
	pointAttr.setScalars( scalars );
	attr.setPointAttribute( pointAttr );
	VTKGeometryPart geom;
	VTKStructuredPoints points;
	points.setAspect( Vector3d( 1.0, 1.0, 1.0 ) );
	points.setDimensions( 32, 32, 32 );
	points.setOrigin( Vector3d( 0.0, 0.0, 0.0 ) );
	points.toPoints();
	geom.setGeometry( &points );
	VTKFile file;
	file.setGeometryPart( geom );
	file.setAttributePart( attr );
	VTKObject* object = factory.create( file );
}

void FileCreatePanel::OnCreateDiffuse( wxCommandEvent& e )
{
	const wxString& filename = wxFileSelector
		(
		wxT("ファイル出力"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"VTK files (*.vtk)|*.vtk",
		wxFD_SAVE
		);
	
	if ( filename.empty() ) {
		return;
	}


	VTKFile file;
	file.setCylinderData();
	std::ofstream stream( filename.ToStdString() );
	file.write(stream);
}

void FileCreatePanel::OnFileSave( wxCommandEvent& e )
{
	const wxString& filename = wxFileSelector
		(
		wxT("ファイル出力"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		"VTK files (*.vtk)|*.vtk",
		wxFD_SAVE
		);
	
	if ( filename.empty() ) {
		return;
	}


	VTKFile file;
	file.setDiffuseData();
	std::ofstream stream( filename.ToStdString() );
	file.write(stream);
}

void Frame::OnFileGenerate( wxRibbonToolBarEvent& )
{
	//const int dim = wxGetNumberFromUser( "空間の次元数", wxEmptyString, wxEmptyString, 1, 1, 3 ); 
	FileCreatePanel dialog = FileCreatePanel( this, factory );
	dialog.ShowModal();
	tree->build();
	view->Refresh();
}