#include <stdafx.h>
#include "View.h"
#include "Frame.h"

#include "../Math/Matrix3d.h"
#include "../Math/Quaternion.h"

#include "../Graphics/Camera.h"

#include "Converter.h"

using namespace Crystal::Graphics;
using namespace Crystal::IO;
using namespace Crystal::App;


BEGIN_EVENT_TABLE( View, wxGLCanvas )
	EVT_PAINT( View::OnPaint )
	EVT_MOUSE_EVENTS( View::OnMouse )
END_EVENT_TABLE()

View::View( Frame* parent, int* args, const int width, const int height  )
:wxGLCanvas(parent, wxID_ANY, args, wxPoint( 0, 0), wxSize( width, height ), wxFULL_REPAINT_ON_RESIZE ),
glContext( this ),// width, height ),
frame( parent ),
renderingMode( WireFrame ),
pointSize( 1.0f ),
vectorScale( 1.0f ),
lineWidth( 1.0f ),
isCell( false )
{
	glContext.SetCurrent( *this );

	//Connect( wxEVT_PAINT, wxPaintEventHandler( View::OnPaint ) );
	Connect( wxEVT_KEY_DOWN, wxKeyEventHandler( View::OnKeyDown ) );
	//Connect( wxEVT_MOUSEWHEEL, wxMouseEventHandler( View::onMouse ) );
	Connect( wxEVT_SIZE, wxSizeEventHandler( View::OnSize ) );

	build();

	std::vector< float > pixels;
	pixels.push_back( 1.0f );
	pixels.push_back( 0.0f );
	pixels.push_back( 0.0f );
	pixels.push_back( 1.0f );

	pixels.push_back( 0.0f );
	pixels.push_back( 0.0f );
	pixels.push_back( 1.0f );
	pixels.push_back( 1.0f );
}

View::~View()
{
}

#include "../Math/Vector3d.h"

using namespace Crystal::Math;


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
/*
	Camera* camera = frame->getModel()->getCameraModel()->getCamera();
	Vector3d pos = camera->pos;

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

	camera->pos = pos;

	draw( GetSize() );

	SwapBuffers();
	*/

}

void View::OnMouse( wxMouseEvent& event )
{
	if( event.Dragging() ) {
		Vector3d pos;
		Vector3d angle;

		if( event.MiddleIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( 0.0f, 0.0f, diff.y * 0.5f );
		}
		else if( event.RightIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			angle += Vector3d( diff.x * 0.01f, diff.y * 0.01f, 0.0f );
		}
		else if( event.LeftIsDown() ) {
			wxPoint position = event.GetPosition();
			const wxPoint diff = position - mouseStart;
			pos += Vector3d( diff.x * 0.1f, diff.y * 0.1f, 0.0f );	
		}
		
		frame->getCamera()->move( pos );
		frame->getCamera()->addAngle( angle );

		draw( GetSize() );

		glFlush();
		SwapBuffers();
    }

	mouseStart = event.GetPosition();
}

void View::OnSize(wxSizeEvent& e)
{
	draw( e.GetSize() );
}

void View::setRenderingBlocks()
{
	this->indices.clear();
	this->min = 0.0f;
	this->max = 1.0f;

	for( VTKObject* object : frame->getFactory()->getSelectedObjects() ) {
		if( object == nullptr ) {
			continue;
		}
		const Vector3dVector& vertices = object->getVertices();
		this->positions = Vector3d::toArray(vertices);
		vertexValues.resize( vertices.size(), 0.5  );
		cellValues.resize( object->getCells().size(), 0.5 );
		
		this->indices = object->getConnections();			

		for( VTKAttributes* attr : object->getNodeAttributes() ) {
			if( !attr->isSelected() ) {
				continue;
			}
			if( attr->getDim() == 1 ) {
				ColorRGBAMap<float>* map = object->getColorMap( attr->getLookupTableName() );
				texColors = map->getColors();
				this->min = attr->getMin();
				this->max = attr->getMax();
				vertexValues = attr->getValues();
				isCell = false;
			}
			else {
				ColorRGBAMap<float>* map = object->getColorMap( attr->getLookupTableName() );
				texColors = map->getColors();
				//this->vectors = attr->getValues();
				const Vector3dVector& vectors = attr->toVector3ds();
				min = FLT_MAX;
				max = -FLT_MAX;
				for( const Vector3d& v : vectors ) {
					min = std::min<float>( min, v.getLength() );
					max = std::max<float>( max, v.getLength() );
				}
				this->vectors = Vector3d::toArray( vectors );
			}
		}

		const Vector3dVector& centers = object->getCellCenters();

		for( VTKAttributes* attr : object->getCellAttributes() ) {
			if( !attr->isSelected() ) {
				continue;
			}
			if( attr->getDim() == 1 ) {
				ColorRGBAMap<float>* map = object->getColorMap( attr->getLookupTableName() );
				texColors = map->getColors();
				this->min = attr->getMin();
				this->max = attr->getMax();
				cellValues = attr->getValues();
				isCell = true;
			}
			else {
				cellCenters = Vector3d::toArray(centers);
				ColorRGBAMap<float>* map = object->getColorMap( attr->getLookupTableName() );
				texColors = map->getColors();
				const Vector3dVector& vectors = attr->toVector3ds();
				min = FLT_MAX;
				max = -FLT_MAX;
				for( const Vector3d& v : vectors ) {
					min = std::min<float>( min, v.getLength() );
					max = std::max<float>( max, v.getLength() );
				}			
				this->vectors = Vector3d::toArray(vectors);
			}
		}
	}
}

void View::draw(const wxSize& size)
{
	//command->draw( frame->getPolygons(), size.GetWidth(), size.GetHeight(), frame->getCamera(), frame->getLights(), frame->getMaterials() );

	const int width = size.GetWidth();
	const int height = size.GetHeight();

	//setRenderingBlocks();
	
	if( renderingMode == RenderingMode::WireFrame ) {
		WireFrameRenderer::Param param;
		param.positions = positions;
		param.max = max;
		param.min = min;
		param.projectionMatrix = frame->getCamera()->getPerspectiveMatrix().toArray4x4();
		param.modelviewMatrix = frame->getCamera()->getModelviewMatrix().toArray4x4();
		if( isCell ) {
			param.values = cellValues;
			meshRenderer.renderCells(width, height, param, indices, texColors, false );
		}
		else {
			param.values = vertexValues;
			meshRenderer.render( width, height, param, indices, texColors, false );
		}
	}
	else if( renderingMode == RenderingMode::VectorMap ) {
		if( isCell ) {
			vectorRenderer.render(  width, height, frame->getCamera(), cellCenters, vectors, min, max, texColors, lineWidth, vectorScale  );
		}
		else {
			vectorRenderer.render(  width, height, frame->getCamera(), positions, vectors, min, max, texColors, lineWidth, vectorScale  );	
		}
	}
	else if( renderingMode == RenderingMode::PointSprite ) {		
		pointRenderer.render( width, height, frame->getCamera(), positions, vertexValues, min, max, texColors, pointSize );
	}
	else if( renderingMode == RenderingMode::Surface ) {
		WireFrameRenderer::Param param;
		param.positions = positions;
		param.max = max;
		param.min = min;
		param.projectionMatrix = frame->getCamera()->getPerspectiveMatrix().toArray4x4();
		param.modelviewMatrix = frame->getCamera()->getModelviewMatrix().toArray4x4();

		if( isCell ) {
			param.values = cellValues;
			meshRenderer.renderCells( width, height, param, indices, texColors, true );
		}
		else {
			param.values = vertexValues;
			meshRenderer.render(width, height, param, indices, texColors, true );
		}
	}
	else {
		assert( false );
	}
}

void View::build()
{
	meshRenderer.build();
	vectorRenderer.build();
	pointRenderer.build();
}