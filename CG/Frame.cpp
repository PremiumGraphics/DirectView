#include <stdafx.h>

#include "Frame.h"

#include "View.h"


#include "wx/filename.h"

#include "VolumeDialog.h"
#include "MetaballDialog.h"
#include "RenderingDialog.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Model;
using namespace Crystal::UI;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_CAMERA,

	ID_IMPORT,
	ID_EXPORT,

	ID_GL_CONFIG,

	ID_SELECTED_MOVE,
	ID_SELECTED_CLEAR,
	ID_SELECTED_DELETE,

	ID_CREATE_METABALL,
	ID_CREATE_VOLUME,

	ID_RENDERING_WIREFRAME,

	ID_CAMERA_FIT,

	ID_CAPTURE,
};


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
	: /*wxMDIParentFrame*/wxFrame(NULL, wxID_ANY, wxEmptyString ),
	model(std::make_shared< MainModel<float> >())
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


	Connect( ID_IMPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnImport ) );
	Connect( ID_EXPORT,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnExport ) );
	Connect( ID_CAPTURE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

	wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );
	operation->AddButton( ID_CAMERA,	"Camera",	wxImage("../Resource/view.png") );
	operation->AddButton( ID_CAMERA_FIT,		"Fit",		wxImage("../Resource/zoom.png") );
	//operation->AddDropdownButton( ID_POLYGON, wxT("Other Polygon"), wxBitmap(hexagon_xpm), wxEmptyString);
	//operation->AddButton(ID_PICK_VERTEX, "Pick", wxImage("../Resource/8-direction.png"));

	Connect( ID_CAMERA,					wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraTranslate ) );
	Connect( ID_CAMERA_FIT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraFit ) );

	wxRibbonPanel* selectionPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Selection"));
	wxRibbonButtonBar* selection = new wxRibbonButtonBar(selectionPanel);
	selection->AddButton(ID_SELECTED_MOVE, "Move", wxBitmap(32, 32));
	selection->AddButton(ID_SELECTED_CLEAR, "Unselect", wxImage(32, 32));
	selection->AddButton(ID_SELECTED_DELETE, "Delete", wxImage(32, 32));

	Connect(ID_SELECTED_MOVE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnSelectedMove));
	Connect(ID_SELECTED_CLEAR,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnSelectedClear));
	Connect(ID_SELECTED_DELETE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnSelectedDelete));

	wxRibbonPanel *renderingPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Rendering") );
	wxRibbonButtonBar* rendering = new wxRibbonButtonBar( renderingPanel );
	rendering->AddButton( ID_RENDERING_WIREFRAME,	"Rendering", wxImage("../Resource/wireframe.png") );

	Connect( ID_RENDERING_WIREFRAME,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnRendering ) );
	//Connect( ID_RENDERING_WIREFRAME,	wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnWireFrameConfig));

	wxRibbonPanel* modelingPanel = new wxRibbonPanel(page, wxID_ANY, wxT("Modeling"));
	wxRibbonButtonBar* modelingBar = new wxRibbonButtonBar(modelingPanel);
	//modelingBar->AddHybridButton(ID_CREATE_SPHERE, "Sphere", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_METABALL, "Particle", wxImage(32, 32));
	modelingBar->AddButton(ID_CREATE_VOLUME,	"Grid", wxImage(32, 32));

	Connect(ID_CREATE_METABALL,			wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateMetaball));
	//Connect(ID_CREATE_METABALL,			wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnMetaballConfig));
	Connect(ID_CREATE_VOLUME,			wxEVT_RIBBONBUTTONBAR_CLICKED,			wxRibbonButtonBarEventHandler(Frame::OnCreateVolume));
	//Connect(ID_CREATE_VOLUME,			wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnVolumeConfig));


	wxRibbonPanel *helpPanel = new wxRibbonPanel(page, wxID_ANY, wxT("�w���v"));
	wxRibbonButtonBar* helpToolBar = new wxRibbonButtonBar(helpPanel);
	helpToolBar->AddButton(wxID_ABOUT, "About", wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(32, 32)), "���̃\�t�g�ɂ���");

	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));


	bar->Realize();
	
	const int width = 1600;//720;
	const int height = 900;////480;

	view = new View( this, width, height, model );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	wxSizer *vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );

	hSizer->Add( view, 0, wxEXPAND);


	vSizer->Add( bar, 0, wxEXPAND );
	vSizer->Add( hSizer, 0, wxEXPAND );


	SetSizer( vSizer );
	
	Show();

	setRendering();

}

Frame::~Frame()
{
	clear();
}

void Frame::clear()
{
	model->clear();
}

void Frame::OnNew( wxRibbonButtonBarEvent& e )
{
	const int ret = wxMessageBox(wxT("���f����ۑ����܂����H"), wxEmptyString, wxYES_NO, this );

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
		wxMessageBox(wxT("���f�����ύX����Ă��܂��B�I�����܂����B"));
	}
	Close(true);
}

void Frame::OnAbout( wxRibbonButtonBarEvent& )
{
	//wxMessageBox( wxT( "CG Studio 0.10" ) );

	wxMessageBox(AppInfo::getProductName() + " " + AppInfo::getVersionStr() + "\n" + "Release" + AppInfo::getReleaseDateStr());
}

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


	//CGSFile file;
	const bool isOk = false;//file.save( filename.ToStdString() );
	if( isOk ) {
		wxMessageBox( wxT("�ۑ����܂����B") );
	}
	else {
		wxMessageBox( wxT("�ۑ��Ɏ��s���܂����B") );
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
		wxMessageBox( wxT("�ǂݍ��݂Ɏ��s���܂����B") );
	}
	*/
}

void Frame::OnCameraTranslate( wxRibbonButtonBarEvent& )
{
	model->setUIMode(Model::UIMode::CAMERA_TRANSLATE);
}

void Frame::OnCreateLight( wxRibbonButtonBarEvent& )
{
}

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
			wxMessageBox( wxT("�C���|�[�g�ɐ������܂����B") );
		}
		else {
			wxMessageBox( wxT("�C���|�[�g�Ɏ��s���܂����B"), wxEmptyString, wxICON_WARNING );
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
			wxMessageBox(wxT("�C���|�[�g�ɐ������܂����B"));
		}
		else {
			wxMessageBox(wxT("�C���|�[�g�Ɏ��s���܂����B"), wxEmptyString, wxICON_WARNING);
			return;
		}

		//PolygonFactory model( model.getPolygonBuilder() );
		//PolygonSPtrList g = model.create(file);
		view->Refresh();

		OnCameraFit( e );
	}
	*/
}


void Frame::OnExport( wxRibbonButtonBarEvent& e )
{
	const wxString& filename = wxFileSelector
		(
		wxT("Export"),
		wxEmptyString,
		wxEmptyString,
		wxEmptyString,
		//"OBJ files (*.obj)|*.obj|"
		"STL files (*.stl)|*.stl",
		wxFD_SAVE
		);

	if( filename.empty() ) {
		return;
	}

	//wxFileName fn( filename );
	//wxString path = fn.GetPath( false );
	//wxString name = fn.GetName() + "."  + fn.GetExt();
	//const wxString& ext = fn.GetExt();

	std::string str;
	for (size_t i = 0; i < filename.Length(); ++i) {
		const char s = filename.GetChar(i);
		str += s;
	}
	model->doExport(str);
	/*
	if( ext == "stl" || ext == "STL" ) {
		const auto str = filename.ToStdString();
		//model->doExport(str);
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

#include "wx/numdlg.h"

void Frame::OnRendering( wxRibbonButtonBarEvent& e)
{
	WireframeConfigDialog dialog(this);
	RenderingConfig<float> rConfig = model->getRenderingConfig();
	dialog.set(rConfig);
	if (dialog.ShowModal() == wxID_OK) {
		rConfig = dialog.get();
		model->setRenderingConfig(rConfig);
		setRendering();
	}
	view->Refresh();
}

void Frame::OnCameraFit( wxRibbonButtonBarEvent& e )
{
	model->fitCamera();
	view->Refresh();
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

void Frame::OnCreateMetaball(wxRibbonButtonBarEvent& e)
{
	MetaballDialog dialog(this);
	dialog.set(model->getMetaballConfig());
	const auto result = dialog.ShowModal();
	if (result == wxID_OK) {
		model->setMetaballConfig(dialog.get());
	}
	model->createMetaball();
	setRendering();
}

void Frame::setRendering()
{
	model->setRendering();
	view->Refresh();

}

void Frame::OnSelectedMove(wxRibbonButtonBarEvent& e)
{
	model->setUIMode(Model::UIMode::SELECTED_TRANSLATE);
}

void Frame::OnSelectedClear(wxRibbonButtonBarEvent& e)
{
	model->clearSelected();
	setRendering();
}

void Frame::OnSelectedDelete(wxRibbonButtonBarEvent& e)
{
	model->deleteSelected();
	setRendering();
	//view->setMode(View::SCALE);
}

void Frame::OnCreateVolume(wxRibbonButtonBarEvent& e)
{
	VolumeDialog dialog(this);
	dialog.set(model->getVolumeConfig());
	const auto result = dialog.ShowModal();
	if (result == wxID_OK) {
		model->setVolumeConfig(dialog.get());
		model->createVolume(dialog.get());
		setRendering();
	}
}
