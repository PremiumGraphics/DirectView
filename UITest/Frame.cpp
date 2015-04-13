#include <stdafx.h>

#include "Frame.h"

#include "View.h"

#include "../UI/PolygonTree.h"
#include "../UI/PropertyDialog.h"
#include "../Graphics/PolygonBuilder.h"

#include "wx/filename.h"

#include "../IO/OBJFile.h"
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::Modeling;
using namespace Crystal::UI;

enum {
	ID_POLYGON_CONFIG = wxID_HIGHEST+1,

	ID_CAMERA_CONFIG,

	ID_CAMERA_TRANSLATE,
	ID_POLYGON_TRANSLATE,
	ID_POLYGON_ROTATE,
	//ID_PICK_VERTEX,


	ID_POLYGON_SCALE,
	ID_POLYGON_SCALE_X,
	ID_POLYGON_SCALE_Y,
	ID_POLYGON_SCALE_Z,

	ID_CAMERA_FIT,

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
	polygonProperty = new PolygonProperty(parent, wxSize(300, 300), model.getPolygonBuilder()->getMaterialBuilder().getMaterials());

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


	wxRibbonPanel *operationPanel = new wxRibbonPanel( page, wxID_ANY, wxT("Operation") );
	wxRibbonButtonBar* operation = new wxRibbonButtonBar( operationPanel );
	operation->AddButton( ID_CAMERA_TRANSLATE,	"Camera",	wxImage(32,32) );
	operation->AddButton(ID_CAMERA_FIT, "Fit", wxImage(32, 32));
	operation->AddButton(ID_POLYGON_TRANSLATE, "Move", wxImage(32, 32));
	operation->AddButton(ID_POLYGON_ROTATE, "Rotate", wxImage(32, 32));

	operation->AddButton(ID_POLYGON_SCALE, "Scale", wxImage(32, 32));

	Connect( ID_CAMERA_FIT,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnCameraFit ) );
	Connect( ID_POLYGON_TRANSLATE,		wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonTranslate ) );
	Connect( ID_POLYGON_SCALE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonScale ) );
	Connect( ID_POLYGON_ROTATE,			wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler( Frame::OnPolygonRotate ) );
	//Connect(ID_PICK_VERTEX,				wxEVT_RIBBONBUTTONBAR_CLICKED, wxRibbonButtonBarEventHandler(Frame::OnPick) );

	wxRibbonPanel *helpPanel = new wxRibbonPanel(page, wxID_ANY, wxT("ヘルプ"));
	wxRibbonButtonBar* helpToolBar = new wxRibbonButtonBar(helpPanel);
	helpToolBar->AddButton(wxID_ABOUT, "About", wxArtProvider::GetBitmap(wxART_INFORMATION, wxART_OTHER, wxSize(32, 32)), "このソフトについて");



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

#include "../IO/CGSFile.h"


void Frame::OnCameraTranslate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::CAMERA_TRANSLATE );
}

void Frame::OnPolygonRotate( wxRibbonButtonBarEvent& )
{
	view->setMode( View::POLYGON_ROTATE );
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
	const Math::Vector3d& center = model.getPolygonBuilder()->getgetgetCenter();
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


void Model::setSelectedVertex(const unsigned int id)
{
	if (id >= 0 && id < getVertices().size()) {
		const VertexSPtrVector& vs = getVertices();
		const VertexSPtr& v = vs[id];
		this->selectedVertex.clear();
		this->selectedVertex.push_back(v);
	}
}

void Model::setSelectedFace(const unsigned int id)
{
	if (id >= 0 && id < getFaces().size()) {
		const FaceSPtrVector& faces = getFaces();
		const FaceSPtr& f = faces[id];
		this->selectedFace.clear();
		this->selectedFace.push_back(f);
	}
}
