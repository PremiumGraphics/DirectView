#include <stdafx.h>
#include "View.h"

#include "../Graphics/Surface.h"

#include "Converter.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Model;
using namespace Crystal::UI;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()


View::View( Frame* parent, const int width, const int height, const MainModelSPtr<float>& model )
:wxGLCanvas(parent, wxID_ANY, NULL, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
mode( CAMERA_TRANSLATE ),
renderingMode( RENDERING_MODE::POINT ),
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
}

View::~View()
{
}



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
	CameraSPtr<float> camera = model->getCamera();
	Vector3d<float> pos = camera->getPos();

	switch ( event.GetKeyCode() ) {
	case WXK_RIGHT:
		pos += Vector3d<float>( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_LEFT:
		pos -= Vector3d<float>( 0.1f, 0.0f, 0.0f );
		break;
	case WXK_DOWN:
		pos += Vector3d<float>( 0.0f, 0.1f, 0.0f );
		break;
	case WXK_UP:
		pos -= Vector3d<float>( 0.0f, 0.1f, 0.0f );
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
		wxMessageBox(wxString::Format("%d %d %d", r, g, b));

		const Object::Type& type = static_cast<Object::Type>(r);
		const unsigned int id = g;
		model->changeSelected(type, id);
		this->set(*model);
		Refresh();

		return;
	}

	if( event.Dragging() ) {
		Vector3d<float> pos;
		Vector3d<float> angle;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d<float>( 0.0f, 0.0f, diff.y * 1.0f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			angle += Vector3d<float>( diff.x * 0.01, diff.y * 0.01, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d<float>( diff.x * 0.1f, diff.y * 0.1f, 0.0f );	
		}
		
		if( mode == CAMERA_TRANSLATE ) {
			model->getCamera()->move( pos );
			model->getCamera()->addAngle( angle );
		}
		else if (mode == TRANSLATE) {
			model->move(pos);
			this->set(*model);
			//ssTransformCmd->move(pos);
		}
		else if (mode == ROTATE) {
			model->rotate(angle);
		}
		else if (mode == SCALE) {
			model->scale(pos);
		}
		else {
			assert( false );
		}

		draw( GetSize() );

		SwapBuffers();
    }

	mouseStart = event.GetPosition();
}

void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}

void View::set(const MainModel<float>& model)
{
	normalRenderer.clear();
	pointBuffer.clear();
	lineBuffer.clear();
	triangleBuffer.clear();

	set( model.getSurfaceModel() );
	set( model.getVolumeModel() );
	set( model.getMetaballModel() );
}

void View::set(const SurfaceModelSPtr<float>& model)
{
	for (const auto& p : model->getPolygons()) {
		if (p->isVisible()) {
			normalRenderer.add(*(p->getPolygon()));
			const auto& surface = p->getPolygon();
			const int type = static_cast<int>(p->getType());
			const int isSelected = p->isSelected();
			pointBuffer.add(*surface, type, p->getId(),isSelected );
			lineBuffer.add(*surface, type, p->getId(), isSelected );
			triangleBuffer.add(*surface, type, p->getId(), isSelected);
		}
	}
}

void View::set(const VolumeModelSPtr<float>& model)
{
	for (const auto& b : model->getSpaces()) {
		if (b->isVisible()) {
			const auto& ss = b->getSpace();
			const auto& cells = ss->toCells();
			for (const auto& c : cells) {
				const auto center = c.getSpace().getCenter();
				const int type = static_cast<int>(b->getType());
				const int isSelected = b->isSelected();
				//pointBuffer.addPosition(center, type, b->getId(), isSelected);
			}
		}
	}

}

void View::set(const MetaballModelSPtr<float>& model)
{
	for (const auto& b : model->getBalls()) {
		if (b->isVisible()) {
			const auto center = b->getMetaball()->getCenter();
			const int type = static_cast<int>( b->getType() );
			const int isSelected = b->isSelected();
			pointBuffer.addPosition(center, type, b->getId(), isSelected);
		}
	}
}


void View::draw(const wxSize& size)
{
	const int width = size.GetWidth();
	const int height = size.GetHeight();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	Camera<float> c = *(model->getCamera());

	glPointSize(getPointSize());

	if( renderingMode == RENDERING_MODE::WIRE_FRAME ) {
		const auto& wConfig = config.getWireframeConfig();
		glLineWidth( wConfig.getLineWidth() );
		//wireFrameRenderer.render(width, height, c );
		idRenderer.render(width, height, c, lineBuffer);
	}
	else if( renderingMode == RENDERING_MODE::SURFACE ) {
		idRenderer.render(width, height, c, triangleBuffer);
		//surfaceRenderer.render(width, height, c );
	}
	else if (renderingMode == RENDERING_MODE::NORMAL) {
		const auto nConfig = config.getNormalConfig();
		glLineWidth( nConfig.getLineWidth() );
		normalRenderer.scale = nConfig.getNormalScale();
		normalRenderer.render(width, height, c );
	}
	else if (renderingMode == RENDERING_MODE::POINT) {
		const auto& pConfig = config.getPointConfig();
		glPointSize(pConfig.getPointSize());
		idRenderer.render(width, height, c, pointBuffer );
	}
	else {
		assert( false );
	}
}

void View::build()
{
	normalRenderer.build();
	idRenderer.build();
}