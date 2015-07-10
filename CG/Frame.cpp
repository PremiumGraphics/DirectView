#include <stdafx.h>

#include "Frame.h"

#include "View.h"


#include "wx/filename.h"

#include "../UI/VolumeDialog.h"
#include "../UI/UserEntryDialog.h"

#include "wx/numdlg.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Command;
using namespace Crystal::UI;


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

	createPanels(page);

	//Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Frame::OnKeyDown));
	this->Bind(wxEVT_CHAR_HOOK, &Frame::OnKeyDown, this);

	bar->Realize();
	
	const int width = 1600;//720;
	const int height = 900;////480;

	view = new View( this, width, height, model );

	SetIcon(wxICON(sample));

	wxInitAllImageHandlers();

	SetClientSize( width, height );

	CreateStatusBar( 2 );

	wxSizer* vSizer = new wxBoxSizer( wxVERTICAL );
	wxSizer* hSizer = new wxBoxSizer( wxHORIZONTAL );

	hSizer->Add( view, 0, wxEXPAND);


	vSizer->Add( bar, 0, wxEXPAND );
	vSizer->Add( hSizer, 0, wxEXPAND );

	createDialogs();


	SetSizer( vSizer );
	
	Show();

	setRendering();

}

void Frame::createDialogs()
{

	brushSizeDialog = new FloatEntryDialog(this, "Size", 0.5f);
	brushSizeDialog->setRange(0.1f, 10.0f);
}

void Frame::createPanels(wxRibbonPage* parent)
{
	createFilePanel(parent);
	createCameraPanel(parent);
	createBrushPanel(parent);
	createRenderingPanel(parent);
	createHelpPanel(parent);
}


void Frame::createFilePanel(wxRibbonPage* parent)
{
	wxRibbonPanel *panel = new wxRibbonPanel(parent, wxID_ANY, wxT("File"));
	wxRibbonButtonBar *bar = new wxRibbonButtonBar(panel);

	const auto importId = wxNewId();
	const auto exportId = wxNewId();
	const auto captureId = wxNewId();

	bar->AddButton(wxID_NEW,	"New",		wxArtProvider::GetBitmap(wxART_NEW, wxART_OTHER, wxSize(32, 32)));
	bar->AddButton(wxID_OPEN,	"Open",		wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(32, 32)));
	bar->AddButton(wxID_SAVE,	"Save",		wxImage("../Resource/save.png"));
	bar->AddButton(wxID_SAVEAS, "Save As",	wxArtProvider::GetBitmap(wxART_FILE_SAVE_AS, wxART_OTHER, wxSize(32, 32)));
	bar->AddButton(wxID_CLOSE,	"Close",	wxImage("../Resource/cancel.png"));
	bar->AddButton(importId,	"Import",	wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_OTHER, wxSize(32, 32)));
	bar->AddButton(exportId,	"Export",	wxImage("../Resource/export.png"), "Export");
	bar->AddButton(captureId,	"Capture",	wxImage("../Resource/screenshot.png"));

	Connect(wxID_NEW, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnNew));
	Connect(wxID_OPEN, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileOpen));
	Connect(wxID_SAVE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileSave));
	Connect(wxID_SAVEAS, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnFileSaveAs));
	Connect(wxID_CLOSE, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnClose));
	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));

	Connect(importId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnImport));
	Connect(exportId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnExport));
	Connect(captureId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCapture));

}

void Frame::createCameraPanel(wxRibbonPage* parent)
{
	wxRibbonPanel *panel = new wxRibbonPanel(parent, wxID_ANY, wxT("Camera"));
	wxRibbonButtonBar* bar = new wxRibbonButtonBar(panel);

	const int cameraId = wxNewId();
	const int centerId = wxNewId();
	const int xyId = wxNewId();
	const int yzId = wxNewId();
	const int zxId = wxNewId();

	bar->AddButton(cameraId, "Camera", wxImage("../Resource/view.png"));
	bar->AddButton(centerId, "Center", wxImage("../Resource/zoom.png"));
	bar->AddButton(xyId, "XY", wxImage("../Resource/zoom.png"));
	bar->AddButton(yzId, "YZ", wxImage("../Resource/zoom.png"));
	bar->AddButton(zxId, "ZX", wxImage("../Resource/zoom.png"));

	Connect(cameraId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraControl));
	Connect(centerId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraFit));
	Connect(xyId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraXY));
	Connect(yzId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraYZ));
	Connect(zxId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCameraZX));
}

void Frame::createBrushPanel(wxRibbonPage* parent)
{
	wxRibbonPanel *panel = new wxRibbonPanel(parent, wxID_ANY, wxT("Brush"));
	wxRibbonButtonBar* bar = new wxRibbonButtonBar(panel);

	const int spriteId = wxNewId();
	const int lineId = wxNewId();
	//const int eraseId = wxNewId();

	bar->AddHybridButton(spriteId,		"Sprite", wxImage("../Resource/point.png"));
	//bar->AddButton(eraseId,		"Erase", wxImage("../Resource/point.png"));


	//operation->AddDropdownButton( ID_POLYGON, wxT("Other Polygon"), wxBitmap(hexagon_xpm), wxEmptyString);
	//operation->AddButton(ID_PICK_VERTEX, "Pick", wxImage("../Resource/8-direction.png"));

	Connect(spriteId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnStrokeSprite));
	Connect(spriteId, wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnStrokeSpriteConfig));


	const int configId = wxNewId();

	bar->AddButton(configId, "Grid", wxImage("../Resource/grid.png"));
	//bar->AddButton(ID_CANVAS_CLEAR, "Clear", wxImage(32, 32));
	Connect(configId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCanvasConfig));
	//Connect( ID_CREATE_VOLUME, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnCreateVolume));

	const int eraseId = wxNewId();
	bar->AddButton(eraseId, "Erase", wxImage("../Resource/grid.png"));
	Connect(eraseId, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnParticleErase));

	//bar->AddButton(ID_BONE_MOVE, "Move", wxImage("../Resource/point.png"));
	//bar->AddButton(ID_BONE_BAKE, "Bake", wxImage("../Resource/point.png"));



	//Connect(eraseId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnParticleErase));
}

void Frame::createRenderingPanel(wxRibbonPage* parent)
{
	wxRibbonPanel *panel = new wxRibbonPanel(parent, wxID_ANY, wxT("Rendering"));
	wxRibbonButtonBar* bar = new wxRibbonButtonBar(panel);

	const auto pointId = wxNewId();
	const auto wireId = wxNewId();
	const auto normalId = wxNewId();
	const auto volumeId = wxNewId();
	const auto smoothId = wxNewId();

	bar->AddHybridButton(pointId, "Point", wxImage("../Resource/wireframe.png"));
	bar->AddHybridButton(wireId, "Wireframe", wxImage("../Resource/wireframe.png"));
	bar->AddHybridButton(normalId, "Normal", wxImage("../Resource/wireframe.png"));
	bar->AddHybridButton(volumeId, "Volume", wxImage("../Resource/wireframe.png"));
	bar->AddHybridButton(smoothId, "Smooth", wxImage("../Resource/wireframe.png"));

	Connect(pointId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingPoint));
	Connect(pointId,	wxEVT_RIBBONBUTTONBAR_DROPDOWN_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingPointConfig));
	Connect(wireId,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingWireframe));
	Connect(normalId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingNormal));
	Connect(volumeId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingVolume));
	Connect(smoothId,	wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnRenderingSmooth));
}

void Frame::createHelpPanel(wxRibbonPage* parent)
{
	wxRibbonPanel *panel = new wxRibbonPanel(parent, wxID_ANY, wxT("Help"));
	wxRibbonButtonBar* bar = new wxRibbonButtonBar(panel);
	bar->AddButton(wxID_ABOUT, "About", wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(32, 32)));

	Connect(wxID_ABOUT, wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnAbout));
}


void Frame::OnNew( wxRibbonButtonBarEvent& e )
{
	const int ret = wxMessageBox(wxT("モデルを保存しますか？"), wxEmptyString, wxYES_NO, this );

	if( ret == wxYES ) {
		OnFileSaveAs( e );
		return;
	}

	model.clear();
	setRendering();
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

void Frame::OnFileSave( wxRibbonButtonBarEvent& )
{
	wxMessageBox("TODO: ファイルフォーマット作成中");

	/*
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
	*/
}

void Frame::OnFileSaveAs( wxRibbonButtonBarEvent& e )
{
	wxMessageBox("TODO: ファイルフォーマット作成中");
}

void Frame::OnFileOpen( wxRibbonButtonBarEvent& e )
{
	wxMessageBox("TODO: ファイルフォーマット作成中");

	/*
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
	const bool isOk = model.read( filename.ToStdString() );
	if( !isOk ) {
		wxMessageBox( wxT("読み込みに失敗しました。") );
	}
	*/
}

void Frame::OnCameraControl( wxRibbonButtonBarEvent& )
{
	model.setUIControl( Command::UIControl::CAMERA );
}

void Frame::OnImport( wxRibbonButtonBarEvent& e )
{
	wxMessageBox("TODO");

	/*
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
	model.doExport(str);
	/*
	if( ext == "stl" || ext == "STL" ) {
		const auto str = filename.ToStdString();
		//model.doExport(str);
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

void Frame::OnRenderingPoint(wxRibbonButtonBarEvent& e)
{
	RenderingConfig<float> config = model.getRenderingConfig();
	config.drawPoint = !config.drawPoint;
	model.setRenderingConfig( config );
	setRendering();
	view->Refresh();

}

void Frame::OnRenderingPointConfig(wxRibbonButtonBarEvent& e)
{
	const int pointSize = wxGetNumberFromUser("PointSize", "", "");
	if (pointSize <= 0) {
		return;
	}
}


void Frame::OnRenderingWireframe( wxRibbonButtonBarEvent& e)
{
	/*
	WireframeConfigDialog dialog(this);
	RenderingConfig<float> rConfig = model.getRenderingConfig();
	dialog.set(rConfig);
	if (dialog.ShowModal() == wxID_OK) {
		rConfig = dialog.get();
		model.setRenderingConfig(rConfig);
		setRendering();
	}
	view->Refresh();
	*/
	RenderingConfig<float> config = model.getRenderingConfig();
	config.drawWire = !config.drawWire;
	model.setRenderingConfig(config);
	setRendering();
	view->Refresh();
}

void Frame::OnRenderingWireframeConfig(wxRibbonButtonBarEvent& e)
{
	const int lineWidth = wxGetNumberFromUser("LineWidth", "", "");
	if (lineWidth <= 0) {
		return;
	}

}

void Frame::OnRenderingNormal(wxRibbonButtonBarEvent& e)
{
	RenderingConfig<float> config = model.getRenderingConfig();
	config.drawNormal = !config.drawNormal;
	model.setRenderingConfig(config);
	setRendering();
	view->Refresh();
}


void Frame::OnRenderingVolume(wxRibbonButtonBarEvent& e)
{
	RenderingConfig<float> config = model.getRenderingConfig();
	config.drawVolume = !config.drawVolume;
	model.setRenderingConfig(config);
	setRendering();
	view->Refresh();
}

void Frame::OnRenderingVolumeConfig(wxRibbonButtonBarEvent& e)
{
	const int pointSize = wxGetNumberFromUser("PointSize", "", "");
	if (pointSize <= 0) {
		return;
	}

}


void Frame::OnRenderingSmooth(wxRibbonButtonBarEvent& e)
{
	RenderingConfig<float> config = model.getRenderingConfig();
	config.drawSmooth = !config.drawSmooth;
	model.setRenderingConfig(config);
	setRendering();
	view->Refresh();
}

void Frame::OnRenderingSmoothConfig(wxRibbonButtonBarEvent& e)
{
	;
}

void Frame::OnCameraFit( wxRibbonButtonBarEvent& e )
{
	model.fitCamera();
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

void Frame::OnStrokeSprite(wxRibbonButtonBarEvent& e)
{
	model.setUIControl(Command::UIControl::SPRITE_STROKE);
}

void Frame::OnStrokeSpriteConfig(wxRibbonButtonBarEvent& e)
{
	/*
	const auto& command = model.getSpriteStrokeCommand();
	FloatEntryDialog dialog(this, "Charge", command->getCharge());
	dialog.setRange(-1.0f, 1.0f);

	if (dialog.ShowModal() == wxID_OK) {
		command->setCharge( dialog.getValue() );
	}
	else {
		return;
	}
	*/

}

void Frame::OnParticleErase(wxRibbonButtonBarEvent& e)
{
	model.setUIControl(Command::UIControl::PARTICLE_ERASE);
	//model.setUIControl);
}
/*
void Frame::OnBoneBake(wxRibbonButtonBarEvent& e)
{
	model.bakeBoneToVolume();
	setRendering();
}
*/


void Frame::setRendering()
{
	model.setRendering();
	view->Refresh();

}

void Frame::OnCanvasConfig(wxRibbonButtonBarEvent& e)
{
	VolumeDialog dialog(this);
	Math::Volume3d<float>::Attribute attr;
	dialog.set(attr);
	const auto result = dialog.ShowModal();
	if (result == wxID_OK) {
		Math::Volume3dSPtr<float> v = std::make_shared<Math::Volume3d<float> >(dialog.get());
		model.setVolume(v);
		setRendering();
	}
}

//bool xIsDown = false;

void Frame::OnKeyDown(wxKeyEvent& event)
{
	switch (event.GetKeyCode()) {
	case 'Z':
		model.setUIControl(Command::UIControl::SPRITE_STROKE);
		break;
	case 'C':
		model.setUIControl(Command::UIControl::CAMERA);
		break;
	case 'N':
		//model.setParticleCharge(-1.0f);
		break;
	case 'M':
		//model.setParticleCharge(1.0f);
		break;
	default:
		event.Skip();
		return;
	};

}

void Frame::OnKeyUp(wxKeyEvent& event)
{

}

void Frame::OnCameraXY(wxRibbonButtonBarEvent& e)
{
	model.getCamera()->setAngle(Vector3d<float>(0.0, 0.0, 0.0));
	view->Refresh();
}

void Frame::OnCameraYZ(wxRibbonButtonBarEvent& e)
{
	model.getCamera()->setAngle(Vector3d<float>(Tolerance<float>::getHalfPI(), 0.0, 0.0));
	view->Refresh();
}

void Frame::OnCameraZX(wxRibbonButtonBarEvent& e)
{
	model.getCamera()->setAngle(Vector3d<float>(0.0, Tolerance<float>::getHalfPI(), 0.0));
	view->Refresh();
}
