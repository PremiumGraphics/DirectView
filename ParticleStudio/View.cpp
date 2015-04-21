#include <stdafx.h>
#include "View.h"

#include "../Math/Matrix3d.h"
#include "../Math/Quaternion.h"

#include "../Graphics/Polygon.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::CG;
using namespace Crystal::IO;


BEGIN_EVENT_TABLE(View, wxGLCanvas)
EVT_MOUSE_EVENTS(View::OnMouse)
END_EVENT_TABLE()

const ColorRGB<float> selectedColor = ColorRGB<float>::Red();

View::View( Frame* parent, const int width, const int height, Model& model  )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
pointSize( 10.0f ),
model( model )
{
	glContext.SetCurrent( *this );

//	const int attributes[] = {WX_GL_SAMPLE_BUFFERS};
//	bool b = IsDisplaySupported( attributes );

	Connect( wxEVT_PAINT, wxPaintEventHandler( View::OnPaint ) );
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( View::OnKeyDown ) );
	//Connect( wxEVT_MOUSE_EVENTS, wxMouseEventHandler( View::onMouse ) );
	Connect( wxEVT_SIZE, wxSizeEventHandler( View::OnSize ) );

	build();

	//texture = new TextureObject( pixels, 2, 1 );
}

View::~View()
{
	//delete texture;
}

#include "../Math/Vector3d.h"


void View::OnPaint( wxPaintEvent& )
{
	wxPaintDC dc( this );

	const wxSize size = GetClientSize();

	glContext.SetCurrent(*this);

	glViewport(0, 0, size.x, size.y );

	draw( size );

	glFlush();

	SwapBuffers();
}

void View::OnKeyDown(wxKeyEvent& event)
{
	Camera<float>* camera = model.getCamera();
	Vector3d pos = camera->getPos();

	switch ( event.GetKeyCode() ) {
	case WXK_RIGHT:
		pos += Vector3d( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_LEFT:
		pos -= Vector3d( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_DOWN:
		pos += Vector3d( 0.0f, 0.1f, 0.0f );
		break;
	case WXK_UP:
		pos -= Vector3d( 0.0f, 0.1f, 0.0f );
		break;
	default:
		event.Skip();
		return;
	};

	camera->setPos( pos );

	draw( GetSize() );

	SwapBuffers();

}

void View::OnMouse( wxMouseEvent& event )
{
	if (event.LeftDClick()) {
		const int width = GetClientSize().GetWidth();
		const int height = GetClientSize().GetHeight();
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

		const wxPoint& position = event.GetPosition();
		const unsigned char r = image.GetRed(position.x, position.y);
		const unsigned char g = image.GetGreen(position.x, position.y);
		const unsigned char b = image.GetBlue(position.x, position.y);
		wxMessageBox(wxString::Format("%d %d %d vertex id = %d face id = %d polygon id = %d", r, g, b, r, g, b));
		const unsigned int id = b * 512;
		const ParticleObjectSPtr& object = model.getObjectById(id);

		if (object.get() != nullptr) {
			model.addSelectedObject(object);
		}
		if (r == 255 && g == 0 && b == 0) {
			model.clearSlectedObjects();
		}
		//frame->selectedFace = frame->get
		draw(GetSize());

		SwapBuffers();

		return;
	}

	if( event.Dragging() ) {
		Vector3d pos;
		Vector3d angle;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( 0.0f, 0.0f, diff.y * 1.0f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			angle += Vector3d( diff.x * 0.01, diff.y * 0.01, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( diff.x * 0.1f, diff.y * 0.1f, 0.0f );	
		}
		
		model.getCamera()->move( pos );
		model.getCamera()->addAngle( angle );

		draw( GetSize() );

		SwapBuffers();
    }

	mouseStart = event.GetPosition();
}

void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}

void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	buildDisplayList();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera<float> c = *(model.getCamera());

	glClearColor(0.0, 0.0, 0.0, 0.0);
		//glClear(GL_COLOR_BUFFER_BIT);
		//glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

	glPointSize(pointSize);
	pointRenderer.render(width, height, &c, list );

	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glPointSize(pointSize*1.5);
	pointRenderer.render(width, height, &c, selectedList);
		/*
		glBegin(GL_POINTS);
		glVertex3f(0.0f, 0.0f, 5.0f);
		glEnd();
		glFlush();
		*/
}

void View::build()
{
	pointRenderer.build();
}

void View::buildDisplayList()
{
	//for (const ParticleObject& object : model.getParticleBuilder().)
	list.clear();
	selectedList.clear();
	/*
	const PolygonSPtrList& polygons = model.getPolygons();
	for (const PolygonSPtr& p : polygons) {
		//dispList.add( p.get() );
		for (const VertexSPtr& v : p->getVertices()) {
			const std::vector<float>& vs = v->getPosition().toArray();
			positions.insert(positions.end(), vs.begin(), vs.end());
		}
	}
	*/
	for (const ParticleObjectSPtr& object : model.getParticleObjects() ) {
		list.add(*object);
	}
	for (const ParticleObjectSPtr& object : model.getSelectedObjects()) {
		selectedList.add(*object, selectedColor);
	}
	/*
	for (const Polygon& p : model.getParticleBuilder().) {

	}
	*/
}