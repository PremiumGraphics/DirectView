#include "stdafx.h"
#include "ColorMapCanvas.h"

#include <vector>

using namespace Crystal::Graphics;
using namespace Crystal::App;

ColorMapCanvas::ColorMapCanvas
	(
	wxWindow *parent,
	const wxPoint& pos,
	const wxSize& size,
	ColorRGBAMap<float>* colorMap
	)
	: wxScrolledWindow(
	parent,
	wxID_ANY,
	pos,
	size,
	wxSUNKEN_BORDER | wxNO_FULL_REPAINT_ON_RESIZE
	),
	colorMap( colorMap )
{
    SetBackgroundColour( *wxWHITE );

    //SetScrollbars(20, 20, 50, 50);
}


void ColorMapCanvas::OnDraw(wxDC& dc) {
	dc.SetBrush( *wxCYAN_BRUSH );

	//dc.GetFont().SetPointSize( 10 );

	const int height = GetClientSize().GetHeight();
	const int width = GetClientSize().GetWidth();

	const int penWidth = 5;

	{
		wxPen pen( *wxRED, penWidth );
		dc.SetPen( pen );

		const std::vector< float >& reds = colorMap->getReds();
		wxPointList* points = new wxPointList();

		for( size_t i = 0; i < reds.size(); ++i ) {
			const int x = i / static_cast<float>(reds.size()) * width;
			const int y = height - reds[i] * height; 
			points->push_back( new wxPoint( x, y ) );
		}
		//dc.DrawSpline( points );
		dc.DrawLines( points );
	}

	{
		wxPen pen( *wxGREEN, penWidth );
		dc.SetPen( pen );

		const std::vector< float >& greens = colorMap->getGreens();
		wxPointList* points = new wxPointList();

		for( size_t i = 0; i < greens.size(); ++i ) {
			const int x = i / static_cast<float>(greens.size()) * GetClientSize().GetWidth();
			const int y = height - greens[i] * height;
			points->push_back( new wxPoint( x, y ) );
		}
		//dc.DrawSpline( points );
		dc.DrawLines( points );
	}

	{
		wxPen pen( *wxBLUE, penWidth );
		dc.SetPen( pen);

		const std::vector< float >& blues = colorMap->getBlues();
		wxPointList* points = new wxPointList();

		for( size_t i = 0; i < blues.size(); ++i ) {
			const int x = i / static_cast<float>(blues.size()) * GetClientSize().GetWidth();
			const int y = height - blues[i] * height;
			points->push_back( new wxPoint( x, y ) );
		}
		//dc.DrawSpline( points );
		dc.DrawLines( points );
	}

}
